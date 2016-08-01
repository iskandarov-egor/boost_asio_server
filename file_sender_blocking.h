#ifndef FILE_SENDER_BLOCKING_H_INCLUDED
#define FILE_SENDER_BLOCKING_H_INCLUDED

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
void serve_file(string path, shared_ptr<tcp::socket> sock, int file_chunk_size);

#endif // FILE_SENDER_BLOCKING_H_INCLUDED
