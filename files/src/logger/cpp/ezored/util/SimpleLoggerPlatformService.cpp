#include "SimpleLoggerPlatformService.hpp"
#include <iostream>

namespace ezored
{
namespace util
{

void SimpleLoggerPlatformService::v(const std::string &message)
{
    std::cout << "[VERBOSE] " << message << std::endl;
}

void SimpleLoggerPlatformService::d(const std::string &message)
{
    std::cout << "[DEBUG] " << message << std::endl;
}

void SimpleLoggerPlatformService::i(const std::string &message)
{
    std::cout << "[INFO] " << message << std::endl;
}

void SimpleLoggerPlatformService::w(const std::string &message)
{
    std::cout << "[WARNING] " << message << std::endl;
}

void SimpleLoggerPlatformService::e(const std::string &message)
{
    std::cout << "[ERROR] " << message << std::endl;
}

void SimpleLoggerPlatformService::setGroup(const std::string &group)
{
    // C++ does not have group support
}

} // namespace util
} // namespace ezored
