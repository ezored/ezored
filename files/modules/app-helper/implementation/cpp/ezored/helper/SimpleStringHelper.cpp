#include "SimpleStringHelper.hpp"

#include <algorithm>
#include <cstdarg>
#include <memory>

#include "asprintf.h"

namespace ezored
{
namespace helper
{

std::string SimpleStringHelper::format(const std::string fmtStr, ...)
{
    va_list ap;
    char *fp = nullptr;
    va_start(ap, fmtStr);
    vasprintf(&fp, fmtStr.c_str(), ap);
    va_end(ap);
    std::unique_ptr<char[]> formatted(fp);

    return std::string(formatted.get());
}

} // namespace helper
} // namespace ezored
