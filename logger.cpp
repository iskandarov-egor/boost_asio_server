#include "logger.h"
#include <iostream>

Logger::Logger(std::string tag):
    tag_(tag)
{

}





void Logger::log(std::string msg) {
    std::cout << "[LOG] " << tag_ << ": " << msg << std::endl;
}


