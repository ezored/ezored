#include "EZRCustomerHelper.hpp"

#include "ezored/core/ApplicationCore.hpp"
#include "ezored/enumerator/CustomerStatusEnum.hpp"
#include "ezored/helper/SharedDataHelper.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace ezored
{
namespace helper
{

using namespace ezored::core;
using namespace ezored::enumerator;

bool CustomerHelper::isLogged()
{
    auto application = ApplicationCore::shared();
    auto customer = application->getCustomer();

    if (customer.token.length() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string CustomerHelper::getToken()
{
    return ApplicationCore::shared()->getCustomer().token;
}

Customer EZRCustomerHelper::fromJson(const rapidjson::Value &json)
{
    auto customer = CustomerHelper::create();

    if (!json.IsNull())
    {
        if (json.IsObject())
        {
            {
                // id
                if (json.HasMember("id"))
                {
                    const rapidjson::Value &value = json["id"];

                    if (value.IsString())
                    {
                        customer.id = std::stoll(value.GetString());
                    }
                    else if (value.IsInt64())
                    {
                        customer.id = value.GetInt64();
                    }
                }
            }
            {
                // name
                if (json.HasMember("name"))
                {
                    const rapidjson::Value &value = json["name"];

                    if (value.IsString())
                    {
                        customer.name = value.GetString();
                    }
                }
            }
            {
                // token
                if (json.HasMember("token"))
                {
                    const rapidjson::Value &value = json["token"];

                    if (value.IsString())
                    {
                        customer.token = value.GetString();
                    }
                }
            }
            {
                // status
                if (json.HasMember("status"))
                {
                    const rapidjson::Value &value = json["status"];

                    if (value.IsInt())
                    {
                        auto status = value.GetInt();

                        if (status == static_cast<int>(CustomerStatusEnum::ACTIVE))
                        {
                            customer.status = CustomerStatusEnum::ACTIVE;
                        }
                        else if (status == static_cast<int>(CustomerStatusEnum::INACTIVE))
                        {
                            customer.status = CustomerStatusEnum::INACTIVE;
                        }
                    }
                }
            }
        }
    }

    return customer;
}

std::string EZRCustomerHelper::toJson(const Customer &customer)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    // customer data
    writer.StartObject();

    writer.Key("id");
    writer.Int64(customer.id);

    writer.Key("name");
    writer.String(customer.name.c_str());

    writer.Key("token");
    writer.String(customer.token.c_str());

    writer.Key("status");
    writer.Int(static_cast<int>(customer.status));

    // end: customer data
    writer.EndObject();

    auto json = buffer.GetString();
    return json;
}

Customer EZRCustomerHelper::fromHttpResponse(const HttpResponse httpResponse)
{
    rapidjson::Document json;
    json.Parse(httpResponse.body.c_str());

    if (json.IsObject() && json.HasMember("data"))
    {
        const rapidjson::Value &dataArgs = json["data"];

        if (!dataArgs.IsNull() && dataArgs.HasMember("customer"))
        {
            const rapidjson::Value &customerArgs = dataArgs["customer"];
            return fromJson(customerArgs);
        }
    }

    return create();
}

Customer CustomerHelper::create()
{
    return Customer{0, "", "", CustomerStatusEnum::INACTIVE};
}

void CustomerHelper::onCustomerLogin(const Customer &customer)
{
    ApplicationCore::shared()->setCustomer(customer);
    SharedDataHelper::storeCustomer();
}

} // namespace helper
} // namespace ezored
