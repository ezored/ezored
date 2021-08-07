#include "ezored/net/http/SimpleHttpServerRequestHandler.hpp"

#include "ezored/core/ApplicationCore.hpp"
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

SimpleHttpServerRequestHandler::SimpleHttpServerRequestHandler(const std::shared_ptr<HttpServerConfig> config)
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

    Poco::URI uri(request.getURI());

    // validate route
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

    if (staticPath.isDirectory())
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
        else if (extension == "css" == 0)
        {
            mimeType = "text/css";
        }
        else if (extension == "html" == 0 || extension == "htm" == 0)
        {
            mimeType = "text/html";
        }
        else if (extension == "js" == 0)
        {
            mimeType = "text/javascript";
        }
        else if (extension == "png" == 0)
        {
            mimeType = "image/png";
        }
        else if (extension == "jpg" == 0 || extension == "jpeg" == 0)
        {
            mimeType = "image/jpeg";
        }
        else if (extension == "ico" == 0)
        {
            mimeType = "image/ico";
        }
        else if (extension == "svg" == 0)
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
