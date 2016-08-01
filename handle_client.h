#ifndef SERVER_H
#define SERVER_H

namespace client_handler {
    struct Config {
        string DOCUMENT_ROOT;
        string HTML_404;
        int FILE_CHUNK_SIZE;
    };
}
void handle_client(shared_ptr<tcp::socket> socket, client_handler::Config config);

#endif // SERVER_H

