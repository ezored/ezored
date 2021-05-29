#include "SimpleSharedDataPlatformService.hpp"
#include "ezored/helper/StringHelper.hpp"
#include "ezored/io/FileHelper.hpp"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace ezored::io;
using namespace ezored::helper;

namespace ezored
{
namespace data
{

std::string SimpleSharedDataPlatformService::baseDir = "ezored";

void SimpleSharedDataPlatformService::setString(const std::string &groupName, const std::string &key, const std::string &value)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        rapidjson::Value &jsonValue = json[key.c_str()];
        jsonValue.SetString(rapidjson::StringRef(value.c_str()));
    }
    else
    {
        auto jsonKey = rapidjson::Value(key.c_str(), json.GetAllocator());
        rapidjson::Value jsonValue;
        jsonValue.SetString(rapidjson::StringRef(value.c_str()));

        json.AddMember(jsonKey, jsonValue, json.GetAllocator());
    }

    save(json, groupName);
}

void SimpleSharedDataPlatformService::setInteger(const std::string &groupName, const std::string &key, int32_t value)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        rapidjson::Value &jsonValue = json[key.c_str()];
        jsonValue.SetInt(value);
    }
    else
    {
        auto jsonKey = rapidjson::Value(key.c_str(), json.GetAllocator());
        rapidjson::Value jsonValue;
        jsonValue.SetInt(value);

        json.AddMember(jsonKey, jsonValue, json.GetAllocator());
    }

    save(json, groupName);
}

void SimpleSharedDataPlatformService::setLong(const std::string &groupName, const std::string &key, int64_t value)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        rapidjson::Value &jsonValue = json[key.c_str()];
        jsonValue.SetInt64(value);
    }
    else
    {
        auto jsonKey = rapidjson::Value(key.c_str(), json.GetAllocator());
        rapidjson::Value jsonValue;
        jsonValue.SetInt64(value);

        json.AddMember(jsonKey, jsonValue, json.GetAllocator());
    }

    save(json, groupName);
}

void SimpleSharedDataPlatformService::setBool(const std::string &groupName, const std::string &key, bool value)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        rapidjson::Value &jsonValue = json[key.c_str()];
        jsonValue.SetBool(value);
    }
    else
    {
        auto jsonKey = rapidjson::Value(key.c_str(), json.GetAllocator());
        rapidjson::Value jsonValue;
        jsonValue.SetBool(value);

        json.AddMember(jsonKey, jsonValue, json.GetAllocator());
    }

    save(json, groupName);
}

void SimpleSharedDataPlatformService::setFloat(const std::string &groupName, const std::string &key, float value)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        rapidjson::Value &jsonValue = json[key.c_str()];
        jsonValue.SetFloat(value);
    }
    else
    {
        auto jsonKey = rapidjson::Value(key.c_str(), json.GetAllocator());
        rapidjson::Value jsonValue;
        jsonValue.SetFloat(value);

        json.AddMember(jsonKey, jsonValue, json.GetAllocator());
    }

    save(json, groupName);
}

void SimpleSharedDataPlatformService::setDouble(const std::string &groupName, const std::string &key, double value)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        rapidjson::Value &jsonValue = json[key.c_str()];
        jsonValue.SetDouble(value);
    }
    else
    {
        auto jsonKey = rapidjson::Value(key.c_str(), json.GetAllocator());
        rapidjson::Value jsonValue;
        jsonValue.SetDouble(value);

        json.AddMember(jsonKey, jsonValue, json.GetAllocator());
    }

    save(json, groupName);
}

std::string SimpleSharedDataPlatformService::getString(const std::string &groupName, const std::string &key)
{
    return getStringWithDefaultValue(groupName, key, "");
}

int32_t SimpleSharedDataPlatformService::getInteger(const std::string &groupName, const std::string &key)
{
    return getIntegerWithDefaultValue(groupName, key, 0);
}

int64_t SimpleSharedDataPlatformService::getLong(const std::string &groupName, const std::string &key)
{
    return getLongWithDefaultValue(groupName, key, 0);
}

bool SimpleSharedDataPlatformService::getBool(const std::string &groupName, const std::string &key)
{
    return getBoolWithDefaultValue(groupName, key, false);
}

float SimpleSharedDataPlatformService::getFloat(const std::string &groupName, const std::string &key)
{
    return getFloatWithDefaultValue(groupName, key, 0);
}

