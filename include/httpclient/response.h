
#ifndef HTTPCLIENT_RESPONSE_H
#define HTTPCLIENT_RESPONSE_H

#include <string>
#include <httpclient/message.h>

namespace HTTPClient {

class Response_t : public Message_t {
friend class HTTPClient_t;
public:
    enum Status_t {
        CONTINUE = 100,
        SWITCHING_PROTOCOLS = 101,
        OK = 200,
        CREATED = 201,
        ACCEPTED = 202,
        NONAUTHORITATIVE = 203,
        NOCONTENT = 204,
        RESETCONTENT = 205,
        PARTIALCONTENT = 206,
        MULTIPLECHOICES = 300,
        MOVEDPERMANENTLY = 301,
        FOUND = 302,
        SEEOTHER = 303,
        NOTMODIFIED = 304,
        USEPROXY = 305,
        RESERVED1 = 306,
        TEMPORARYREDIRECT = 307,
        BADREQUEST = 400,
        UNAUTHORIZED = 401,
        PAYMENTREQUIRED = 402,
        FORBIDDEN = 403,
        NOTFOUND = 404,
        METHODNOTALLOWED = 405,
        NOTACCEPTABLE = 406,
        PROXYAUTHENTICATIONREQUIRED = 407,
        REQUESTTIMEOUT = 408,
        CONFLICT = 409,
        GONE = 410,
        LENGTHREQUIRED = 411,
        PRECONDITIONFAILED = 412,
        REQUESTENTITYTOOLARGE = 413,
        REQUESTURITOOLONG = 414,
        UNSUPPORTEDMEDIATYPE = 415,
        REQUESTRANGENOTSATISFIABLE = 416,
        EXPECTATIONFAILED = 417,
        INTERNALSERVERERROR = 500,
        NOTIMPLEMENTED = 501,
        BADGATEWAY = 502,
        SERVICEUNAVAILABLE = 503,
        GATEWAYTIMEOUT = 504,
        HTTPVERSIONNOTSUPPORTED = 505
    };

    Response_t();

    ~Response_t();

    void write(const std::string &data);

    Status_t getStatus() const;

private:
    enum State_t {
        INIT = 0,
        HEADERS,
        DATA
    };

    State_t state;
    Status_t status;
};

} // namespace HTTPClient

#endif // HTTPCLIENT_RESPONSE_H
