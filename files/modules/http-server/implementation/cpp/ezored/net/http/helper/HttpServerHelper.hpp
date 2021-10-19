#pragma once

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include <string>

namespace ezored
{
namespace net
{
namespace http
{
namespace helper
{

class HttpServerHelper
{
public:
    HttpServerHelper(){};
    virtual ~HttpServerHelper(){};
    static std::string getRequestContent(Poco::Net::HTTPServerRequest &request);
    static bool process(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
};

} // namespace helper
} // namespace http
} // namespace net
} // namespace ezored
