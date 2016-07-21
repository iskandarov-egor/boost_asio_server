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
#include "file_serving.h"
#include "config.h"
#include <unistd.h>

using boost::asio::ip::tcp;
using namespace boost::asio;

typedef boost::shared_ptr<tcp::socket> socket_ptr;
using namespace std;


void test_handler(shared_ptr<tcp::socket> socket) {
    cout << "handler handling!" << endl;
}

bool extract_uri(string &line, string &dest) {
    string LEFT { "GET " };
    string RIGHT { " HTTP/1.0" };
    try {
        if(line.compare(0, LEFT.length(), LEFT) != 0) {
            return false;
        }
        // todo find instead cause \r\n
        int right_pos = line.find(RIGHT.data(), 0, RIGHT.length());
        if(line.compare(right_pos, RIGHT.length(), RIGHT) != 0) {
            return false;
        }
        dest = line.substr(LEFT.length(), right_pos - LEFT.length());
    } catch(std::out_of_range) {
        return false;
    }
    return true;
}

void handle_read(shared_ptr<tcp::socket> socket,
                 boost::asio::streambuf *data,
                 const boost::system::error_code &error,
                 size_t bytes_transferred) {
    if(error) {
        print_log("handle_read error", error);
    }
    // streambuf to string
    boost::asio::streambuf::const_buffers_type bufs = data->data();
    std::string request(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);
    delete data;

    string uri;
    if(!extract_uri(request, uri)) {
        print_log("read_handler: invalid request", request);
    }
    print_log("read_handler request uri", "'" + uri + "'");

    serve_uri(socket, uri);
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
    std::thread thread1{[&io_service](){ io_service.run(); }};
    std::thread thread2{[&io_service](){ io_service.run(); }};
    std::thread thread3{[&io_service](){ io_service.run(); }};
    std::thread thread4{[&io_service](){ io_service.run(); }};
    thread1.join();
    //thread2.join();
    cout << "join!!" << endl;
    //io_service.run();
}


int main(int argc, char **argv)
{
    int i=fork();
	if (i<0) exit(1); /* fork error */
	if (i>0) exit(0); /* parent exits */
	/* child (daemon) continues */

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
