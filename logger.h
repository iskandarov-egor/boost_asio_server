#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

#define DEBUG

class Logger
{
public:
    Logger(std::string tag);
    void log(std::string msg);
private:
    std::string tag_;
};

template<typename T>
void print_log(std::string tag, T obj) {
#ifdef DEBUG
    std::cout << "[LOG] " << tag << ": " << obj << std::endl;
#endif
}

#endif // LOGGER_H
