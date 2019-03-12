#include "ezored/helpers/SharedDataHelper.hpp"
#include "ezored/helpers/CustomerHelper.hpp"
#include "ezored/helpers/EZRCustomerHelper.hpp"
#include "ezored/data/SharedData.hpp"
#include "ezored/domain/Customer.hpp"
#include "ezored/core/ApplicationCore.hpp"

#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#include <string>

namespace ezored { namespace helpers {

using namespace ezored::data;
using namespace ezored::domain;
using namespace ezored::core;

void SharedDataHelper::setCustomer(const Customer &value)
{
    auto customerJson = EZRCustomerHelper::toJson(value);
    
    SharedData::shared()->start("customer");
    SharedData::shared()->setString("data", customerJson);
    SharedData::shared()->saveAsync();
}

Customer SharedDataHelper::getCustomer()
{
    SharedData::shared()->start("customer");
    auto customerJson = SharedData::shared()->getString("data");
    SharedData::shared()->finish();

    rapidjson::Document json;
    json.Parse(customerJson.c_str());

    if (json.IsObject()) {
        return EZRCustomerHelper::fromJson(json);
    }

    return CustomerHelper::create();
}

void SharedDataHelper::storeCustomer()
{
    setCustomer(ApplicationCore::shared()->getCustomer());
}

void SharedDataHelper::setDemoFlag(bool value)
{
    SharedData::shared()->start("demo");
    SharedData::shared()->setBool("flag", value);
    SharedData::shared()->saveAsync();
}

bool SharedDataHelper::getDemoFlag()
{
    SharedData::shared()->start("demo");
    auto value = SharedData::shared()->getBool("flag");
    SharedData::shared()->finish();
    return value;
}

} }
