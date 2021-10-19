#include "ezored/net/http/controller/HttpServerTodoController.hpp"

#include "ezored/domain/Todo.hpp"
#include "ezored/helper/ResponseHelper.hpp"
#include "ezored/json/JsonMapping.hpp"
#include "ezored/net/http/helper/HttpServerHelper.hpp"
#include "ezored/time/DateTime.hpp"
#include "ezored/util/Logger.hpp"

#include "ezored/repository/TodoRepository.hpp"

#include "Poco/URI.h"

using namespace ezored::time;
using namespace ezored::helper;
using namespace ezored::repository;
using namespace ezored::util;
using namespace ezored::net::http::helper;

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
    else if (uri.getPath() == "/todo/create" && request.getMethod() == "POST")
    {
        actionTodoCreate(request, response);
        return true;
    }
    else if (uri.getPath() == "/todo/update" && request.getMethod() == "POST")
    {
        actionTodoUpdate(request, response);
        return true;
    }
    else if (uri.getPath() == "/todo/delete" && request.getMethod() == "POST")
    {
        actionTodoDelete(request, response);
        return true;
    }
    else if (uri.getPath() == "/todo/done-by-id" && request.getMethod() == "POST")
    {
        actionTodoDoneById(request, response);
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

    auto list = TodoRepository::findAllOrderByCreatedAtDesc();

    nlohmann::json json = resp;
    json["data"]["list"] = list;

    responseStream << json;
}

void HttpServerTodoController::actionTodoCreate(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream &responseStream = response.send();

    auto resp = ResponseHelper::create();

    try
    {
        auto rjson = nlohmann::json::parse(HttpServerHelper::getRequestContent(request));

        if (rjson != nullptr)
        {
            auto todo = Todo{
                0,
                rjson["title"].get<std::string>(),
                rjson["body"].get<std::string>(),
                rjson["data"].get<std::unordered_map<std::string, std::string>>(),
                rjson["done"].get<bool>(),
                rjson["createdAt"].get<std::chrono::system_clock::time_point>(),
                rjson["updatedAt"].get<std::chrono::system_clock::time_point>(),
            };

            todo.createdAt = DateTime::getCurrentDateTime();
            todo.updatedAt = DateTime::getCurrentDateTime();

            todo.id = TodoRepository::insert(todo);

            if (todo.id > 0)
            {
                todo = TodoRepository::findById(todo.id);

                resp.success = true;
                resp.message = "created";

                nlohmann::json json = resp;

                json["data"]["todo"] = todo;

                responseStream << json;

                return;
            }
        }
    }
    catch (std::exception &e)
    {
        Logger::e("[HttpServerTodoController : actionTodoCreate] Error: " + std::string(e.what()));
    }

    nlohmann::json json = resp;
    responseStream << json;
}

void HttpServerTodoController::actionTodoUpdate(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream &responseStream = response.send();

    auto resp = ResponseHelper::create();

    try
    {
        auto rjson = nlohmann::json::parse(HttpServerHelper::getRequestContent(request));

        if (rjson != nullptr)
        {
            auto todo = Todo{
                rjson["id"].get<int64_t>(),
                rjson["title"].get<std::string>(),
                rjson["body"].get<std::string>(),
                rjson["data"].get<std::unordered_map<std::string, std::string>>(),
                rjson["done"].get<bool>(),
                rjson["createdAt"].get<std::chrono::system_clock::time_point>(),
                rjson["updatedAt"].get<std::chrono::system_clock::time_point>(),
            };

            todo.createdAt = DateTime::getCurrentDateTime();
            todo.updatedAt = DateTime::getCurrentDateTime();

            auto rows = TodoRepository::update(todo.id, todo);

            if (rows > 0)
            {
                todo = TodoRepository::findById(todo.id);

                resp.success = true;
                resp.message = "updated";

                nlohmann::json json = resp;

                json["data"]["todo"] = todo;

                responseStream << json;

                return;
            }
        }
    }
    catch (std::exception &e)
    {
        Logger::e("[HttpServerTodoController : actionTodoUpdate] Error: " + std::string(e.what()));
    }

    nlohmann::json json = resp;
    responseStream << json;
}

void HttpServerTodoController::actionTodoDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream &responseStream = response.send();

    auto resp = ResponseHelper::create();

    try
    {
        auto rjson = nlohmann::json::parse(HttpServerHelper::getRequestContent(request));

        if (rjson != nullptr)
        {
            auto paramId = rjson["id"].get<int64_t>();

            auto result = TodoRepository::removeById(paramId);

            if (result)
            {
                resp.success = true;
                resp.message = "deleted";

                nlohmann::json json = resp;
                responseStream << json;

                return;
            }
        }
    }
    catch (std::exception &e)
    {
        Logger::e("[HttpServerTodoController : actionTodoDelete] Error: " + std::string(e.what()));
    }

    nlohmann::json json = resp;
    responseStream << json;
}

void HttpServerTodoController::actionTodoDoneById(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream &responseStream = response.send();

    auto resp = ResponseHelper::create();

    try
    {
        auto rjson = nlohmann::json::parse(HttpServerHelper::getRequestContent(request));

        if (rjson != nullptr)
        {
            auto paramId = rjson["id"].get<int64_t>();
            auto paramDone = rjson["done"].get<bool>();

            auto result = TodoRepository::setDoneById(paramId, paramDone);

            if (result)
            {
                auto todo = TodoRepository::findById(paramId);

                resp.success = true;
                resp.message = "updated";

                nlohmann::json json = resp;

                json["data"]["todo"] = todo;

                responseStream << json;

                return;
            }
        }
    }
    catch (std::exception &e)
    {
        Logger::e("[HttpServerTodoController : actionTodoDoneById] Error: " + std::string(e.what()));
    }

    nlohmann::json json = resp;
    responseStream << json;
}

} // namespace controller
} // namespace http
} // namespace net
} // namespace ezored
