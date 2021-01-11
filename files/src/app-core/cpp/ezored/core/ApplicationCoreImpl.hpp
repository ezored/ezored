#pragma once

#include "ezored/core/ApplicationCore.hpp"

#include "ezored/domain/DeviceData.hpp"
#include "ezored/domain/InitializationData.hpp"

#include "ezored/net/http/HttpHeader.hpp"
#include "ezored/net/http/HttpRequestParam.hpp"

#include "SQLiteCpp/Database.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ezored
{
namespace core
{

using namespace ezored::domain;
using namespace ezored::net::http;

class ApplicationCoreImpl : public ApplicationCore
{
public:
    ApplicationCoreImpl();
    virtual ~ApplicationCoreImpl() {}

    static std::shared_ptr<ApplicationCoreImpl> internalSharedInstance();

    virtual void initialize(const InitializationData &initializationData, const DeviceData &deviceData) override;

    void initializeDB();
    void initializeHttpClient();
    void initializeHttpLogger();
    void initializeCustomer();

    std::vector<HttpRequestParam> getDefaultHttpRequestParams();
    std::vector<HttpHeader> getDefaultHttpRequestHeaders();
    std::shared_ptr<SQLite::Database> getDB();

    InitializationData getInitializationData() override;
    DeviceData getDeviceData() override;

    Customer getCustomer() override;
    void setCustomer(const Customer &customer) override;

    std::string getVersion() override;

private:
    static std::shared_ptr<ApplicationCoreImpl> instance;
    std::shared_ptr<SQLite::Database> db;

    std::shared_ptr<InitializationData> initializationData;
    std::shared_ptr<DeviceData> deviceData;
    std::shared_ptr<Customer> customer;
};

} // namespace core
} // namespace ezored
