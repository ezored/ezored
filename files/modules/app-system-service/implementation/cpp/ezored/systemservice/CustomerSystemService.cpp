#include "ezored/systemservice/CustomerSystemService.hpp"
#include "ezored/core/ApplicationCore.hpp"
#include "ezored/core/ApplicationCoreImpl.hpp"
#include "ezored/helper/CustomerHelper.hpp"
#include "ezored/helper/EZRCustomerHelper.hpp"
#include "ezored/helper/ResponseHelper.hpp"
#include "ezored/systemservice/CustomerSystemServiceLoginData.hpp"

#include "ezored/net/http/HttpClient.hpp"
#include "ezored/net/http/HttpHeader.hpp"
#include "ezored/net/http/HttpMethod.hpp"
#include "ezored/net/http/HttpRequest.hpp"
#include "ezored/net/http/HttpRequestParam.hpp"
#include "ezored/net/http/HttpResponse.hpp"

namespace ezored
{
namespace systemservice
{

using namespace ezored::helper;
using namespace ezored::core;
using namespace ezored::net::http;

CustomerSystemServiceLoginData CustomerSystemService::login(const std::string &username, const std::string &password)
{
    auto application = std::static_pointer_cast<ApplicationCoreImpl>(ApplicationCore::shared());

    auto httpHeaders = application->getDefaultHttpRequestHeaders();
    httpHeaders.push_back(HttpHeader{"Content-Type", "application/x-www-form-urlencoded"});

    auto httpParams = application->getDefaultHttpRequestParams();
    httpParams.push_back(HttpRequestParam{"username", username});
    httpParams.push_back(HttpRequestParam{"password", password});

    auto httpURL = "https://raw.githubusercontent.com/ezored/ezored.github.io/main/extras/http-test/login-success.json";

    if (username != "demo" || password != "demo")
    {
        httpURL = "https://raw.githubusercontent.com/ezored/ezored.github.io/main/extras/http-test/login-error.json";
    }

    auto httpRequest = HttpRequest{httpURL, HttpMethod::METHOD_GET, httpParams, httpHeaders, ""};
    auto httpResponse = HttpClient::shared()->doRequest(httpRequest);

    auto response = ResponseHelper::fromHttpResponse(httpResponse);
    auto customer = EZRCustomerHelper::fromHttpResponse(httpResponse);
    auto data = CustomerSystemServiceLoginData{response, customer};

    if (response.success)
    {
        CustomerHelper::onCustomerLogin(customer);
    }

    return data;
}

} // namespace systemservice
} // namespace ezored
