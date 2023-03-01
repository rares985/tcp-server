#ifndef LOGGER_H_
#define LOGGER_H_

#include <memory.h>
#include <cstdio>
#include <cstdarg>
#include <pthread.h> // TODO: Mutexes for multi-threading
#include <iostream>

class Logger
{
private:
    char *buffer_;
    const char *ctx_id_;
    std::uint16_t bufsiz_;

    int vformat(const char *format, va_list args);

public:
    Logger(uint16_t bufsiz, const char *ctx_id);

    // Logger(const Logger &other) = delete;
    // Logger(Logger &&other) = delete;

    // Logger &operator=(Logger &other) = delete;
    // Logger &operator=(Logger &&other) = delete;

    ~Logger();

    // void critical(const char *format, ...);
    // void error(const char *format, ...);
    // void warning(const char *format, ...);
    void information(const char *format, ...);
    // void verbose(const char *format, ...);
};

#endif /* LOGGER_H_ */