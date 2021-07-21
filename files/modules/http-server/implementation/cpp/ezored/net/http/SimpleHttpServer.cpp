#include "ezored/net/http/SimpleHttpServer.hpp"
#include "ezored/net/http/SimpleHttpServerRequestHandlerFactory.hpp"

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
    params->setTimeout(15000);

    auto requestHandler = new SimpleHttpServerRequestHandlerFactory{config};

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

int32_t SimpleHttpServer::getSocketPort()
{
    if (server != nullptr)
    {
        return server->socket().address().port();
    }

    return 0;
}

std::string SimpleHttpServer::getSocketHost()
{
    if (server != nullptr)
    {
        return server->socket().address().host().toString();
    }

    return "";
}

bool SimpleHttpServer::isSocketSecure()
{
    if (server != nullptr)
    {
        return server->socket().secure();
    }

    return false;
}

std::shared_ptr<SimpleHttpServer> SimpleHttpServer::create(const std::shared_ptr<HttpServerConfig> config)
{
    return std::make_shared<SimpleHttpServer>(config);
}

} // namespace http
} // namespace net
} // namespace ezored