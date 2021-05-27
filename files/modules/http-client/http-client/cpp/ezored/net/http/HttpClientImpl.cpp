#include "HttpClientImpl.hpp"
#include <iostream>

namespace ezored
{
namespace net
{
namespace http
{

std::shared_ptr<HttpClientImpl> HttpClientImpl::instance = nullptr;

HttpClientImpl::HttpClientImpl()
{
    ps = nullptr;
    logger = nullptr;
}

std::shared_ptr<HttpClient> HttpClient::shared()
{
    return HttpClientImpl::internalSharedInstance();
}

std::shared_ptr<HttpClientImpl> HttpClientImpl::internalSharedInstance()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<HttpClientImpl>();
    }

    return instance;
}

void HttpClientImpl::setPlatformService(const std::shared_ptr<HttpClientPlatformService> &ps)
{
    this->ps = ps;
}

std::shared_ptr<HttpClientPlatformService> HttpClientImpl::getPlatformService()
{
    return ps;
}

bool HttpClientImpl::hasPlatformService()
{
    return (ps != nullptr);
}

void HttpClientImpl::setLogger(const std::shared_ptr<HttpClientLogger> &logger)
{
    this->logger = logger;
}

std::shared_ptr<HttpClientLogger> HttpClientImpl::getLogger()
{
    return logger;
}

bool HttpClientImpl::hasLogger()
{
    return (logger != nullptr);
}

HttpResponse HttpClientImpl::doRequest(const HttpRequest &request)
{
    if (ps != nullptr)
    {
        if (hasLogger())
        {
            logger->onRequest(request);
        }

        auto response = ps->doRequest(request);

        if (hasLogger())
        {
            logger->onResponse(request, response);
        }

        return response;
    }

    return HttpResponse(0, "", "", std::vector<HttpHeader>{});
}

} // namespace http
} // namespace net
} // namespace ezored
