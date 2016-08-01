#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include "logger.h"

using namespace std;

static bool real_path(string full_path, string &dest) {
    char *real_path = realpath(full_path.data(), NULL);
    if(real_path == NULL) {
        if((errno & (EACCES | ELOOP | ENAMETOOLONG | ENOENT | ENOTDIR)) != 0) {
            return false;
        }
        throw std::runtime_error("real_path failed");
    }
    dest = real_path;
    free(real_path);
    return true;
}

bool validate_and_normalize_uri(string &uri, string &allowed_subfolder) {
    string path;
    bool valid = real_path(uri, path);
    if(valid) {
        valid = path.find(allowed_subfolder) == 0;
        if(valid) {
            struct stat s;
            if( stat(path.c_str(), &s) == 0 ) {
                // check if directory
                if( S_ISREG(s.st_mode)) {
                    uri = path;
                    return true;
                }
                print_log("validation failed, uri is not a file", uri);
                return false;
            } else {
                print_log("validation failed, stat", uri);
                return false;
            }

        }
        print_log("validation failed, uri is not a subdir of doc root", uri);
        return false;
    }
    print_log("validation failed, realpath false", uri);
    return false;
}
