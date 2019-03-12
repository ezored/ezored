#include "SimpleStringHelper.hpp"

#include <memory>
#include <algorithm>
#include <cstdarg>

namespace ezored { namespace helpers {

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

} }