// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include <cstdint>
#include <string>

namespace ezored { namespace data {

class SharedDataPlatformService {
public:
    virtual ~SharedDataPlatformService() {}

    virtual void setString(const std::string & groupName, const std::string & key, const std::string & value) = 0;

    virtual void setInteger(const std::string & groupName, const std::string & key, int32_t value) = 0;

    virtual void setLong(const std::string & groupName, const std::string & key, int64_t value) = 0;

    virtual void setBool(const std::string & groupName, const std::string & key, bool value) = 0;

    virtual void setFloat(const std::string & groupName, const std::string & key, float value) = 0;

    virtual void setDouble(const std::string & groupName, const std::string & key, double value) = 0;

    virtual std::string getString(const std::string & groupName, const std::string & key) = 0;

    virtual int32_t getInteger(const std::string & groupName, const std::string & key) = 0;

    virtual int64_t getLong(const std::string & groupName, const std::string & key) = 0;

    virtual bool getBool(const std::string & groupName, const std::string & key) = 0;

    virtual float getFloat(const std::string & groupName, const std::string & key) = 0;

    virtual double getDouble(const std::string & groupName, const std::string & key) = 0;

    virtual std::string getStringWithDefaultValue(const std::string & groupName, const std::string & key, const std::string & defaultValue) = 0;

    virtual int32_t getIntegerWithDefaultValue(const std::string & groupName, const std::string & key, int32_t defaultValue) = 0;

    virtual int64_t getLongWithDefaultValue(const std::string & groupName, const std::string & key, int64_t defaultValue) = 0;

    virtual bool getBoolWithDefaultValue(const std::string & groupName, const std::string & key, bool defaultValue) = 0;

    virtual float getFloatWithDefaultValue(const std::string & groupName, const std::string & key, float defaultValue) = 0;

    virtual double getDoubleWithDefaultValue(const std::string & groupName, const std::string & key, double defaultValue) = 0;

    virtual bool has(const std::string & groupName, const std::string & key) = 0;

    virtual void remove(const std::string & groupName, const std::string & key) = 0;

    virtual void clear(const std::string & groupName) = 0;
};

} }  // namespace ezored::data
