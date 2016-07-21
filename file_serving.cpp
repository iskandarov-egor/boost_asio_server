#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include "logger.h"
#include <fstream>
#include "file_serving.h"
#include <string>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <stdexcept>
#include "config.h"

using namespace std;
using boost::asio::ip::tcp;

typedef struct ClientData {
    shared_ptr<tcp::socket> socket;
    std::ifstream fstream;
    char *buf;

    ClientData(shared_ptr<tcp::socket> _socket, string file_path):
        socket{_socket},
        buf{new char[512]},
        fstream{file_path.c_str(), std::ios::in | std::ios::binary}
    {
    }

    bool is_file_ok() {
        return (bool)fstream;
    }

    ~ClientData() {
        print_log("clientdata", "destruct");
        boost::system::error_code error_code;
        socket->shutdown(tcp::socket::shutdown_both, error_code);
        socket->close();
        if(error_code) {
            print_log("serve_chunk error while shutdown", error_code);
        }
        delete[] buf;
    }
} ClientData;

void handle_write_chunk(shared_ptr<ClientData> client_data, const boost::system::error_code &error);

void serve_chunk(shared_ptr<ClientData> client_data) {
    if (client_data->fstream.read(client_data->buf, 512).gcount() > 0) {
        print_log("serve_uri serving chunk, len ", client_data->fstream.gcount());

        boost::asio::async_write(*(client_data->socket),
                                 boost::asio::buffer(client_data->buf, client_data->fstream.gcount()),
                                 boost::bind(handle_write_chunk,
                                             client_data,
                                             boost::asio::placeholders::error));
    } else {
        print_log("serve_uri", "no more chunks");


    }
}

void handle_write_chunk(shared_ptr<ClientData> client_data, const boost::system::error_code &error) {
    if(error) {
        print_log("handle_write_chunk error", error);
        return;
    }
    serve_chunk(client_data);
}

void handle_write_headers(shared_ptr<ClientData> client_data,
                          shared_ptr<string> headers,
                          const boost::system::error_code &error);

void serve_headers(shared_ptr<ClientData> client_data, shared_ptr<string> headers) {
    boost::asio::async_write(*(client_data->socket),
                             boost::asio::buffer(headers->data(), headers->length()),
                             boost::bind(handle_write_headers,
                                         client_data,
                                         headers,
                                         boost::asio::placeholders::error));
}

void handle_write_headers(shared_ptr<ClientData> client_data,
                          shared_ptr<string> headers,
                          const boost::system::error_code &error) {
    if(error) {
        print_log("handle_write_headers error", error);
        return;
    }
    serve_chunk(client_data);
}

bool real_path(string full_path, string &dest) {
    char *real_path = realpath(full_path.data(), NULL);
    if(real_path == NULL) {
        if((errno & (EACCES | ELOOP | ENAMETOOLONG | ENOENT | ENOTDIR)) != 0) {
            return false;
        }
        throw std::runtime_error("real_path failed");
    }
    dest = real_path;
    free(real_path);
    return true;
}

string PROTOCOL_STR = "HTTP/1.0";
string DELIMITER = "\r\n";

string STATUS_OK = "200 OK";
string STATUS_NOT_FOUND = "404 NOT FOUND";

string make_headers(string status_code) {
    std::ostringstream stream;
    stream << PROTOCOL_STR << ' ' << status_code << ' ' << DELIMITER;
    stream << "Content-Type: text/html" << DELIMITER;
    stream << DELIMITER;
    string header = stream.str();
    return header;
}

string NOT_FOUND_HTML = "/home/box/final/404.html";

void serve_uri(shared_ptr<tcp::socket> socket, string uri) {
    string path;
    string status = STATUS_OK;
    bool not_found = !real_path(config::DOCUMENT_ROOT + uri, path);
    ClientData *client_data;
    if(!not_found) {
        client_data = new ClientData(socket, path);
        if (!client_data->is_file_ok()) {
            print_log("could not open file, serving 404 page", "uri:" + uri);
            not_found = true;
        }
    } else {
        print_log("real_path failed, serving 404 page", "uri:" + uri);
    }

    if(not_found) {
        client_data = new ClientData(socket, NOT_FOUND_HTML);
        status = STATUS_NOT_FOUND;
        if(!client_data->is_file_ok()) {
            throw std::runtime_error("could not open not_found_html");
        }
    }

    shared_ptr<ClientData> client_data_sptr(client_data);
    print_log("serve_uri", "responding");
    shared_ptr<string> headers {new string(make_headers(STATUS_OK))};
    serve_headers(client_data_sptr, headers);
}
