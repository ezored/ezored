#pragma once

#include "ezored/net/http/HttpClientPlatformService.hpp"
#include <string>

namespace ezored
{
namespace net
{
namespace http
{

class SimpleHttpClientPlatformService : public HttpClientPlatformService
{
public:
    HttpResponse doRequest(const HttpRequest &request) override;

private:
    std::string getMethodFromRequest(const HttpRequest &request);
};

} // namespace http
} // namespace net
} // namespace ezored
