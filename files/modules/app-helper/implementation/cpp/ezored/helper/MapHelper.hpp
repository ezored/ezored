#pragma once

#include <string>
#include <unordered_map>

namespace ezored
{
namespace helper
{

class MapHelper
{
public:
    virtual ~MapHelper() {}

    static std::string toJsonString(const std::unordered_map<std::string, std::string> &data);
    static std::unordered_map<std::string, std::string> fromJsonString(const std::string &data);
    static std::string getValue(const std::string &key, const std::unordered_map<std::string, std::string> &data, const std::string &defaultValue);
};

} // namespace helper
} // namespace ezored
