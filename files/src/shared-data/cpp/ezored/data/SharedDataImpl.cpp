#include "SharedDataImpl.hpp"

namespace ezored { namespace data {

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

void SharedDataImpl::setPlatformService(const std::shared_ptr<SharedDataPlatformService> & ps) 
{
    this->ps = ps;
}

std::shared_ptr<SharedDataPlatformService> SharedDataImpl::getPlatformService() 
{
    return ps;
}

void SharedDataImpl::setString(const std::string & key, const std::string & value) 
{
    if (ps != nullptr) 
    {
        ps->setString(key, value);
    }
}

void SharedDataImpl::setInteger(const std::string & key, int32_t value) 
{
    if (ps != nullptr) 
    {
        ps->setInteger(key, value);
    }
}

void SharedDataImpl::setLong(const std::string & key, int64_t value) 
{
    if (ps != nullptr) 
    {
        ps->setLong(key, value);
    }
}

void SharedDataImpl::setBool(const std::string & key, bool value) 
{
    if (ps != nullptr) 
    {
        ps->setBool(key, value);
    }
}

void SharedDataImpl::setFloat(const std::string & key, float value) 
{
    if (ps != nullptr) 
    {
        ps->setFloat(key, value);
    }
}
    
void SharedDataImpl::setDouble(const std::string & key, double value) 
{
    if (ps != nullptr) 
    {
        ps->setDouble(key, value);
    }
}

std::string SharedDataImpl::getString(const std::string & key) 
{
    if (ps != nullptr) 
    {
        return ps->getString(key);
    }

    return "";
}
    
int32_t SharedDataImpl::getInteger(const std::string & key) 
{
    if (ps != nullptr) 
    {
        return ps->getInteger(key);
    }

    return 0;
}

int64_t SharedDataImpl::getLong(const std::string & key) 
{
    if (ps != nullptr) 
    {
        return ps->getLong(key);
    }

    return 0;
}
    
bool SharedDataImpl::getBool(const std::string & key) 
{
    if (ps != nullptr) 
    {
        return ps->getBool(key);
    }

    return false;
}

float SharedDataImpl::getFloat(const std::string & key) 
{
    if (ps != nullptr) 
    {
        return ps->getFloat(key);
    }

    return 0.0;
}

double SharedDataImpl::getDouble(const std::string & key) 
{
    if (ps != nullptr) 
    {
        return ps->getDouble(key);
    }

    return 0.0;
}

std::string SharedDataImpl::getStringWithDefaultValue(const std::string &key, const std::string &defaultValue) 
{
    if (ps != nullptr) 
    {
        return ps->getStringWithDefaultValue(key, defaultValue);
    }

    return defaultValue;
}

int32_t SharedDataImpl::getIntegerWithDefaultValue(const std::string &key, int32_t defaultValue) 
{
    if (ps != nullptr) 
    {
        return ps->getIntegerWithDefaultValue(key, defaultValue);
    }

    return defaultValue;
}

int64_t SharedDataImpl::getLongWithDefaultValue(const std::string &key, int64_t defaultValue) 
{
    if (ps != nullptr) 
    {
        return ps->getLongWithDefaultValue(key, defaultValue);
    }

    return defaultValue;
}

bool SharedDataImpl::getBoolWithDefaultValue(const std::string &key, bool defaultValue) 
{
    if (ps != nullptr) 
    {
        return ps->getBoolWithDefaultValue(key, defaultValue);
    }

    return defaultValue;
}

float SharedDataImpl::getFloatWithDefaultValue(const std::string &key, float defaultValue) 
{
    if (ps != nullptr) 
    {
        return ps->getFloatWithDefaultValue(key, defaultValue);
    }

    return defaultValue;
}

double SharedDataImpl::getDoubleWithDefaultValue(const std::string &key, double defaultValue) 
{
    if (ps != nullptr) 
    {
        return ps->getDoubleWithDefaultValue(key, defaultValue);
    }

    return defaultValue;
}

bool SharedDataImpl::has(const std::string &key) 
{
    if (ps != nullptr) 
    {
        return ps->has(key);
    }

    return false;
}

void SharedDataImpl::remove(const std::string &key) 
{
    if (ps != nullptr) 
    {
        ps->remove(key);
    }
}

void SharedDataImpl::clear() 
{
    if (ps != nullptr) 
    {
        ps->clear();
    }
}

bool SharedDataImpl::hasPlatformService() 
{
    return (ps != nullptr);
}

void SharedDataImpl::save(bool async, bool autoFinish) 
{
    if (ps != nullptr) 
    {
        ps->save(async, autoFinish);
    }
}

void SharedDataImpl::start(const std::string & groupName) 
{
    if (ps != nullptr) 
    {
        ps->start(groupName);
    }
}

void SharedDataImpl::finish() 
{
    if (ps != nullptr) 
    {
        ps->finish();
    }
}

void SharedDataImpl::saveAsync() 
{
    if (ps != nullptr) 
    {
        ps->saveAsync();
    }
}

void SharedDataImpl::saveSync() 
{
    if (ps != nullptr) 
    {
        ps->saveSync();
    }
}

}}
