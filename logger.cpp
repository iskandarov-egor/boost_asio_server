#include "logger.h"

template<typename T>
void print_log(std::string tag, T obj) {
#ifdef DEBUG
    std::cout << "[LOG] " << tag << ": " << obj << std::endl;
#endif
}
