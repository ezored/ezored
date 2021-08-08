#pragma once

#include "ezored/net/http/HttpServerConfig.hpp"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace ezored
{
namespace net
{
namespace http
{

class SimpleHttpServer : public Poco::Util::ServerApplication
{
public:
    SimpleHttpServer(const std::shared_ptr<HttpServerConfig> &config);
    virtual ~SimpleHttpServer();

    static std::shared_ptr<SimpleHttpServer> create(const std::shared_ptr<HttpServerConfig> &config);
    void start();
    void stop();
    void waitForTermination();
    int32_t getSocketPort();
    std::string getSocketHost();
    bool isSocketSecure();

private:
    std::shared_ptr<Poco::Net::HTTPServer> server;
};

} // namespace http
} // namespace net
} // namespace ezored
