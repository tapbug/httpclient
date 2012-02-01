
#ifndef HTTPCLIENT_REQUEST_H
#define HTTPCLIENT_REQUEST_H

#include <string>
#include <httpclient/message.h>

namespace HTTPClient {

class Request_t : public Message_t {
friend class HTTPClient_t;
public:
    enum Method_t {
        GET = 0,
        POST
    };

    Request_t(const std::string &url = "",
              const Method_t method = GET);

    ~Request_t();

    void setUrl(const std::string &url);

    void setMethod(const Method_t method);

private:
    std::string url;
    Method_t method;
};

} // namespace HTTPClient

#endif // HTTPCLIENT_REQUEST_H
