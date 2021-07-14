#include "SimpleHttpServer.hpp"
#include "SimpleHttpServerRequestHandlerFactory.hpp"

#include "ezored/util/Logger.hpp"

namespace ezored
{
namespace net
{

namespace http
{

using namespace ezored::net::http;
using namespace ezored::util;

SimpleHttpServer::SimpleHttpServer(const std::shared_ptr<HttpServerConfig> config)
{
    Poco::Net::HTTPServerParams *params = new Poco::Net::HTTPServerParams();
    params->setMaxQueued(10);
    params->setMaxThreads(1);

    SimpleHttpServerRequestHandlerFactory *requestHandler = new SimpleHttpServerRequestHandlerFactory{config};
    Poco::Net::ServerSocket serverSocket = Poco::Net::ServerSocket{static_cast<Poco::UInt16>(config->port)};
    server = std::make_shared<Poco::Net::HTTPServer>(requestHandler, serverSocket, params);
}

SimpleHttpServer::~SimpleHttpServer()
{
    if (server != nullptr)
    {
        stop();
    }
}

void SimpleHttpServer::start()
{
    if (server != nullptr)
    {
        server->start();
    }
}

void SimpleHttpServer::stop()
{
    if (server != nullptr)
    {
        server->stopAll();
    }
}

void SimpleHttpServer::waitForTermination()
{
    if (server != nullptr)
    {
        waitForTerminationRequest();
    }
}

std::shared_ptr<SimpleHttpServer> SimpleHttpServer::create(const std::shared_ptr<HttpServerConfig> config)
{
    return std::make_shared<SimpleHttpServer>(config);
}

} // namespace http
} // namespace net
} // namespace ezored
