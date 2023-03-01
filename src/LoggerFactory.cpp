#include "LoggerFactory.h"

static constexpr int kDefaultBufsiz = 128;

Logger &LoggerFactory::CreateLogger(std::uint16_t bufsize, const char *ctx)
{
    auto it = loggers_.find(ctx);
    if (it != loggers_.end())
    {
        (*it->second).information("Logger %s already exists!");
        return (*it->second);
    }

    loggers_[ctx] = std::make_unique<Logger>(bufsize, ctx);

    return *loggers_.at(ctx);
}

Logger &LoggerFactory::GetLogger(const char *ctx)
{
    auto it = loggers_.find(ctx);
    if (it != loggers_.end())
    {
        return (*it->second);
    }

    loggers_[ctx] = std::make_unique<Logger>(kDefaultBufsiz, ctx);
    return *loggers_.at(ctx);
}