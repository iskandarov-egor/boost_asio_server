#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "acceptor_loop.hpp"
#include <stdexcept>
#include "logger.h"

using namespace acceptor_loop;
using namespace std;
using boost::asio::ip::tcp;
ClientHandler _client_handler;

tcp::acceptor *acceptor = nullptr;

void on_accept(shared_ptr<tcp::socket> client_socket, const boost::system::error_code &err);

void accept_next() {
    print_log("AcceptorLoop", "async accepting");

    shared_ptr<tcp::socket> client_socket_dest(new tcp::socket(acceptor->get_io_service())); // todo unique
    acceptor->async_accept(*client_socket_dest,
        boost::bind(on_accept, client_socket_dest, _1));
}

void register_acceptor_loop(boost::asio::io_service &io_service, tcp::endpoint &endpoint, ClientHandler client_handler) {
    if(acceptor != nullptr)
        throw std::runtime_error("acceptor loop called twice");

    acceptor= new boost::asio::ip::tcp::acceptor(io_service, endpoint);
    _client_handler = client_handler;
    accept_next();
}

void on_accept(shared_ptr<tcp::socket> client_socket, const boost::system::error_code &err) {
    if(err) {
        cout << "AcceptorLoop error: " << err << endl;
        return;
    }
    print_log("AcceptorLoop", "on_accept, calling handler");
    _client_handler(client_socket);
    accept_next();
}
