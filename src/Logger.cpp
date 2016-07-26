#include "Logger.h"

Logger::Logger() : sout(std::cout), serr(std::cerr) {

}

void Logger::out(const char *message) {
    sout << message;
}

void Logger::err(const char *message) {
    serr << message;
}
