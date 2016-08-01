#include "async_chunk_sender.h"
#include "logger.h"
#include <stdexcept>

int provide(std::ifstream *fstream, int chunk_size, char *buffer, char **buf_dest, int *buf_size_dest) {
    int count = fstream->readsome(buffer, chunk_size);
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

void serve_file(string path, shared_ptr<tcp::socket> sock, int file_chunk_size) {
    std::ifstream *fstream = new std::ifstream(path.c_str(), std::ios::in | std::ios::binary);
    fstream->exceptions ( ifstream::failbit | ifstream::badbit );
    if(*fstream) {
        char *buffer = new char [file_chunk_size];
        print_log("starting serving file", path);
        start_sending_chunks(sock, boost::bind(provide, fstream, file_chunk_size, buffer, _1, _2));
    } else {
        throw std::runtime_error { "fstream open failed" };
    }
}
