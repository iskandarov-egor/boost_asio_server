#ifndef FILE_SERVING_H
#define FILE_SERVING_H

#include <boost/asio.hpp>
#include <string>

void serve_uri(std::shared_ptr<boost::asio::ip::tcp::socket> socket, std::string uri);

#endif // FILE_SERVING_H

