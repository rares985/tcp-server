#ifndef LOGGER_FACTORY_H_
#define LOGGER_FACTORY_H_

#include <map>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>

#include "Logger.h"

class LoggerFactory
{
    static LoggerFactory &GetInstance()
    {
        static LoggerFactory instance;
        return instance;
    }

private:
    LoggerFactory() {}
    ~LoggerFactory()
    {
        loggers_.clear();
    }

public:
    LoggerFactory(const LoggerFactory &) = delete;
    LoggerFactory(const LoggerFactory &&) = delete;
    LoggerFactory &operator=(const LoggerFactory &) = delete;
    LoggerFactory &operator=(const LoggerFactory &&) = delete;

private:
    std::map<const char *, std::unique_ptr<Logger>> loggers_;

public:
    Logger &CreateLogger(std::uint16_t bufsize, const char *ctx);
    Logger &GetLogger(const char *context);
};

#endif /* LOGGER_FACTORY_H_ */