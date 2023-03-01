#include "Logger.h"

Logger::Logger(std::uint16_t bufsiz, const char *ctx_id) : buffer_{new char[bufsiz]}, ctx_id_{ctx_id}, bufsiz_{bufsiz}
{
}

Logger::~Logger()
{
    delete[] buffer_;
}

int Logger::vformat(const char *format, va_list args)
{
    int ret = -1;

    // TODO: Mutex this.. in case multi-threading is required
    ret = vsnprintf(&buffer_[0], bufsiz_, format, args);
    if (ret < 0)
    {
        std::cout << "Encoding error in vsnprintf...\n";
        return ret;
    }

    if (ret >= bufsiz_)
    {
        std::cout << "Log is too large! Will be truncated\n";
    }
    return ret;
}

void Logger::information(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int rc = vformat(format, args);
    va_end(args);

    if (rc != 0)
    {
        return;
    }
    /* Output buffer to file .. or std */
}