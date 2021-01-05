#include "SharedDataImpl.hpp"

namespace ezored
{
namespace data
{

std::shared_ptr<SharedDataImpl> SharedDataImpl::instance = nullptr;

SharedDataImpl::SharedDataImpl()
{
    ps = nullptr;
}

std::shared_ptr<SharedData> SharedData::shared()
{
    return SharedDataImpl::internalSharedInstance();
}

std::shared_ptr<SharedDataImpl> SharedDataImpl::internalSharedInstance()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<SharedDataImpl>();
    }

    return instance;
}

void SharedDataImpl::setPlatformService(const std::shared_ptr<SharedDataPlatformService> &ps)
{
    this->ps = ps;
}

std::shared_ptr<SharedDataPlatformService> SharedDataImpl::getPlatformService()
{
    return ps;
}

void SharedDataImpl::setString(const std::string &groupName, const std::string &key, const std::string &value)
{
    if (ps != nullptr)
    {
        ps->setString(groupName, key, value);
    }
}

void SharedDataImpl::setInteger(const std::string &groupName, const std::string &key, int32_t value)
{
    if (ps != nullptr)
    {
        ps->setInteger(groupName, key, value);
    }
}

void SharedDataImpl::setLong(const std::string &groupName, const std::string &key, int64_t value)
{
    if (ps != nullptr)
    {
        ps->setLong(groupName, key, value);
    }
}

void SharedDataImpl::setBool(const std::string &groupName, const std::string &key, bool value)
{
    if (ps != nullptr)
    {
        ps->setBool(groupName, key, value);
    }
}

void SharedDataImpl::setFloat(const std::string &groupName, const std::string &key, float value)
{
    if (ps != nullptr)
    {
        ps->setFloat(groupName, key, value);
    }
}

void SharedDataImpl::setDouble(const std::string &groupName, const std::string &key, double value)
{
    if (ps != nullptr)
    {
        ps->setDouble(groupName, key, value);
    }
}

std::string SharedDataImpl::getString(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        return ps->getString(groupName, key);
    }

    return "";
}

int32_t SharedDataImpl::getInteger(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        return ps->getInteger(groupName, key);
    }

    return 0;
}

int64_t SharedDataImpl::getLong(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        return ps->getLong(groupName, key);
    }

    return 0;
}

bool SharedDataImpl::getBool(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        return ps->getBool(groupName, key);
    }

    return false;
}

float SharedDataImpl::getFloat(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        return ps->getFloat(groupName, key);
    }

    return 0.0;
}

double SharedDataImpl::getDouble(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        return ps->getDouble(groupName, key);
    }

    return 0.0;
}

std::string SharedDataImpl::getStringWithDefaultValue(const std::string &groupName, const std::string &key, const std::string &defaultValue)
{
    if (ps != nullptr)
    {
        return ps->getStringWithDefaultValue(groupName, key, defaultValue);
    }

    return defaultValue;
}

int32_t SharedDataImpl::getIntegerWithDefaultValue(const std::string &groupName, const std::string &key, int32_t defaultValue)
{
    if (ps != nullptr)
    {
        return ps->getIntegerWithDefaultValue(groupName, key, defaultValue);
    }

    return defaultValue;
}

int64_t SharedDataImpl::getLongWithDefaultValue(const std::string &groupName, const std::string &key, int64_t defaultValue)
{
    if (ps != nullptr)
    {
        return ps->getLongWithDefaultValue(groupName, key, defaultValue);
    }

    return defaultValue;
}

bool SharedDataImpl::getBoolWithDefaultValue(const std::string &groupName, const std::string &key, bool defaultValue)
{
    if (ps != nullptr)
    {
        return ps->getBoolWithDefaultValue(groupName, key, defaultValue);
    }

    return defaultValue;
}

float SharedDataImpl::getFloatWithDefaultValue(const std::string &groupName, const std::string &key, float defaultValue)
{
    if (ps != nullptr)
    {
        return ps->getFloatWithDefaultValue(groupName, key, defaultValue);
    }

    return defaultValue;
}

double SharedDataImpl::getDoubleWithDefaultValue(const std::string &groupName, const std::string &key, double defaultValue)
{
    if (ps != nullptr)
    {
        return ps->getDoubleWithDefaultValue(groupName, key, defaultValue);
    }

    return defaultValue;
}

bool SharedDataImpl::has(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        return ps->has(groupName, key);
    }

    return false;
}

void SharedDataImpl::remove(const std::string &groupName, const std::string &key)
{
    if (ps != nullptr)
    {
        ps->remove(groupName, key);
    }
}

void SharedDataImpl::clear(const std::string &groupName)
{
    if (ps != nullptr)
    {
        ps->clear(groupName);
    }
}

bool SharedDataImpl::hasPlatformService()
{
    return (ps != nullptr);
}

} // namespace data
} // namespace ezored
