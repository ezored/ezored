#include "ApplicationCoreImpl.hpp"

#include "ezored/util/Logger.hpp"

#include "ezored/net/http/HttpClient.hpp"
#include "ezored/net/http/HttpClientLoggerImpl.hpp"

#include "ezored/helpers/DatabaseHelper.hpp"
#include "ezored/helpers/SharedDataHelper.hpp"
#include "ezored/helpers/CustomerHelper.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <map>

namespace ezored { namespace core {

using namespace ezored::domain;
using namespace ezored::util;
using namespace ezored::net::http;
using namespace ezored::helpers;

std::shared_ptr<ApplicationCoreImpl> ApplicationCoreImpl::instance = nullptr;

ApplicationCoreImpl::ApplicationCoreImpl()
{
    
}

std::shared_ptr<ApplicationCore> ApplicationCore::shared()
{
    return ApplicationCoreImpl::internalSharedInstance();
}

std::shared_ptr<ApplicationCoreImpl> ApplicationCoreImpl::internalSharedInstance()
{
    if (instance == nullptr) 
    {
        instance = std::make_shared<ApplicationCoreImpl>();
    }

    return instance;
}

void ApplicationCoreImpl::initialize(const InitializationData & initializationData, const DeviceData & deviceData)
{
    Logger::shared()->i("Application initializing...");

    Logger::shared()->i("App ID: " + initializationData.appId);
    Logger::shared()->i("Name: " + initializationData.name);
    Logger::shared()->i("Base path: " + initializationData.basePath);
    
    this->initializationData = std::make_shared<InitializationData>(initializationData);
    this->deviceData = std::make_shared<DeviceData>(deviceData);

    initializeHttpLogger();
    initializeDB();

    Logger::shared()->i("Application initialized");
}

void ApplicationCoreImpl::initializeDB() 
{
    db = DatabaseHelper::initializeDatabase(initializationData->basePath);
    DatabaseHelper::migrateDatabase(db);
    Logger::shared()->i("Database initialized and migrated");
}

void ApplicationCoreImpl::initializeCustomer() 
{
    auto currentCustomer = SharedDataHelper::getCustomer();
    customer = std::make_shared<Customer>(currentCustomer);
    Logger::shared()->i("Customer initialized");
}

void ApplicationCoreImpl::initializeHttpLogger() 
{
    auto loggerPS = std::make_shared<HttpClientLoggerImpl>();
    HttpClient::shared()->setLogger(loggerPS);
}

InitializationData ApplicationCoreImpl::getInitializationData()
{
    return *initializationData;
}

DeviceData ApplicationCoreImpl::getDeviceData() 
{
    return *deviceData;
}

Customer ApplicationCoreImpl::getCustomer() 
{
    if (customer)
    {
        return *customer;
    }

    return CustomerHelper::create();
}

void ApplicationCoreImpl::setCustomer(const Customer & customer) 
{
    this->customer = std::make_shared<Customer>(customer);
}

std::vector<HttpRequestParam> ApplicationCoreImpl::getDefaultHttpRequestParams() 
{
    std::vector<HttpRequestParam> params = std::vector<HttpRequestParam>{};
    return params;
}

std::vector<HttpHeader> ApplicationCoreImpl::getDefaultHttpRequestHeaders() 
{
    std::vector<HttpHeader> headers = std::vector<HttpHeader>{};
    headers.push_back(HttpHeader{"User-Agent", "Ezored Http Client"});
    return headers;
}

std::shared_ptr<SQLite::Database> ApplicationCoreImpl::getDB() 
{
    return db;
}

/*
std::string ApplicationCoreImpl::doPostRequest(std::string url, std::string body, std::map<std::string, std::string> headers)
{
    v1:
    auto httpRequest = ezored::net::http::HttpRequest(url, ezored::net::http::HttpMethod::POST, {}, {}, "");
    auto httpResponse = ezored::net::http::HttpClient::shared()->doRequest(httpRequest);
    return httpResponse.body;

    v2:
    try
    {
        // prepare session
        Poco::URI uri(url);
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
        Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        req.setContentType("application/x-www-form-urlencoded");
        
        // set headers here
        for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++) 
        {
            req.set(it->first, it->second);
        }
        
        // set the request body
        req.setContentLength( body.length() );
        
        // sends request, returns open stream
        std::ostream& os = session->sendRequest(req);

        // sends the body
        os << body;  
        
        // get response
        Poco::Net::HTTPResponse res;        
        std::istream &is = session->receiveResponse(res);
        std::stringstream ss;
        Poco::StreamCopier::copyStream(is, ss);
        
        return ss.str();
    }
    catch (Poco::Exception &ex)
    {
        return ex.displayText();
    }

    return "";
}
*/

} }
