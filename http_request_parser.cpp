#include <string>
#include <stdexcept>
#include "http_request_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

string PROTOCOL_STR = "HTTP/1.0";
string static DELIMITER = "\r\n";



string make_headers(string status_code) {
    std::ostringstream stream;
    stream << PROTOCOL_STR << ' ' << status_code << ' ' << DELIMITER;
    stream << "Content-Type: text/html" << DELIMITER;
    stream << DELIMITER;
    string header = stream.str();
    return header;
}

bool extract_uri(string &line, string &dest) {
    string LEFT { "GET " };
    string protocols[] = { "HTTP/1.0", "HTTP/1.1" };
    string PROTOCOL = protocols[1];
    static_assert(sizeof(protocols) > 0, "no http protocols specified");

    try {
        if(line.compare(0, LEFT.length(), LEFT) != 0) {
            return false;
        }

        // todo fix

        int protocol_pos = line.find(PROTOCOL.data(), 0, PROTOCOL.length());


        int args_pos = line.find('?');
        int right = (args_pos == string::npos) ? protocol_pos : args_pos;
        if(line.compare(protocol_pos, PROTOCOL.length(), PROTOCOL) != 0) {
            return false;
        }
        dest = line.substr(LEFT.length(), right - LEFT.length());
        // trim trailing spaces
        size_t endpos = dest.find_last_not_of(" \t");
        if( string::npos != endpos ) {
            dest = dest.substr( 0, endpos+1 );
        }
    } catch(std::out_of_range) {
        return false;
    }
    return true;
}
