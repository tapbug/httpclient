
#include <iostream>
#include <httpclient/httpclient.h>
#include <httpclient/request.h>

int main(int argc, char **argv)
{
    HTTPClient::HTTPClient_t httpClient(100);
    HTTPClient::Request_t request("http://eressea.cz/");
    request.setHeader("User-Agent", "HTTPClient 0.0.1");

    HTTPClient::Response_t response(httpClient(request));

    std::cout << response.getData().size() << std::endl;

    return 0;
}
