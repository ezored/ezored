#include "SimpleHttpServerRequestHandler.hpp"

#include "ezored/core/ApplicationCore.hpp"
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
using namespace ezored::util;

SimpleHttpServerRequestHandler::SimpleHttpServerRequestHandler(const std::shared_ptr<HttpServerConfig> config)
{
    serverConfig = config;
}

void SimpleHttpServerRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    // log request
    if (ApplicationCore::shared()->getInitializationData().debug)
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] New request for Host: " + request.getHost() + ", Method: " + request.getMethod() + ", URI: " + request.getURI());
    }

    std::string lastModifiedHeader = request.get("If-Modified-Since", "");
    Poco::URI uri(request.getURI());
    std::string staticPathname = serverConfig->staticPath;

    // validate static path
    if (staticPathname.empty())
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] Error: Static path was not defined");

        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.send();
        return;
    }

    // create full path
    Poco::Path staticPath(staticPathname);

    std::vector<std::string> uriPathSegments;
    uri.getPathSegments(uriPathSegments);

    for (auto &segment : uriPathSegments)
    {
        staticPath.append(segment);
    }

    if (staticPath.isDirectory())
    {
        staticPath.append("index.html");
    }

    Poco::File staticFile(staticPath);

    // serve file
    if (staticFile.exists())
    {
        Logger::d("[SimpleHttpServerRequestHandler : handleRequest] File: " + staticPath.toString());

        std::string mimeType;

        if (staticPath.getExtension().compare("gif") == 0)
        {
            mimeType = "image/gif";
        }
        else if (staticPath.getExtension().compare("css") == 0)
        {
            mimeType = "text/css";
        }
        else if (staticPath.getExtension().compare("html") == 0 || staticPath.getExtension().compare("htm") == 0)
        {
            mimeType = "text/html";
        }
        else if (staticPath.getExtension().compare("js") == 0)
        {
            mimeType = "text/javascript";
        }
        else if (staticPath.getExtension().compare("png") == 0)
        {
            mimeType = "image/png";
        }
        else if (staticPath.getExtension().compare("jpg") == 0 || staticPath.getExtension().compare("jpeg") == 0)
        {
            mimeType = "image/jpeg";
        }
        else if (staticPath.getExtension().compare("ico") == 0)
        {
            mimeType = "image/ico";
        }
        else if (staticPath.getExtension().compare("svg") == 0)
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
