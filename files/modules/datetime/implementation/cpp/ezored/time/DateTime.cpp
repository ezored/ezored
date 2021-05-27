#include "ezored/time/DateTime.hpp"
#include "date/date.h"

#include <chrono>
#include <sstream>

namespace ezored
{
namespace time
{

std::chrono::system_clock::time_point DateTime::getDateTimeFromString(const std::string &value)
{
    std::chrono::system_clock::time_point dt;
    std::stringstream ss{value};
    ss >> date::parse("%F %T", dt);
    return date::floor<std::chrono::seconds>(dt);
}

std::string DateTime::getStringFromDateTime(const std::chrono::system_clock::time_point &value)
{
    return date::format("%F %T", date::floor<std::chrono::seconds>(value));
}

std::string DateTime::getCurrentDateTimeAsString()
{
    auto dt = std::chrono::system_clock::now();
    return date::format("%F %T", date::floor<std::chrono::seconds>(dt));
}

std::chrono::system_clock::time_point DateTime::getCurrentDateTime()
{
    return date::floor<std::chrono::seconds>(std::chrono::system_clock::now());
}

std::chrono::system_clock::time_point DateTime::getDateTimeFromSeconds(int64_t value)
{
    auto dur = std::chrono::seconds(value);
    return std::chrono::time_point<std::chrono::system_clock>(dur);
}

std::chrono::system_clock::time_point DateTime::getDateTimeFromMilliseconds(int64_t value)
{
    auto dur = std::chrono::milliseconds(value);
    return std::chrono::time_point<std::chrono::system_clock>(dur);
}

int64_t DateTime::getTimestampInMillisecondsFromDateTime(const std::chrono::system_clock::time_point &value)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch()).count();
}

int64_t DateTime::getTimestampInSecondsFromDateTime(const std::chrono::system_clock::time_point &value)
{
    return std::chrono::duration_cast<std::chrono::seconds>(value.time_since_epoch()).count();
}

std::string DateTime::getCurrentTimestampInSecondsAsString()
{
    return std::to_string(getCurrentTimestampInSeconds());
}

int64_t DateTime::getCurrentTimestampInSeconds()
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string DateTime::getCurrentTimestampInMillisecondsAsString()
{
    return std::to_string(getCurrentTimestampInMilliseconds());
}

int64_t DateTime::getCurrentTimestampInMilliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

} // namespace time
} // namespace ezored
