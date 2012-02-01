
#include <httpclient/httpclient.h>
#include <httpclient/error.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <iostream>

namespace HTTPClient {

HTTPClient_t::HTTPClient_t(int timeout)
  : curl(0),
    timeout(timeout)
{
    curl = curl_easy_init();
    if (!curl) {
        throw Error_t("Can't initialise CURL library");
    }
}

HTTPClient_t::~HTTPClient_t()
{
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

Response_t HTTPClient_t::operator()(const Request_t &request)
{
    curl_easy_reset(curl);

    Response_t response;

    setOpt(CURLOPT_WRITEFUNCTION, HTTPClient_t::writeFunction);
    setOpt(CURLOPT_WRITEDATA, reinterpret_cast<void*>(&response));
    setOpt(CURLOPT_HEADERFUNCTION, HTTPClient_t::writeHeaderFunction);
    setOpt(CURLOPT_WRITEHEADER, &response);
    setOpt(CURLOPT_NOSIGNAL, 1L);
    setOpt(CURLOPT_NOPROGRESS, 1L);
    setOpt(CURLOPT_URL, request.url.c_str());
    if (request.method == Request_t::POST) {
        setOpt(CURLOPT_POST, 1L);
        if (!request.data.empty()) {
            setOpt(CURLOPT_POSTFIELDS, request.data.data());
            setOpt(CURLOPT_POSTFIELDSIZE, request.data.size());
        }
    }
    setOpt(CURLOPT_TIMEOUT_MS, timeout);

    struct curl_slist *headers(0);
    for (std::map<std::string, std::string>::const_iterator iheaders(request.headers.begin()) ;
         iheaders != request.headers.end() ;
         ++iheaders) {

        headers = curl_slist_append(headers, (iheaders->first + ": " + iheaders->second).c_str());
    }
    setOpt(CURLOPT_HTTPHEADER, headers);


    CURLcode res(curl_easy_perform(curl));
    if (res) {
        throw Error_t("Can't download %s: %s",
            request.url.c_str(), curl_easy_strerror(res));
    }

    return response;
}

size_t HTTPClient_t::writeFunction(const void *buffer, const size_t size, const size_t count, Response_t *response)
{
    size_t res(size*count);
    response->write(std::string(reinterpret_cast<const char*>(buffer), res));
    response->state = Response_t::DATA;
    return res;
}

size_t HTTPClient_t::writeHeaderFunction(const void *buffer, const size_t size, const size_t count, Response_t *response)
{
    size_t res(size*count);

    if (response->state >= Response_t::DATA) {
        return res;
    }

    size_t lineSize(res);
    for (size_t i(0) ; i < lineSize ; ++i) {
        if (reinterpret_cast<const char*>(buffer)[i] == '\r'
            || reinterpret_cast<const char*>(buffer)[i] == '\n') {

            lineSize = i;
            break;
        }
    }

    std::string line(reinterpret_cast<const char*>(buffer), lineSize);

    if (response->state == Response_t::INIT) {
        size_t pos(line.find(" "));
        if (pos == std::string::npos) {
            throw Error_t("Bad response line %s", line.c_str());
        }
        std::string proto(line.substr(0, pos));
        if (proto != "HTTP/1.0" && proto != "HTTP/1.1") {
            throw Error_t("Bad response line %s", line.c_str());
        }
        std::string rest(line.substr(pos + 1));
        pos = rest.find(" ");
        if (pos == std::string::npos) {
            throw Error_t("Bad response line %s", line.c_str());
        }
        response->status = static_cast<Response_t::Status_t>(
            boost::lexical_cast<int>(rest.substr(0, pos)));
        response->state = Response_t::HEADERS;
    } else if (!line.empty()) {
        size_t pos(line.find(":"));
        if (pos == std::string::npos) {
            throw Error_t("Bad header line %s", line.c_str());
        }
        response->setHeader(line.substr(0, pos), line.substr(pos + 1));
    }

    //std::cout << line << std::endl;
    return res;
}

} // namespace HTTPClient
