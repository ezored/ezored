#include "gtest/gtest.h"

#include "ezored/core/ApplicationCore.hpp"

#include "ezored/util/Logger.hpp"
#include "ezored/util/LoggerLevel.hpp"
#include "ezored/util/SimpleLoggerPlatformService.hpp"

#include "ezored/net/http/HttpClient.hpp"
#include "ezored/net/http/HttpClientLoggerImpl.hpp"
#include "ezored/net/http/HttpRequest.hpp"
#include "ezored/net/http/HttpResponse.hpp"
#include "ezored/net/http/SimpleHttpClientPlatformService.hpp"

#include "ezored/data/SharedData.hpp"
#include "ezored/data/SimpleSharedDataPlatformService.hpp"

#include "ezored/io/FileHelper.hpp"
#include "ezored/io/SimpleFileHelperPlatformService.hpp"

#include "ezored/domain/DeviceData.hpp"
#include "ezored/domain/InitializationData.hpp"

#include <memory>

using namespace ezored::util;
using namespace ezored::net::http;
using namespace ezored::io;
using namespace ezored::data;

using namespace ezored::domain;
using namespace ezored::core;

class InitializationFixture : public ::testing::Test
{
public:
    InitializationFixture()
    {
        // initialization code here
    }

    void SetUp()
    {
        // platform services
        Logger::shared()->setPlatformService(std::make_shared<SimpleLoggerPlatformService>());
        Logger::shared()->setLevel(LoggerLevel::VERBOSE);

        FileHelper::shared()->setPlatformService(std::make_shared<SimpleFileHelperPlatformService>());
        HttpClient::shared()->setPlatformService(std::make_shared<SimpleHttpClientPlatformService>());
        SharedData::shared()->setPlatformService(std::make_shared<SimpleSharedDataPlatformService>());

        // application core
        auto homeDir = FileHelper::join(FileHelper::getHomeDir(), "ezored");
        FileHelper::createDir(homeDir);

        auto initializationData = InitializationData{"com.ezored.sample", "ezored", homeDir, 0, true};
        auto deviceData = DeviceData{"", "", "", "", "", "", "", "", "", 0, 0, 0, "", "", "", ""};

        ApplicationCore::shared()->initialize(initializationData, deviceData);

        coreIsInitialized = true;
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~InitializationFixture()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
    bool coreIsInitialized = false;
};
