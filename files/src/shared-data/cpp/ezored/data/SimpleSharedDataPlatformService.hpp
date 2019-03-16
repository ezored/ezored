#pragma once

#include "ezored/data/SharedDataPlatformService.hpp"
#include <string>

namespace ezored
{
namespace data
{

class SimpleSharedDataPlatformService : public SharedDataPlatformService
{
public:
    void setString(const std::string &key, const std::string &value) override;
    void setInteger(const std::string &key, int32_t value) override;
    void setLong(const std::string &key, int64_t value) override;
    void setBool(const std::string &key, bool value) override;
    void setFloat(const std::string &key, float value) override;
    void setDouble(const std::string &key, double value) override;

    std::string getString(const std::string &key) override;
    int32_t getInteger(const std::string &key) override;
    int64_t getLong(const std::string &key) override;
    bool getBool(const std::string &key) override;
    float getFloat(const std::string &key) override;
    double getDouble(const std::string &key) override;

    std::string getStringWithDefaultValue(const std::string &key, const std::string &defaultValue) override;
    int32_t getIntegerWithDefaultValue(const std::string &key, int32_t defaultValue) override;
    int64_t getLongWithDefaultValue(const std::string &key, int64_t defaultValue) override;
    bool getBoolWithDefaultValue(const std::string &key, bool defaultValue) override;
    float getFloatWithDefaultValue(const std::string &key, float defaultValue) override;
    double getDoubleWithDefaultValue(const std::string &key, double defaultValue) override;

    bool has(const std::string &key) override;
    void remove(const std::string &key) override;
    void clear() override;
    void save(bool async, bool autoFinish) override;
    void saveAsync() override;
    void saveSync() override;
    void start(const std::string &groupName) override;
    void finish() override;
};

} // namespace data
} // namespace ezored
