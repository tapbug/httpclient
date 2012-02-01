
#ifndef HTTPCLIENT_HTTPCLIENT_H
#define HTTPCLIENT_HTTPCLIENT_H

#include <string>
#include <curl/curl.h>
#include <httpclient/request.h>
#include <httpclient/response.h>

namespace HTTPClient {

class HTTPClient_t {
public:
    HTTPClient_t(int timeout = 5000);

    ~HTTPClient_t();

    Response_t operator()(const Request_t &request);

private:
    template<class T_t>
    void setOpt(const CURLoption name, T_t value)
    {
        CURLcode res(curl_easy_setopt(curl, name, value));
        if (res) {
            throw Error_t(-res, "Can't set CURL option: %s", curl_easy_strerror(res));
        }
    }

    static size_t writeFunction(const void *buffer, const size_t size, const size_t count, Response_t *response);

    static size_t writeHeaderFunction(const void *buffer, const size_t size, const size_t count, Response_t *response);

    CURL *curl;
    int timeout;
};

} // namespace HTTPClient

#endif // HTTPCLIENT_HTTPCLIENT_H
