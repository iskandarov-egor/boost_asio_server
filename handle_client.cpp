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
#include <unistd.h>
#include "http.h"
#include "validation.h"
#include "file_sender_blocking.h"
#include "handle_client.h"

using namespace std;
using boost::asio::ip::tcp;
using namespace client_handler;

void handle_write_headers(shared_ptr<tcp::socket> sock,
                          Config config,
                          string uri,
                          const boost::system::error_code &error) {
    if(error) {
        print_log("handle_write_headers error", error);
        return;
    }
    print_log("read_handler: serving uri", uri);
    serve_file(uri, sock, config.FILE_CHUNK_SIZE);
}

void respond(shared_ptr<tcp::socket> sock, Config config, string uri, string &headers) {
    print_log("writing headers", "");
    boost::asio::async_write(*sock,
                             boost::asio::buffer(headers.c_str(), headers.length()),
                             boost::bind(handle_write_headers,
                                         sock,
                                         config,
                                         uri,
                                         boost::asio::placeholders::error));
}

void handle_request(shared_ptr<tcp::socket> socket,
                    Config config,
                    shared_ptr<boost::asio::streambuf> request_data,
                    const boost::system::error_code &error,
                    size_t bytes_transferred) {
    if(error) {
        if(boost::asio::error::eof == error)
            return;
        throw std::runtime_error("handle_read error");
    }

    // streambuf to string
    boost::asio::streambuf::const_buffers_type bufs = request_data->data();
    std::string request(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);

    print_log("read_handler request", "'" + request + "'");

    string uri;
    bool flag = false;
    if(!extract_uri(request, uri)) {
        print_log("read_handler: invalid request", request);
        flag = true;
    }
    uri = config.DOCUMENT_ROOT + uri;
    if(!validate_and_normalize_uri(uri, config.DOCUMENT_ROOT)) {
        print_log("read_handler: validation failed", uri);
        flag = true;
    }

    StatusCode status_code = OK;

    if(flag) {
        uri = config.HTML_404;
        status_code = NOT_FOUND;
    }

    string headers = make_headers(status_code, content_type_of(uri));
    respond(socket, config, uri, headers);
}

void handle_client(shared_ptr<tcp::socket> socket, Config config) {
    print_log("client handler", "new client");
    shared_ptr<boost::asio::streambuf> data { new boost::asio::streambuf(1024) }; // todo test

    async_read_until(*socket, *data, '\n', boost::bind(handle_request,
                                                       socket,
                                                       config,
                                                       data,
                                                       boost::asio::placeholders::error,
                                                       boost::asio::placeholders::bytes_transferred
                                                   ));
}
