#include "ezored/helpers/StringHelper.hpp"
#include <regex>

namespace ezored
{
namespace helpers
{

std::string StringHelper::trim(const std::string &value)
{
    return leftTrim(rightTrim(value));
}

std::string StringHelper::leftTrim(const std::string &value)
{
    static const std::regex lws{"^[[:space:]]*", std::regex_constants::extended};
    return std::regex_replace(value, lws, "");
}

std::string StringHelper::rightTrim(const std::string &value)
{
    static const std::regex tws{"[[:space:]]*$", std::regex_constants::extended};
    return std::regex_replace(value, tws, "");
}

std::string StringHelper::toLower(const std::string &value)
{
    std::string result(value);
    transform(value.begin(), value.end(), result.begin(), ::tolower);
    return result;
}

std::string StringHelper::toUpper(const std::string &value)
{
    std::string result(value);
    transform(value.begin(), value.end(), result.begin(), ::toupper);
    return result;
}

} // namespace helpers
} // namespace ezored
