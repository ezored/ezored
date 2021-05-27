#include "ezored/helpers/SharedDataHelper.hpp"
#include "ezored/core/ApplicationCore.hpp"
#include "ezored/data/SharedData.hpp"
#include "ezored/domain/Customer.hpp"
#include "ezored/helpers/CustomerHelper.hpp"
#include "ezored/helpers/EZRCustomerHelper.hpp"

#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#include <string>

namespace ezored
{
namespace helpers
{

using namespace ezored::data;
using namespace ezored::domain;
using namespace ezored::core;

void SharedDataHelper::setCustomer(const Customer &value)
{
    auto customerJson = EZRCustomerHelper::toJson(value);

    SharedData::shared()->setString("customer", "data", customerJson);
}

Customer SharedDataHelper::getCustomer()
{
    auto customerJson = SharedData::shared()->getString("customer", "data");

    rapidjson::Document json;
    json.Parse(customerJson.c_str());

    if (json.IsObject())
    {
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
    SharedData::shared()->setBool("demo", "flag", value);
}

bool SharedDataHelper::getDemoFlag()
{
    return SharedData::shared()->getBool("demo", "flag");
}

} // namespace helpers
} // namespace ezored
