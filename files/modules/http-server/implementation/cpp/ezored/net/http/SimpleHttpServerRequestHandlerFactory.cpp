#include "ezored/net/http/SimpleHttpServerRequestHandlerFactory.hpp"
#include "ezored/net/http/SimpleHttpServerRequestHandler.hpp"

#include "ezored/util/Logger.hpp"

namespace ezored
{
namespace net
{

namespace http
{

using namespace ezored::net::http;
using namespace ezored::util;

SimpleHttpServerRequestHandlerFactory::SimpleHttpServerRequestHandlerFactory(const std::shared_ptr<HttpServerConfig> config)
{
    serverConfig = config;
}

Poco::Net::HTTPRequestHandler *SimpleHttpServerRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    return new SimpleHttpServerRequestHandler{serverConfig};
}

} // namespace http
} // namespace net
} // namespace ezored
