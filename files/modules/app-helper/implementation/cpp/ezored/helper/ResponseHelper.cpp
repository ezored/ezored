#include "ResponseHelper.hpp"

#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#include <string>

namespace ezored
{
namespace helper
{

Response ResponseHelper::fromHttpResponse(const HttpResponse httpResponse)
{
    auto response = domain::Response{false, "", createResponseError(), false};

    rapidjson::Document json;
    json.Parse(httpResponse.body.c_str());

    if (json.IsObject())
    {
        {
            // success
            if (json.HasMember("success"))
            {
                const rapidjson::Value &value = json["success"];

                if (value.IsBool())
                {
                    response.success = value.GetBool();
                }
            }
        }
        {
            // message
            if (json.HasMember("message"))
            {
                const rapidjson::Value &value = json["message"];

                if (value.IsString())
                {
                    response.message = value.GetString();
                }
            }
        }
        {
            // response error
            if (json.HasMember("data"))
            {
                const rapidjson::Value &valueData = json["data"];

                if (!valueData.IsNull() && valueData.IsObject() && valueData.HasMember("errors"))
                {
                    const rapidjson::Value &errorsData = valueData["errors"];

                    if (!errorsData.IsNull() && errorsData.IsArray())
                    {
                        for (auto &errorData : errorsData.GetArray())
                        {
                            if (!errorData.IsNull() && errorData.IsArray())
                            {
                                /**
                                 * In this case errors is:
                                 * "data":{
                                 *     "errors":[
                                 *         [
                                 *             "error-field",
                                 *             ["error-message"]
                                 *         ]
                                 *     ]
                                 * }
                                 */

                                std::string errorField = "";
                                std::string errorMessage = "";

                                auto x = 0;

                                for (auto &errorFieldMessageData : errorData.GetArray())
                                {
                                    if (!errorFieldMessageData.IsNull())
                                    {
                                        if (errorFieldMessageData.IsString())
                                        {
                                            errorField = errorFieldMessageData.GetString();
                                        }
                                        else if (errorFieldMessageData.IsArray())
                                        {
                                            for (auto &errorFieldMessageDataItem : errorFieldMessageData.GetArray())
                                            {
                                                if (!errorFieldMessageDataItem.IsNull() && errorFieldMessageDataItem.IsString())
                                                {
                                                    if (x == 1)
                                                    {
                                                        errorMessage = errorFieldMessageDataItem.GetString();
                                                    }
                                                    else
                                                    {
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    x++;
                                }

                                response.error.field = errorField;
                                response.error.message = errorMessage;
                            }
                        }
                    }
                }
            }
        }
    }

    if (response.error.message.size() > 0)
    {
        response.hasError = true;
    }

    return response;
}

ResponseError ResponseHelper::createResponseError()
{
    return ResponseError{"", ""};
}

Response ResponseHelper::create()
{
    return Response{false, "", createResponseError(), false};
}

} // namespace helper
} // namespace ezored
