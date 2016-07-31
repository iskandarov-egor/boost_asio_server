#include "config.h"
#include <stdexcept>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
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



unordered_map<string, string*> string_map = {
    {"port", &PORT},
    {"document_root", &DOCUMENT_ROOT},
    {"host", &HOST},
    {"html_404", &HTML_404}
};

unordered_map<string, int*> int_map = {
    {"file_chunk_size", &FILE_CHUNK_SIZE}
};

void store_line(string &key, string &value) {
   if(string_map.find(key) != string_map.end()) {
        *(string_map[key]) = value;
    } else if(int_map.find(key) != int_map.end()) {
        *(int_map[key]) = stoi(value);
    } else {
        cout << "unrecognized config option: " << key << endl;
    }
}

void load_config_file(string filename) {
    ifstream file { filename };

    std::string line;
    while( std::getline(file, line) ) {
      std::istringstream is_line(line);
      std::string key;
      if( std::getline(is_line, key, '=') )
      {
        std::string value;
        if( std::getline(is_line, value) )
          store_line(key, value);
      }
    }
}

}
