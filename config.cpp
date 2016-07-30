#include "config.h"
#include <stdexcept>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

namespace config
{
string PORT = "8989";
string DOCUMENT_ROOT = "/home/name";
string HOST = "0.0.0.0";
string HTML_404 = "404.html";
int FILE_CHUNK_SIZE = 512;


void parse_args(int argc, char **argv) {
    char c;
    while ((c = getopt (argc, argv, "h:p:d:")) != -1) {
        switch (c) {
            case 'h': {
                HOST = optarg;
                break;
            }
            case 'p':
                PORT = optarg;
                break;
            case 'd': {
                DOCUMENT_ROOT = optarg;
                break;
            }
            case '?':
                throw std::runtime_error("getopt error ?");
                break;
            default:
                throw std::runtime_error("getopt error default");
                break;
            }
    }
}
}
