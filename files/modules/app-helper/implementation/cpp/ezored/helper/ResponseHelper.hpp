#pragma once

#include "ezored/domain/Response.hpp"
#include "ezored/domain/ResponseError.hpp"

#include "ezored/net/http/HttpResponse.hpp"

namespace ezored
{
namespace helper
{

using namespace domain;
using namespace ezored::net::http;

class ResponseHelper
{
public:
    virtual ~ResponseHelper() {}
    static Response fromHttpResponse(const HttpResponse httpResponse);
    static ResponseError createResponseError();
    static Response create();
};

} // namespace helper
} // namespace ezored
