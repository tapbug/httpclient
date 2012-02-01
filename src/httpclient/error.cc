
#include <stdarg.h>
#include <stdio.h>

#include <httpclient/error.h>

namespace HTTPClient {

#define ERROR_MESSAGEBUFFERSIZE 65536

#define VARARGSTOSTRING() \
    ({ \
        va_list valist; \
        char messageBuffer[ERROR_MESSAGEBUFFERSIZE]; \
        va_start(valist, format); \
        vsnprintf(messageBuffer, ERROR_MESSAGEBUFFERSIZE, format, valist); \
        va_end(valist); \
        messageBuffer; \
    })

Error_t::Error_t(const char *format, ...)
  : std::runtime_error(VARARGSTOSTRING()),
    _code(0)
{
}

Error_t::Error_t(const int _code, const char *format, ...)
  : std::runtime_error(VARARGSTOSTRING()),
    _code(_code)
{
}

Error_t::Error_t(const std::string &message)
  : std::runtime_error(message.c_str()),
    _code(0)
{
}

Error_t::Error_t(const int _code, const std::string &message)
  : std::runtime_error(message.c_str()),
    _code(_code)
{
}

int Error_t::code() const
{
    return _code;
}

#undef VARARGSTOSTRING
#undef ERROR_MESSAGEBUFFERSIZE

} // namespace HTTPClient
