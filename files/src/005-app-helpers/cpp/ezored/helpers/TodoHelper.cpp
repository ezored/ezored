#include "ezored/helpers/TodoHelper.hpp"
#include "ezored/time/DateTime.hpp"

namespace ezored { namespace helpers {

using namespace ezored::domain;
using namespace ezored::time;

Todo TodoHelper::create()
{
    auto data = std::unordered_map<std::string, std::string>();
    return Todo{0, "", "", data, false, DateTime::getCurrentDateTime(), DateTime::getCurrentDateTime()};
}

} }
