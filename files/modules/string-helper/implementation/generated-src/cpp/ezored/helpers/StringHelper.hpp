// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from proj.djinni

#pragma once

#include <string>
#include <vector>

namespace ezored
{
namespace helpers
{

class StringHelper
{
public:
    virtual ~StringHelper() {}

    static std::string trim(const std::string &value);

    static std::string leftTrim(const std::string &value);

    static std::string rightTrim(const std::string &value);

    static std::string toLower(const std::string &value);

    static std::string toUpper(const std::string &value);

    static std::vector<std::string> split(const std::string &text, const std::string &sep, bool trimEmpty);
};

} // namespace helpers
} // namespace ezored
