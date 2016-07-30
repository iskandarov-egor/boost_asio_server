#ifndef HTTP_REQUEST_PARSER_H_INCLUDED
#define HTTP_REQUEST_PARSER_H_INCLUDED

#include <string>
using namespace std;


bool extract_uri(string &line, string &dest);
string make_headers(string status_code);

#endif // HTTP_REQUEST_PARSER_H_INCLUDED
