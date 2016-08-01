#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include "acceptor_loop.hpp"
#include "logger.h"
#include <fstream>
#include "config.h"
#include <unistd.h>
#include "http.h"
#include "validation.h"
#include "file_sender_blocking.h"
#include "handle_client.h"

using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace std;

#include <thread>

struct ServerConfig {
    string HOST;
    string PORT;
    int threads;
    client_handler::Config handler_config;
};

ServerConfig load_server_config(string filename) {
    vector<string> bad_lines;
    unordered_map<string, string> config_map = parse_config_file(filename, &bad_lines);

    for(auto it : bad_lines) {
        cout << "bad line '" << it << "' in config file '" << filename << '\'' << endl;
    }

    ServerConfig config;
    unordered_map<string, string*> string_map = {
        {"port", &config.PORT},
        {"document_root", &config.handler_config.DOCUMENT_ROOT},
        {"host", &config.HOST},
        {"html_404", &config.handler_config.HTML_404}
    };
    unordered_map<string, int*> int_map = {
        {"file_chunk_size", &config.handler_config.FILE_CHUNK_SIZE},
        {"threads", &config.threads}
    };


    for(auto it : string_map) {
        try{
            string key = it.first;
            *(it.second) = config_map.at(key);
            config_map.erase(key);
        } catch (std::out_of_range) {
            cout << it.first << " not found in config file " << '"' << filename << '"' << endl;
        }
    }

    for(auto it : int_map) {
        try{
            string key = it.first;
            *(it.second) = stoi(config_map.at(key));
            config_map.erase(key);
        } catch (std::out_of_range) {
            cout << it.first << " not found in config file " << '"' << filename << '"' << endl;
        }
    }

    for(auto it : config_map) {
        cout << "unrecognized option '" << it.first << "' in config file '" << filename << '\'' << endl;
    }

    if(config.threads < 1) {
        cout << "number of threads out of range, using 1" << endl;
        config.threads = 1;
    }

    return config;
}

#include <boost/function.hpp>

void _main() {
    ServerConfig config = load_server_config("config.txt");
    boost::asio::io_service io_service;

    // endpoint_from_string
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(config.HOST, config.PORT);
    tcp::resolver::iterator iter = resolver.resolve(query);
    tcp::endpoint endpoint = iter->endpoint();

    // register server callbacks in io_service
    register_acceptor_loop(io_service, endpoint,
                           boost::bind(handle_client, _1, config.handler_config));

    cout << "starting at " << config.HOST << ':' << config.PORT << endl;

    thread *threads = new thread[config.threads];
    for(int i = 0; i < config.threads; i++)
        threads[i] = thread{[&io_service](){ io_service.run(); }};

    threads[0].join();
}

int main(int argc, char **argv)
{
    try {
        _main();
    }
    catch (std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }

    return 0;
}

/*
deadline_timer *timer;

void start_timer();

void timeout(const boost::system::error_code &error) {
    if (error)
        return;
    cout << "tick" << endl;
    start_timer();
}

void start_timer() {
    timer->expires_from_now(boost::posix_time::seconds(5));
    timer->async_wait(boost::bind(timeout, boost::asio::placeholders::error));
}
*/
