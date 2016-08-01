#include <string>
#include <stdexcept>
#include "http.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include "logger.h"

using namespace std;

string PROTOCOL_STR = "HTTP/1.0";
string static DELIMITER = "\r\n";

const char *STATUS_STRINGS[] = {"200 OK", "404 NOT FOUND"};
const char *CONTENT_TYPE_STRINGS[] = {"text/plain; charset=utf-8", "text/html; charset=utf-8", "image/png", "image/jpeg"};

string make_headers(StatusCode status_code, ContentType content_type) {
    std::ostringstream stream;
    stream << PROTOCOL_STR << ' ' << STATUS_STRINGS[status_code] << ' ' << DELIMITER;
    stream << "Content-Type: " << CONTENT_TYPE_STRINGS[content_type] << DELIMITER;
    stream << DELIMITER;
    string header = stream.str();
    print_log("response header", header);
    return header;
}

bool extract_uri(string &line, string &dest) {
    string LEFT { "GET " };
    string protocols[] = { "HTTP/1.0", "HTTP/1.1" };
    string PROTOCOL = protocols[0]; // todo
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

#include <unordered_map>

const unordered_map<string, ContentType> mime_map = {
    {".txt", TEXT_PLAIN},
    {".html", TEXT_HTML},
    {".png", IMAGE_PNG},
    {".jpg", IMAGE_JPEG},
    {".jpeg", IMAGE_JPEG}
};

ContentType content_type_of(string &filename) {
    string file_extension  = boost::filesystem::extension(filename);
    auto ret = mime_map.find(file_extension);
    if(ret == mime_map.end()) {
        return TEXT_PLAIN;
    }
    return ret->second;
}
