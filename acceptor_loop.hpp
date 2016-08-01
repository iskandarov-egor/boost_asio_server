#ifndef ACCEPTOR_LOOP_HPP
#define ACCEPTOR_LOOP_HPP

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <string>

namespace acceptor_loop {
    typedef boost::function<void (std::shared_ptr<boost::asio::ip::tcp::socket> sock)> ClientHandler;
}

void register_acceptor_loop(boost::asio::io_service &io_service,
                            boost::asio::ip::tcp::endpoint &endpoint,
                            acceptor_loop::ClientHandler client_handler);

#endif // ACCEPTOR_LOOP_HPP







