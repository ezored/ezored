// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace ezored
{
namespace net
{
namespace http
{

struct HttpServerConfig;

class HttpServer
{
public:
    virtual ~HttpServer() {}

    static std::shared_ptr<HttpServer> shared();

    virtual void initialize(const HttpServerConfig &config) = 0;

    virtual HttpServerConfig getConfig() = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void waitForTermination() = 0;

    virtual int32_t getSocketPort() = 0;

    virtual std::string getSocketHost() = 0;

    virtual std::string getSocketAddress() = 0;

    virtual bool isSocketSecure() = 0;
};

} // namespace http
} // namespace net
} // namespace ezored
