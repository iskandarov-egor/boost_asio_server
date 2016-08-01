#include "config.h"
#include <stdexcept>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>
using namespace std;

bool store_line(string &key,
                string &value,
                unordered_map<string, string*> &string_map) {
   if(string_map.find(key) != string_map.end()) {
        *(string_map[key]) = value;
        return true;
    } else {
        return false;
        cout << "unrecognized config option: " << key << endl;
    }
}


unordered_map<string, string> parse_config_file(string filename,
                                                  vector<string> *bad_lines) {
    unordered_map<string, string> ret;
    ifstream file { filename };

    std::string line;
    while( std::getline(file, line) ) {
        std::istringstream is_line(line);
        std::string key;
        bool success;
        if( success = (bool)std::getline(is_line, key, '=') )
        {
            std::string value;
            if( success = (bool)std::getline(is_line, value) ) {
                ret[key] = value;
            }
        }

        if(!success && bad_lines != nullptr) {
            bad_lines->push_back(line);
        }
    }

    return ret;
}






