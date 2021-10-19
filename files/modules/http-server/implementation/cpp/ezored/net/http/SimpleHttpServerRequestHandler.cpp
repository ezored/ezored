#include "ezored/net/http/SimpleHttpServerRequestHandler.hpp"

#include "ezored/core/ApplicationCore.hpp"
#include "ezored/io/FileHelper.hpp"
#include "ezored/net/http/helper/HttpServerHelper.hpp"
#include "ezored/util/Logger.hpp"

#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/URI.h"

#include <iostream>

namespace ezored
{
namespace net
{

namespace http
{

using namespace ezored::core;
using namespace ezored::net::http;
using namespace ezored::net::http::helper;
using namespace ezored::util;
using namespace ezored::domain;
using namespace ezored::io;

SimpleHttpServerRequestHandler::SimpleHttpServerRequestHandler(const std::shared_ptr<HttpServerConfig> &config)
{
    Logger::d("[SimpleHttpServerRequestHandler : constructor]");
    serverConfig = config;
}

void SimpleHttpServerRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    Logger::d("[SimpleHttpServerRequestHandler : handleRequest]");

    // log request
    if (ApplicationCore::shared()->getInitializationData().debug)
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] New request for Host: " + request.getHost() + ", Method: " + request.getMethod() + ", URI: " + request.getURI() + ", Version: " + request.getVersion() + ", Content-Type: " + request.getContentType() + ", Transfer-Encoding: " + request.getTransferEncoding());
    }

    // add CORS headers
    response.add("Access-Control-Allow-Origin", "*");
    response.add("Access-Control-Allow-Headers", "Accept, Authorization, Cache-Control, Content-Type, DNT, If-Modified-Since, Keep-Alive, Origin, Referer, User-Agent, X-Requested-With");
    response.add("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
    response.add("Access-Control-Allow-Credentials", "true");

    // validate CORS
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS)
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] CORS request");

        response.setContentType("text/plain charset=UTF-8");
        response.add("Access-Control-Max-Age", "3600");
        response.setContentLength(0);
        response.send();

        return;
    }

    // validate route
    Poco::URI uri(request.getURI());

    Logger::d("[SimpleHttpServerRequestHandler : handleRequest] Validating know routes...");

    if (HttpServerHelper::process(request, response))
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] Route is know");
        return;
    }

    Logger::d("[SimpleHttpServerRequestHandler : handleRequest] Route is a static asset");

    std::string serverStaticPath = serverConfig->staticPath;

    // validate static path
    if (serverStaticPath.empty())
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] Error: Static path was not defined");

        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.send();
        return;
    }

    // create full path
    Poco::Path staticPath(serverStaticPath);

    std::vector<std::string> uriPathSegments;
    uri.getPathSegments(uriPathSegments);

    for (auto &segment : uriPathSegments)
    {
        staticPath.append(segment);
    }

    Poco::File staticFile(staticPath);

    if (FileHelper::isDir(staticPath.toString()))
    {
        staticPath.append("index.html");
        staticFile = Poco::File(staticPath);
    }

    // serve file
    if (staticFile.exists())
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] File: " + staticPath.toString());

        std::string mimeType;
        std::string extension = Poco::Path(staticFile.path()).getExtension();

        if (extension == "gif")
        {
            mimeType = "image/gif";
        }
        else if (extension == "css")
        {
            mimeType = "text/css";
        }
        else if (extension == "html" || extension == "htm")
        {
            mimeType = "text/html";
        }
        else if (extension == "js")
        {
            mimeType = "text/javascript";
        }
        else if (extension == "png")
        {
            mimeType = "image/png";
        }
        else if (extension == "jpg" || extension == "jpeg")
        {
            mimeType = "image/jpeg";
        }
        else if (extension == "ico")
        {
            mimeType = "image/ico";
        }
        else if (extension == "svg")
        {
            mimeType = "image/svg";
        }

        try
        {
            response.sendFile(staticPath.toString(), mimeType);
        }
        catch (Poco::FileNotFoundException &)
        {
            Logger::e("[SimpleHttpServerRequestHandler : handleRequest] Can't find file: " + staticPath.toString());
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, ("Can't find file: " + staticPath.toString()));
        }
        catch (Poco::OpenFileException &)
        {
            Logger::e("[SimpleHttpServerRequestHandler : handleRequest] Can't open file: " + staticPath.toString());
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR, ("Can't open file: " + staticPath.toString()));
        }

        return;
    }

    Logger::e("[SimpleHttpServerRequestHandler : handleRequest] Can't find file: " + staticPath.toString());

    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    response.send();
}

} // namespace http
} // namespace net
} // namespace ezored
