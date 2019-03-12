#pragma once

#include "ezored/helpers/CustomerHelper.hpp"
#include "ezored/domain/Customer.hpp"
#include "rapidjson/document.h"
#include <ezored/net/http/HttpResponse.hpp>

#include <string>

namespace ezored { namespace helpers {

using namespace domain;
using namespace ezored::net::http;

class EZRCustomerHelper: public CustomerHelper {
public:
    virtual ~EZRCustomerHelper() {}

    static Customer fromJson(const rapidjson::Value& json);
    static std::string toJson(const Customer& customer);
    static Customer fromHttpResponse(const HttpResponse httpResponse);
};

} }
