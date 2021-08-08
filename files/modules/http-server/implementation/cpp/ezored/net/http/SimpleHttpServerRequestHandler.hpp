#pragma once

#include "ezored/net/http/HttpServerConfig.hpp"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include <memory>
#include <string>

namespace ezored
{
namespace net
{
namespace http
{

class SimpleHttpServerRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    SimpleHttpServerRequestHandler(const std::shared_ptr<HttpServerConfig> &config);
    virtual ~SimpleHttpServerRequestHandler() {}
    virtual void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

private:
    std::shared_ptr<HttpServerConfig> serverConfig;
};

} // namespace http
} // namespace net
} // namespace ezored
