
#ifndef HTTPCLIENT_ERROR_H
#define HTTPCLIENT_ERROR_H

#include <stdexcept>
#include <string>

namespace HTTPClient {

class Error_t : public std::runtime_error {
public:
    Error_t(const char *format, ...);

    Error_t(const int _code, const char *format, ...);

    Error_t(const std::string &message);

    Error_t(const int _code, const std::string &message);

    int code() const;

private:
    const int _code;
};

} // namespace HTTPClient

#endif // HTTPCLIENT_ERROR_H
