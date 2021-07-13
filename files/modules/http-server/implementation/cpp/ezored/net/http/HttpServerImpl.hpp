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

    std::shared_ptr<SimpleHttpServer> getServer();

    HttpServerConfig getConfig() override;

    void start() override;

    void stop() override;

    void waitForTermination() override;

private:
    static std::shared_ptr<HttpServerImpl> instance;

    std::shared_ptr<SimpleHttpServer> server;
    std::shared_ptr<HttpServerConfig> serverConfig;
};

} // namespace http
} // namespace net
} // namespace ezored
