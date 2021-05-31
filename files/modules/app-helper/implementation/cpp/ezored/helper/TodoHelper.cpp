#include "ezored/helper/TodoHelper.hpp"
#include "ezored/time/DateTime.hpp"

namespace ezored
{
namespace helper
{

using namespace ezored::domain;
using namespace ezored::time;

Todo TodoHelper::create()
{
    auto data = std::unordered_map<std::string, std::string>();
    return Todo{0, "", "", data, false, DateTime::getCurrentDateTime(), DateTime::getCurrentDateTime()};
}

} // namespace helper
} // namespace ezored
