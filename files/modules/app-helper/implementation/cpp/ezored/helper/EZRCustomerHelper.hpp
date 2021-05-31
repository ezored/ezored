#pragma once

#include "ezored/domain/Customer.hpp"
#include "ezored/helper/CustomerHelper.hpp"
#include "ezored/net/http/HttpResponse.hpp"
#include "rapidjson/document.h"

#include <string>

namespace ezored
{
namespace helper
{

using namespace domain;
using namespace ezored::net::http;

class EZRCustomerHelper : public CustomerHelper
{
public:
    virtual ~EZRCustomerHelper() {}

    static Customer fromJson(const rapidjson::Value &json);
    static std::string toJson(const Customer &customer);
    static Customer fromHttpResponse(const HttpResponse httpResponse);
};

} // namespace helper
} // namespace ezored
