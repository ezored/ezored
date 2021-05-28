#pragma once

#include "ezored/net/http/HttpClient.hpp"
#include "ezored/net/http/HttpClientLogger.hpp"
#include "ezored/net/http/HttpClientPlatformService.hpp"
#include "ezored/net/http/HttpRequest.hpp"
#include "ezored/net/http/HttpResponse.hpp"

#include <string>

namespace ezored
{
namespace net
{
namespace http
{

class HttpClientImpl : public HttpClient
{
public:
    HttpClientImpl();
    static std::shared_ptr<HttpClientImpl> internalSharedInstance();

    void setPlatformService(const std::shared_ptr<HttpClientPlatformService> &ps) override;
    std::shared_ptr<HttpClientPlatformService> getPlatformService() override;
    bool hasPlatformService() override;

    HttpResponse doRequest(const HttpRequest &request) override;

    void setLogger(const std::shared_ptr<HttpClientLogger> &logger) override;
    std::shared_ptr<HttpClientLogger> getLogger() override;
    bool hasLogger() override;

private:
    static std::shared_ptr<HttpClientImpl> instance;
    std::shared_ptr<HttpClientPlatformService> ps;
    std::shared_ptr<HttpClientLogger> logger;
};

} // namespace http
} // namespace net
} // namespace ezored
