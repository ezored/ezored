#include "ezored/systemservices/CustomerSystemService.hpp"
#include "ezored/core/ApplicationCore.hpp"
#include "ezored/core/ApplicationCoreImpl.hpp"
#include "ezored/helpers/CustomerHelper.hpp"
#include "ezored/helpers/EZRCustomerHelper.hpp"
#include "ezored/helpers/ResponseHelper.hpp"
#include "ezored/systemservices/CustomerSystemServiceLoginData.hpp"

#include "ezored/net/http/HttpClient.hpp"
#include "ezored/net/http/HttpHeader.hpp"
#include "ezored/net/http/HttpMethod.hpp"
#include "ezored/net/http/HttpRequest.hpp"
#include "ezored/net/http/HttpRequestParam.hpp"
#include "ezored/net/http/HttpResponse.hpp"

namespace ezored
{
namespace systemservices
{

using namespace ezored::helpers;
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

    auto httpURL = "https://public.ezored.com/http-test/login-ok.json";

    if (username != "demo" || password != "demo")
    {
        httpURL = "https://public.ezored.com/http-test/login-error.json";
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

} // namespace systemservices
} // namespace ezored