double SimpleSharedDataPlatformService::getDouble(const std::string &groupName, const std::string &key)
{
    return getDoubleWithDefaultValue(groupName, key, 0);
}

std::string SimpleSharedDataPlatformService::getStringWithDefaultValue(const std::string &groupName, const std::string &key, const std::string &defaultValue)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        const rapidjson::Value &value = json[key.c_str()];

        if (value.IsString())
        {
            return value.GetString();
        }
    }

    return defaultValue;
}

int32_t SimpleSharedDataPlatformService::getIntegerWithDefaultValue(const std::string &groupName, const std::string &key, int32_t defaultValue)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        const rapidjson::Value &value = json[key.c_str()];

        if (value.IsInt())
        {
            return value.GetInt();
        }
    }

    return defaultValue;
}

int64_t SimpleSharedDataPlatformService::getLongWithDefaultValue(const std::string &groupName, const std::string &key, int64_t defaultValue)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        const rapidjson::Value &value = json[key.c_str()];

        if (value.IsInt64())
        {
            return value.GetInt64();
        }
    }

    return defaultValue;
}

bool SimpleSharedDataPlatformService::getBoolWithDefaultValue(const std::string &groupName, const std::string &key, bool defaultValue)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        const rapidjson::Value &value = json[key.c_str()];

        if (value.IsBool())
        {
            return value.GetBool();
        }
    }

    return defaultValue;
}

float SimpleSharedDataPlatformService::getFloatWithDefaultValue(const std::string &groupName, const std::string &key, float defaultValue)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        const rapidjson::Value &value = json[key.c_str()];

        if (value.IsFloat())
        {
            return value.GetFloat();
        }
    }

    return defaultValue;
}

double SimpleSharedDataPlatformService::getDoubleWithDefaultValue(const std::string &groupName, const std::string &key, double defaultValue)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        const rapidjson::Value &value = json[key.c_str()];

        if (value.IsDouble())
        {
            return value.GetDouble();
        }
    }

    return defaultValue;
}

bool SimpleSharedDataPlatformService::has(const std::string &groupName, const std::string &key)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        return true;
    }

    return false;
}

void SimpleSharedDataPlatformService::remove(const std::string &groupName, const std::string &key)
{
    auto json = create(groupName);

    if (json.HasMember(key.c_str()))
    {
        json.RemoveMember(key.c_str());
    }

    save(json, groupName);
}

void SimpleSharedDataPlatformService::clear(const std::string &groupName)
{
    std::string homeDir = FileHelper::join(FileHelper::getHomeDir(), baseDir);
    FileHelper::createDir(homeDir);

    homeDir = FileHelper::join(homeDir, "shared-data");

    std::string filename = groupName + ".json";
    std::string filePath = FileHelper::join(homeDir, filename);

    FileHelper::removeFile(filePath);
}

void SimpleSharedDataPlatformService::save(rapidjson::Document &json, const std::string &groupName)
{
    rapidjson::StringBuffer buffer;
    buffer.Clear();

    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    json.Accept(writer);

    std::string homeDir = FileHelper::join(FileHelper::getHomeDir(), baseDir);
    homeDir = FileHelper::join(homeDir, "shared-data");

    std::string filename = groupName + ".json";
    std::string filePath = FileHelper::join(homeDir, filename);

    FileHelper::createFileWithStringContent(filePath, std::string(buffer.GetString()));
}

rapidjson::Document SimpleSharedDataPlatformService::create(const std::string &groupName)
{
    // reset data
    auto json = rapidjson::Document();
    json.SetObject();

    // prepare data
    std::string homeDir = FileHelper::join(FileHelper::getHomeDir(), baseDir);
    FileHelper::createDir(homeDir);

    homeDir = FileHelper::join(homeDir, "shared-data");
    FileHelper::createDir(homeDir);

    std::string filename = groupName + ".json";
    std::string filePath = FileHelper::join(homeDir, filename);

    // create file to check errors
    if (!FileHelper::isFile(filePath))
    {
        FileHelper::createFile(filePath);
    }

    // if at the end the file exists then continue
    if (FileHelper::isFile(filePath))
    {
        json.Parse(FileHelper::getFileContentAsString(filePath).c_str());
    }

    return json;
}

} // namespace data
} // namespace ezored
