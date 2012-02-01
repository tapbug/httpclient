
#include <httpclient/request.h>

namespace HTTPClient {

Request_t::Request_t(const std::string &url,
                     const Method_t method)
  : Message_t(),
    url(url),
    method(method)
{
}

Request_t::~Request_t()
{
}

void Request_t::setUrl(const std::string &url)
{
    this->url = url;
}

void Request_t::setMethod(const Method_t method)
{
    this->method = method;
}

} // namespace HTTPClient

