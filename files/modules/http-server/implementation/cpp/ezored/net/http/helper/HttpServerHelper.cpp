#include "ezored/net/http/helper/HttpServerHelper.hpp"
#include "ezored/net/http/controller/HttpServerTodoController.hpp"

using namespace ezored::net::http::controller;

namespace ezored
{
namespace net
{
namespace http
{
namespace helper
{

std::string HttpServerHelper::getRequestContent(Poco::Net::HTTPServerRequest &request)
{
    auto &stream = request.stream();
    const size_t len = request.getContentLength();
    std::string buffer(len, 0);
    stream.read(buffer.data(), len);

    return buffer;
}

bool HttpServerHelper::process(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    if (HttpServerTodoController::process(request, response))
    {
        return true;
    }

    return false;
}

} // namespace helper
} // namespace http
} // namespace net
} // namespace ezored
