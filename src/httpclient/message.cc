
#include <httpclient/error.h>
#include <httpclient/message.h>

namespace HTTPClient {

Message_t::Message_t()
  : headers(),
    data()
{
}

Message_t::~Message_t()
{
}

Message_t::HeaderMap_t Message_t::getHeaders() const
{
    return headers;
}

void Message_t::setData(const std::string &data)
{
    this->data = data;
}

std::string Message_t::getData() const
{
    return data;
}

} // namespace HTTPClient

