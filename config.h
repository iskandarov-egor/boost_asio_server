#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


unordered_map<string, string> parse_config_file(string filename,
                                                  vector<string> *bad_lines = nullptr);

#endif // CONFIG_H_INCLUDED
