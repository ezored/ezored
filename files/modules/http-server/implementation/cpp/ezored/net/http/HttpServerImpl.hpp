#pragma once

#include "ezored/net/http/HttpServer.hpp"
#include "ezored/net/http/HttpServerConfig.hpp"
#include "ezored/net/http/SimpleHttpServer.hpp"

#include <memory>

namespace ezored
{
namespace net
{
namespace http
{

class HttpServerImpl : public HttpServer
{
public:
    HttpServerImpl();
    virtual ~HttpServerImpl() {}

    static std::shared_ptr<HttpServerImpl> internalSharedInstance();

    virtual void initialize(const HttpServerConfig &serverConfig) override;
    virtual HttpServerConfig getConfig() override;
    virtual void start() override;
    virtual void stop() override;
    virtual void waitForTermination() override;
    virtual int32_t getSocketPort() override;
    virtual std::string getSocketHost() override;
    virtual std::string getSocketAddress() override;
    virtual bool isSocketSecure() override;
    virtual bool isRunning() override;

    std::shared_ptr<SimpleHttpServer> getServer();

private:
    static std::shared_ptr<HttpServerImpl> instance;

    std::shared_ptr<SimpleHttpServer> server;
    std::shared_ptr<HttpServerConfig> serverConfig;

    bool running;
};

} // namespace http
} // namespace net
} // namespace ezored
