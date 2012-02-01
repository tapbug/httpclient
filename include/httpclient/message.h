
#ifndef HTTPCLIENT_MESSAGE_H
#define HTTPCLIENT_MESSAGE_H

#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <httpclient/error.h>

namespace HTTPClient {

class Message_t {
friend class HTTPClient_t;
public:
    typedef std::map<std::string, std::string> HeaderMap_t;

    Message_t();

    ~Message_t();

    HeaderMap_t getHeaders() const;

    template<class T_t>
    void setHeader(const std::string &name,
                   const T_t &value)
    {
        headers[name] = boost::lexical_cast<std::string>(value);
    }

    template<class T_t>
    T_t getHeader(const std::string &name) const
    {
        HeaderMap_t::iterator iheaders(headers.find(name));
        if (iheaders == headers.end()) {
            throw Error_t("Header %s doesn't exist", name.c_str());
        }
        return boost::lexical_cast<T_t>(iheaders->second);
    }

    template<class T_t>
    T_t getHeader(const std::string &name,
                  const T_t &defaultValue) const
    {
        HeaderMap_t::iterator iheaders(headers.find(name));
        if (iheaders == headers.end()) {
            return defaultValue;
        }
        return boost::lexical_cast<T_t>(iheaders->second);
    }

    void setData(const std::string &data);

    std::string getData() const;

protected:
    HeaderMap_t headers;
    std::string data;
};

} // namespace HTTPClient

#endif // HTTPCLIENT_MESSAGE_H
