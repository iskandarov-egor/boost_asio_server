#include "async_chunk_sender.h"
#include "config.h"
#include "logger.h"
#include <stdexcept>

int provide(std::ifstream *fstream, char *buffer, char **buf_dest, int *buf_size_dest) {
    int count = fstream->readsome(buffer, config::FILE_CHUNK_SIZE);
    if(count > 0) {
        print_log("sending chunk, size", count);
        *buf_dest = buffer;
        *buf_size_dest = count;
        return true;
    } else {
        print_log("no more chunks", "");
        delete[] buffer;
        delete fstream;
        return false;
    }
}

void serve_file(string path, shared_ptr<tcp::socket> sock) {
    std::ifstream *fstream = new std::ifstream(path.c_str(), std::ios::in | std::ios::binary);
    fstream->exceptions ( ifstream::failbit | ifstream::badbit );
    if(*fstream) {
        char *buffer = new char [config::FILE_CHUNK_SIZE];
        print_log("starting serving file", path);
        start_sending_chunks(sock, boost::bind(provide, fstream, buffer, _1, _2));
    } else {
        throw std::runtime_error { "fstream open failed" };
    }
}
