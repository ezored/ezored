#include "ezored/core/ApplicationCore.hpp"

#include "ezored/util/Logger.hpp"
#include "ezored/util/LoggerLevel.hpp"
#include "ezored/util/SimpleLoggerPlatformService.hpp"

#include "ezored/net/http/HttpClient.hpp"
#include "ezored/net/http/HttpClientLoggerImpl.hpp"
#include "ezored/net/http/HttpRequest.hpp"
#include "ezored/net/http/HttpResponse.hpp"
#include "ezored/net/http/SimpleHttpClientPlatformService.hpp"

#include "ezored/helpers/StringHelper.hpp"
#include "ezored/io/FileHelper.hpp"
#include "ezored/time/DateTime.hpp"

#include "ezored/helpers/CustomerHelper.hpp"
#include "ezored/helpers/EnvironmentHelper.hpp"
#include "ezored/helpers/TodoHelper.hpp"

#include "ezored/data/SharedData.hpp"
#include "ezored/data/SimpleSharedDataPlatformService.hpp"

#include "ezored/domain/DeviceData.hpp"
#include "ezored/domain/InitializationData.hpp"
#include "ezored/domain/Todo.hpp"

#include "ezored/dataservices/TodoDataService.hpp"

#include "ezored/systemservices/CustomerSystemService.hpp"
#include "ezored/systemservices/CustomerSystemServiceLoginData.hpp"

#include "Poco/File.h"
#include "Poco/Path.h"

#include <iostream>
#include <memory>

using namespace ezored::util;
using namespace ezored::net::http;
using namespace ezored::time;
using namespace ezored::helpers;
using namespace ezored::io;
using namespace ezored::data;

using namespace ezored::domain;
using namespace ezored::core;
using namespace ezored::dataservices;
using namespace ezored::systemservices;
using namespace ezored::helpers;

int main(int argc, char **argv)
{
    // platform services
    Logger::shared()->setPlatformService(std::make_shared<SimpleLoggerPlatformService>());
    Logger::shared()->setLevel(LoggerLevel::VERBOSE);

    HttpClient::shared()->setPlatformService(std::make_shared<SimpleHttpClientPlatformService>());
    SharedData::shared()->setPlatformService(std::make_shared<SimpleSharedDataPlatformService>());

    // application core
    auto homeDir = Poco::Path::home() + "ezored";
    Poco::File(homeDir).createDirectory();

    auto initializationData = InitializationData{"com.ezored.sample", "ezored", homeDir, 0, true};
    auto deviceData = DeviceData{"", "", "", "", "", "", "", "", "", 0, 0, 0, "", "", "", ""};

    ApplicationCore::shared()->initialize(initializationData, deviceData);

    // get initialized customer is stored before
    {
        auto customer = ApplicationCore::shared()->getCustomer();
        std::cout << "Current customer: " << customer.id << " - " << customer.name << " - " << customer.token << std::endl;
        std::cout << "Current customer is logged: " << CustomerHelper::isLogged() << std::endl;
        std::cout << "Current customer token: " << CustomerHelper::getToken() << std::endl;
    }

    // clear and add TODO items to database
    {
        TodoDataService::truncate();

        // todo 1
        auto todo1 = TodoHelper::create();
        todo1.title = "Title 1";
        todo1.body = "Body 1";
        todo1.done = false;
        todo1.data["key1"] = "value1";

        todo1.id = TodoDataService::add(todo1);

        todo1.done = true;
        TodoDataService::add(todo1);

        TodoDataService::setDoneById(todo1.id, false);

        // todo 2
        auto todo2 = TodoHelper::create();
        todo2.title = "Title 2";
        todo2.body = "Body 2";
        todo2.done = false;

        todo2.id = TodoDataService::add(todo2);

        todo2.data["key1"] = "value1";
        TodoDataService::add(todo2);

        TodoDataService::setDoneById(todo2.id, true);
    }

    // get TODO items from database
    {
        auto list = TodoDataService::findAllOrderByCreatedAtDesc();

        for (auto &item : list)
        {
            std::cout << "Todo: " << item.title << std::endl;
        }
    }

    // login error
    {
        auto data = CustomerSystemService::login("demo-error", "demo-error");
        std::cout << "Customer system service login: " << data.response.message << std::endl;

        if (data.response.success)
        {
            std::cout << "Customer system service login: OK" << std::endl;
            std::cout << "Customer system service login customer / ID:" << data.customer.id << " / Name: " << data.customer.name << " / Token: " << data.customer.token << " / Status: " << static_cast<int>(data.customer.status) << std::endl;
        }
        else
        {
            std::cout << "Customer system service login: FAIL" << std::endl;
            std::cout << "Customer system service login error: " << data.response.error.message << std::endl;
        }
    }

    // login success
    {
        auto data = CustomerSystemService::login("demo", "demo");
        std::cout << "Customer system service login: " << data.response.message << std::endl;

        if (data.response.success)
        {
            std::cout << "Customer system service login: OK" << std::endl;
            std::cout << "Customer system service login customer / ID:" << data.customer.id << " / Name: " << data.customer.name << " / Token: " << data.customer.token << " / Status: " << static_cast<int>(data.customer.status) << std::endl;
        }
        else
        {
            std::cout << "Customer system service login: FAIL" << std::endl;
            std::cout << "Customer system service login error: " << data.response.error.message << std::endl;
        }
    }

    // show logged user
    {
        auto customer = ApplicationCore::shared()->getCustomer();
        std::cout << "Current customer: " << customer.id << " - " << customer.name << " - " << customer.token << std::endl;
        std::cout << "Current customer is logged: " << CustomerHelper::isLogged() << std::endl;
        std::cout << "Current customer token: " << CustomerHelper::getToken() << std::endl;
    }

    // post http request
    auto httpRequest = HttpRequest("http://httpbin.org/post", HttpMethod::METHOD_POST, {}, {}, "");
    auto httpResponse = HttpClient::shared()->doRequest(httpRequest);
    std::cout << "Response: " << httpResponse.body << std::endl;

    // secret key store internal
    auto secret = EnvironmentHelper::getSecretKey();

    std::cout << "SECRET: " << secret << std::endl;
    std::cout << "CURRENT DATETIME UTC: " << DateTime::getCurrentDateTimeAsString() << std::endl;
    std::cout << "STRING TO UPPER: " << StringHelper::toUpper(StringHelper::trim(" ezored ")) << std::endl;

    // file helper
    FileHelper::createDir(FileHelper::join("path1", "path2"));

    // shared data
    SharedData::shared()->start("app");

    if (SharedData::shared()->getBoolWithDefaultValue("first-open", true) == true)
    {
        std::cout << "FIRST OPEN: YES" << std::endl;
        SharedData::shared()->setBool("first-open", false);
        SharedData::shared()->saveAsync();
    }
    else
    {
        std::cout << "FIRST OPEN: NO" << std::endl;
        SharedData::shared()->finish();
    }

    return EXIT_SUCCESS;
}
