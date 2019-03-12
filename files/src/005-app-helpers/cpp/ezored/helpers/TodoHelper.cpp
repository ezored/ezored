#include "ezored/helpers/TodoHelper.hpp"
#include "ezored/time/DateTime.hpp"

namespace ezored { namespace helpers {

using namespace ezored::domain;
using namespace ezored::time;

Todo TodoHelper::create()
{
    return Todo{0, "", "", {}, false, DateTime::getCurrentDateTime(), DateTime::getCurrentDateTime()};
}

} }
