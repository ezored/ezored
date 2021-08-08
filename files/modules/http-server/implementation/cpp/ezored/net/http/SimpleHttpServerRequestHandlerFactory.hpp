#pragma once

#include "ezored/net/http/HttpServerConfig.hpp"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

#include <memory>

namespace ezored
{
namespace net
{
namespace http
{

class SimpleHttpServerRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    SimpleHttpServerRequestHandlerFactory(const std::shared_ptr<HttpServerConfig> &config);
    virtual ~SimpleHttpServerRequestHandlerFactory() {}
    virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

private:
    std::shared_ptr<HttpServerConfig> serverConfig;
};

} // namespace http
} // namespace net
} // namespace ezored
