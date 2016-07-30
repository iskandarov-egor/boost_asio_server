#ifndef HTTP_REQUEST_PARSER_H_INCLUDED
#define HTTP_REQUEST_PARSER_H_INCLUDED

#include <string>
using namespace std;

enum ContentType {
    TEXT_PLAIN = 0,
    TEXT_HTML,
    IMAGE_PNG,
    IMAGE_JPEG
};

enum StatusCode {
    OK = 0,
    NOT_FOUND
};



bool extract_uri(string &line, string &dest);
string make_headers(StatusCode status_code, ContentType content_type);
ContentType content_type_of(string &filename);

#endif // HTTP_REQUEST_PARSER_H_INCLUDED
