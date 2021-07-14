#include "HttpServerTodoController.hpp"

#include "ezored/domain/Todo.hpp"
#include "ezored/helper/ResponseHelper.hpp"
#include "ezored/json/JsonMapping.hpp"
#include "ezored/time/DateTime.hpp"

#include "Poco/URI.h"

using namespace ezored::time;
using namespace ezored::helper;

namespace ezored
{
namespace net
{
namespace http
{
namespace controller
{

bool HttpServerTodoController::process(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    Poco::URI uri(request.getURI());

    if (uri.getPath() == "/todo/list" && request.getMethod() == "GET")
    {
        actionTodoList(request, response);
        return true;
    }

    return false;
}
void HttpServerTodoController::actionTodoList(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream &responseStream = response.send();

    auto resp = ResponseHelper::create();
    resp.success = true;
    resp.message = "list";

    auto todo = Todo{1, "test 1", "test 2", {}, true, DateTime::getCurrentDateTime(), DateTime::getCurrentDateTime()};
    auto list = {todo, todo};

    nlohmann::json json = resp;
    json["data"]["list"] = list;

    responseStream << json;
}

} // namespace controller
} // namespace http
} // namespace net
} // namespace ezored
