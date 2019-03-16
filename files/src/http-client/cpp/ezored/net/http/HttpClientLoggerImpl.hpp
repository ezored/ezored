#pragma once

#include "ezored/net/http/HttpClientLogger.hpp"

namespace ezored
{
namespace net
{
namespace http
{

class HttpClientLoggerImpl : public HttpClientLogger
{
public:
    void onRequest(const HttpRequest &request) override;
    void onResponse(const HttpRequest &request, const HttpResponse &response) override;
};

} // namespace http
} // namespace net
} // namespace ezored