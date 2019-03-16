#pragma once

#include <string>

namespace ezored { namespace helpers {

class SimpleStringHelper {
public:
    virtual ~SimpleStringHelper() {}
    static std::string format(const std::string fmtStr, ...);
};

} }
