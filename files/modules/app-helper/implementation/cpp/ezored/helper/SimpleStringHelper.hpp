#pragma once

#include <string>

namespace ezored
{
namespace helper
{

class SimpleStringHelper
{
public:
    virtual ~SimpleStringHelper() {}
    static std::string format(const std::string fmtStr, ...);
};

} // namespace helper
} // namespace ezored
