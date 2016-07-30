#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include "acceptor_loop.hpp"
#include "logger.h"
#include <fstream>
#include "config.h"
#include <unistd.h>
#include "http_request_parser.h"
#include "validation.h"
#include "file_sender_blocking.h"

using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace std;


void test_handler(shared_ptr<tcp::socket> socket) {
    cout << "handler handling!" << endl;
}

void handle_write_headers(shared_ptr<tcp::socket> sock, string uri, const boost::system::error_code &error) {
    if(error) {
        print_log("handle_write_headers error", error);
        return;
    }
    print_log("read_handler: serving uri", uri);
    serve_file(uri, sock);
}

void respond(shared_ptr<tcp::socket> sock, string uri, string &headers) {
    print_log("writing headers", "");
    boost::asio::async_write(*sock,
                             boost::asio::buffer(headers.c_str(), headers.length()),
                             boost::bind(handle_write_headers,
                                         sock,
                                         uri,
                                         boost::asio::placeholders::error));
}

string STATUS_OK = "200 OK";
string STATUS_NOT_FOUND = "404 NOT FOUND";

void handle_read(shared_ptr<tcp::socket> socket,
                 boost::asio::streambuf *data,
                 const boost::system::error_code &error,
                 size_t bytes_transferred) {
    if(error) {
        if(boost::asio::error::eof == error)
            return;
        throw std::runtime_error("handle_read error");
    }
    // streambuf to string
    boost::asio::streambuf::const_buffers_type bufs = data->data();
    std::string request(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);

    print_log("read_handler request", "'" + request + "'");
    delete data;

    string uri;
    if(!extract_uri(request, uri)) {
        print_log("read_handler: invalid request", request);
        return;
    }
    if(!validate_and_normalize_uri(uri)) {
        print_log("read_handler: validation failed", uri);
        return;
    }

    string headers = make_headers(STATUS_OK);

    respond(socket, uri, headers);
}

void client_handler(shared_ptr<tcp::socket> socket) {
    print_log("client handler", "starting");
    boost::asio::streambuf *data = new boost::asio::streambuf(512);

    async_read_until(*socket, *data, '\n', boost::bind(handle_read,
                                                       socket,
                                                       data,
                                                       boost::asio::placeholders::error,
                                                       boost::asio::placeholders::bytes_transferred
                                                   ));

    print_log("client handler", "leaving");
}

deadline_timer *timer;

void start_timer();

void timeout(const boost::system::error_code &error) {
    if (error)
        return;
    cout << "tick" << endl;
    start_timer();
}

void start_timer() {
    timer->expires_from_now(boost::posix_time::seconds(5));
    timer->async_wait(boost::bind(timeout, boost::asio::placeholders::error));
}

#include <thread>

void run_server() {
    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    cout << config::HOST << config::PORT << endl;
    tcp::resolver::query query(config::HOST, config::PORT);
    tcp::resolver::iterator iter = resolver.resolve(query);

    tcp::endpoint endpoint = iter->endpoint();
    start_acceptor_loop(io_service, endpoint, client_handler);
    //timer = new deadline_timer(io_service);
    //start_timer();
    io_service.run();
    //std::thread thread1{[&io_service](){ io_service.run(); }};
    //std::thread thread2{[&io_service](){ io_service.run(); }};
    //std::thread thread3{[&io_service](){ io_service.run(); }};
    //std::thread thread4{[&io_service](){ io_service.run(); }};
    //thread1.join();
    //thread2.join();
    cout << "join!!" << endl;
    //io_service.run();
}


int main(int argc, char **argv)
{


    try
    {

        config::parse_args(argc, argv);
        run_server();

    }
    catch (std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }

    return 0;
}
