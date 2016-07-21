#ifndef ACCEPTOR_LOOP_HPP
#define ACCEPTOR_LOOP_HPP

#include <boost/asio.hpp>
#include <string>

namespace acceptor_loop {
    typedef void (*ClientHandler)(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
}

void start_acceptor_loop(boost::asio::io_service &io_service,
                         boost::asio::ip::tcp::endpoint &endpoint,
                         acceptor_loop::ClientHandler client_handler);

#endif // ACCEPTOR_LOOP_HPP







