#include "SimpleHttpClientPlatformService.hpp"

#include "ezored/net/http/HttpHeader.hpp"
#include "ezored/net/http/HttpMethod.hpp"
#include "ezored/net/http/HttpRequest.hpp"
#include "ezored/net/http/HttpRequestParam.hpp"
#include "ezored/net/http/HttpResponse.hpp"

#include "Poco/DigestStream.h"
#include "Poco/MD5Engine.h"

#include "Poco/Exception.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Path.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"

#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace ezored
{
namespace net
{
namespace http
{

using namespace ezored::net::http;

HttpResponse SimpleHttpClientPlatformService::doRequest(const HttpRequest &request)
{
    auto response = HttpResponse{0, "", "", {}};

    try
    {
        // prepare session
        Poco::URI uri(request.url);
        Poco::Net::HTTPClientSession *session;

        if (uri.getScheme() == "https")
        {
            const Poco::Net::Context::Ptr context(new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", Poco::Net::Context::VERIFY_NONE, 9, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"));
            session = new Poco::Net::HTTPSClientSession(uri.getHost(), uri.getPort(), context);
        }
        else
        {
            session = new Poco::Net::HTTPClientSession(uri.getHost(), uri.getPort());
        }

        // prepare path
        std::string path(uri.getPathAndQuery());

        if (path.empty())
        {
            path = "/";
        }

        // send request
        Poco::Net::HTTPRequest req(getMethodFromRequest(request), path, Poco::Net::HTTPMessage::HTTP_1_1);

        // set headers here
        for (auto &header : request.headers)
        {
            req.set(header.name, header.value);
        }

        // set the request body
        std::string body;

        if (request.params.size() > 0)
        {
            for (auto &param : request.params)
            {
                if (body.length() > 0)
                {
                    body = body + "&" + param.name + "=" + param.value;
                }
                else
                {
                    body = param.name + "=" + param.value;
                }
            }
        }
        else
        {
            body = request.body;
        }

        req.setContentLength(static_cast<std::streamsize>(body.length()));

        // sends request, returns open stream
        std::ostream &os = session->sendRequest(req);

        // sends the body
        os << body;

        // get response
        Poco::Net::HTTPResponse res;
        std::istream &is = session->receiveResponse(res);
        std::stringstream ss;
        Poco::StreamCopier::copyStream(is, ss);

        response.body = ss.str();
        response.code = res.getStatus();
        response.url = request.url;

        Poco::Net::NameValueCollection::ConstIterator i = res.begin();

        while (i != res.end())
        {
            response.headers.push_back(HttpHeader(i->first, i->second));
            ++i;
        }
    }
    catch (Poco::Exception &ex)
    {
        response.body = ex.displayText();
    }

    return response;
}

std::string SimpleHttpClientPlatformService::getMethodFromRequest(const HttpRequest &request)
{
    switch (request.method)
    {
    case HttpMethod::METHOD_GET:
        return "GET";
        break;
    case HttpMethod::METHOD_POST:
        return "POST";
        break;
    case HttpMethod::METHOD_HEAD:
        return "HEAD";
        break;
    case HttpMethod::METHOD_PUT:
        return "PUT";
        break;
    case HttpMethod::METHOD_DELETE:
        return "DELETE";
        break;
    case HttpMethod::METHOD_PATCH:
        return "PATCH";
        break;
    case HttpMethod::METHOD_CONNECT:
        return "CONNECT";
        break;
    case HttpMethod::METHOD_OPTIONS:
        return "OPTIONS";
        break;
    case HttpMethod::METHOD_TRACE:
        return "TRACE";
        break;
    }

    return "";
}

} // namespace http
} // namespace net
} // namespace ezored
