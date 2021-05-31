#include "ezored/helper/StringHelper.hpp"
#include <regex>

namespace ezored
{
namespace helper
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

std::vector<std::string> StringHelper::split(const std::string &text, const std::string &sep, bool trimEmpty)
{
    std::vector<std::string> tokens;

    std::string::size_type pos, lastPos = 0, length = text.length();

    while (lastPos < length + 1)
    {
        pos = text.find_first_of(sep, lastPos);

        if (pos == std::string::npos)
        {
            pos = length;
        }

        if (pos != lastPos || !trimEmpty)
        {
            tokens.push_back(std::string(text.data() + lastPos, pos - lastPos));
        }

        lastPos = pos + 1;
    }

    return tokens;
}

} // namespace helper
} // namespace ezored
