
#include <httpclient/response.h>

namespace HTTPClient {

Response_t::Response_t()
  : Message_t(),
    state(INIT)
{
}

Response_t::~Response_t()
{
}

void Response_t::write(const std::string &data)
{
    this->data += data;
    state = DATA;
}

Response_t::Status_t Response_t::getStatus() const
{
    return status;
}

} // namespace HTTPClient

