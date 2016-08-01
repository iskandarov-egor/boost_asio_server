#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include "logger.h"
#include <fstream>
#include <string>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <stdexcept>
#include <cstring>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>
#include "async_chunk_sender.h"

using namespace std;
using boost::asio::ip::tcp;

void handle_write_chunk(shared_ptr<tcp::socket> sock,
                        ChunkProvider provider, const boost::system::error_code &error);

void serve_chunk(shared_ptr<tcp::socket> sock, ChunkProvider provider) {
    int buf_size;
    char *buf;
    int ret = provider(&buf, &buf_size);
    if(ret) {
        if(buf_size <= 0) {
            throw std::runtime_error("invalid buf size");
        }

        print_log("serving chunk, len ", buf_size);

        boost::asio::async_write(*sock,
                                 boost::asio::buffer(buf, buf_size),
                                 boost::bind(handle_write_chunk,
                                             sock,
                                             provider,
                                             boost::asio::placeholders::error));
    } else {
        print_log("serve_uri", "no more chunks");


    }
}

void handle_write_chunk(shared_ptr<tcp::socket> sock,
                        ChunkProvider provider, const boost::system::error_code &error) {
    if(error) {
        print_log("handle_write_chunk error", error);
        return;
    }
    serve_chunk(sock, provider);
}


void start_sending_chunks(shared_ptr<tcp::socket> sock, ChunkProvider provider) {
    serve_chunk(sock, provider);
}
