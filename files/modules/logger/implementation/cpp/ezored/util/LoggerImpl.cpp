#include "LoggerImpl.hpp"
#include "ezored/util/LoggerLevel.hpp"

namespace ezored
{
namespace util
{

std::shared_ptr<LoggerImpl> LoggerImpl::instance = nullptr;

LoggerImpl::LoggerImpl()
{
    ps = nullptr;
    level = LoggerLevel::DEBUG;
}

std::shared_ptr<Logger> Logger::shared()
{
    return LoggerImpl::internalSharedInstance();
}

std::shared_ptr<LoggerImpl> LoggerImpl::internalSharedInstance()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<LoggerImpl>();
    }

    return instance;
}

void LoggerImpl::setPlatformService(const std::shared_ptr<LoggerPlatformService> &ps)
{
    this->ps = ps;
}

std::shared_ptr<LoggerPlatformService> LoggerImpl::getPlatformService()
{
    return ps;
}

bool LoggerImpl::hasPlatformService()
{
    return (ps != nullptr);
}

void LoggerImpl::setLevel(LoggerLevel level)
{
    this->level = level;
}

bool LoggerImpl::allowedLevel(LoggerLevel level)
{
    switch (this->level)
    {
    case LoggerLevel::ERROR:
        switch (level)
        {
        case LoggerLevel::ERROR:
            return true;
            break;
        default:
            break;
        }
        break;

    case LoggerLevel::WARNING:
        switch (level)
        {
        case LoggerLevel::ERROR:
        case LoggerLevel::WARNING:
            return true;
            break;
        default:
            break;
        }
        break;

    case LoggerLevel::INFO:
        switch (level)
        {
        case LoggerLevel::ERROR:
        case LoggerLevel::WARNING:
        case LoggerLevel::INFO:
            return true;
            break;
        default:
            break;
        }
        break;

    case LoggerLevel::DEBUG:
        switch (level)
        {
        case LoggerLevel::ERROR:
        case LoggerLevel::WARNING:
        case LoggerLevel::INFO:
        case LoggerLevel::DEBUG:
            return true;
            break;
        default:
            break;
        }
        break;

    case LoggerLevel::VERBOSE:
        return true;
        break;
    default:
        break;
    }

    return false;
}

void Logger::v(const std::string &message)
{
    if (Logger::shared()->getPlatformService() == nullptr)
    {
        return;
    }

    if (!Logger::shared()->allowedLevel(LoggerLevel::VERBOSE))
    {
        return;
    }

    Logger::shared()->getPlatformService()->v(message);
}

void Logger::d(const std::string &message)
{
    if (Logger::shared()->getPlatformService() == nullptr)
    {
        return;
    }

    if (!Logger::shared()->allowedLevel(LoggerLevel::DEBUG))
    {
        return;
    }

    Logger::shared()->getPlatformService()->d(message);
}

void Logger::i(const std::string &message)
{
    if (Logger::shared()->getPlatformService() == nullptr)
    {
        return;
    }

    if (!Logger::shared()->allowedLevel(LoggerLevel::INFO))
    {
        return;
    }

    Logger::shared()->getPlatformService()->i(message);
}

void Logger::w(const std::string &message)
{
    if (Logger::shared()->getPlatformService() == nullptr)
    {
        return;
    }

    if (!Logger::shared()->allowedLevel(LoggerLevel::WARNING))
    {
        return;
    }

    Logger::shared()->getPlatformService()->w(message);
}

void Logger::e(const std::string &message)
{
    if (Logger::shared()->getPlatformService() == nullptr)
    {
        return;
    }

    if (!Logger::shared()->allowedLevel(LoggerLevel::ERROR))
    {
        return;
    }

    Logger::shared()->getPlatformService()->e(message);
}

void Logger::setGroup(const std::string &group)
{
    if (Logger::shared()->getPlatformService() == nullptr)
    {
        return;
    }

    Logger::shared()->getPlatformService()->setGroup(group);
}

} // namespace util
} // namespace ezored
