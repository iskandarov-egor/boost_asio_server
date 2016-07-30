#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include <string>

namespace config
{
    extern std::string PORT;
    extern std::string DOCUMENT_ROOT;
    extern std::string HOST;
    extern int FILE_CHUNK_SIZE;

    void parse_args(int argc, char **argv);
}

#endif // CONFIG_H_INCLUDED
