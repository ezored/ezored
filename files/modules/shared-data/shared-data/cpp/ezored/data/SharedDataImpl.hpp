#pragma once

#include "ezored/data/SharedData.hpp"
#include "ezored/data/SharedDataPlatformService.hpp"

namespace ezored
{
namespace data
{

class SharedDataImpl : public SharedData
{

public:
    SharedDataImpl();
    static std::shared_ptr<SharedDataImpl> internalSharedInstance();

    void setPlatformService(const std::shared_ptr<SharedDataPlatformService> &ps) override;
    std::shared_ptr<SharedDataPlatformService> getPlatformService() override;
    bool hasPlatformService() override;

    void setString(const std::string &groupName, const std::string &key, const std::string &value) override;
    void setInteger(const std::string &groupName, const std::string &key, int32_t value) override;
    void setLong(const std::string &groupName, const std::string &key, int64_t value) override;
    void setBool(const std::string &groupName, const std::string &key, bool value) override;
    void setFloat(const std::string &groupName, const std::string &key, float value) override;
    void setDouble(const std::string &groupName, const std::string &key, double value) override;

    std::string getString(const std::string &groupName, const std::string &key) override;
    int32_t getInteger(const std::string &groupName, const std::string &key) override;
    int64_t getLong(const std::string &groupName, const std::string &key) override;
    bool getBool(const std::string &groupName, const std::string &key) override;
    float getFloat(const std::string &groupName, const std::string &key) override;
    double getDouble(const std::string &groupName, const std::string &key) override;

    std::string getStringWithDefaultValue(const std::string &groupName, const std::string &key, const std::string &defaultValue) override;
    int32_t getIntegerWithDefaultValue(const std::string &groupName, const std::string &key, int32_t defaultValue) override;
    int64_t getLongWithDefaultValue(const std::string &groupName, const std::string &key, int64_t defaultValue) override;
    bool getBoolWithDefaultValue(const std::string &groupName, const std::string &key, bool defaultValue) override;
    float getFloatWithDefaultValue(const std::string &groupName, const std::string &key, float defaultValue) override;
    double getDoubleWithDefaultValue(const std::string &groupName, const std::string &key, double defaultValue) override;

    bool has(const std::string &groupName, const std::string &key) override;
    void remove(const std::string &groupName, const std::string &key) override;
    void clear(const std::string &groupName) override;

private:
    static std::shared_ptr<SharedDataImpl> instance;

    std::shared_ptr<SharedDataPlatformService> ps;
};

} // namespace data
} // namespace ezored
