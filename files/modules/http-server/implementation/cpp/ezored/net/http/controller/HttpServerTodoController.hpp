#pragma once

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace ezored
{
namespace net
{
namespace http
{
namespace controller
{

class HttpServerTodoController
{
public:
    HttpServerTodoController(){};
    virtual ~HttpServerTodoController(){};
    static bool process(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    static void actionTodoList(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    static void actionTodoCreate(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    static void actionTodoUpdate(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    static void actionTodoDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    static void actionTodoDoneById(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
};

} // namespace controller
} // namespace http
} // namespace net
} // namespace ezored
