#ifndef ASYNC_CHUNK_SENDER_H_INCLUDED
#define ASYNC_CHUNK_SENDER_H_INCLUDED

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
#include "config.h"
#include <cstring>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>
#include <boost/function.hpp>

using namespace std;
using boost::asio::ip::tcp;

typedef boost::function<int (char** buf_ptr, int* buf_size_ptr)> ChunkProvider;
void start_sending_chunks(shared_ptr<tcp::socket> sock, ChunkProvider provider);

#endif // ASYNC_CHUNK_SENDER_H_INCLUDED
