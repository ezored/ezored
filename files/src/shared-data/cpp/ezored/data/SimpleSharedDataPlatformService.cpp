#include "SimpleSharedDataPlatformService.hpp"
#include "ezored/helpers/StringHelper.hpp"
#include "ezored/io/FileHelper.hpp"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace ezored::io;
using namespace ezored::helpers;

namespace ezored
{
namespace data
{

std::string SimpleSharedDataPlatformService::baseDir = "ezored";

void SimpleSharedDataPlatformService::setString(const std::string &key, const std::string &value)
{
    if (initialized)
    {
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
    }
}

void SimpleSharedDataPlatformService::setInteger(const std::string &key, int32_t value)
{
    if (initialized)
    {
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
    }
}

void SimpleSharedDataPlatformService::setLong(const std::string &key, int64_t value)
{
    if (initialized)
    {
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
    }
}

void SimpleSharedDataPlatformService::setBool(const std::string &key, bool value)
{
    if (initialized)
    {
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
    }
}

void SimpleSharedDataPlatformService::setFloat(const std::string &key, float value)
{
    if (initialized)
    {
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
    }
}

void SimpleSharedDataPlatformService::setDouble(const std::string &key, double value)
{
    if (initialized)
    {
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
    }
}

std::string SimpleSharedDataPlatformService::getString(const std::string &key)
{
    return getStringWithDefaultValue(key, "");
}

int32_t SimpleSharedDataPlatformService::getInteger(const std::string &key)
{
    return getIntegerWithDefaultValue(key, 0);
}

int64_t SimpleSharedDataPlatformService::getLong(const std::string &key)
{
    return getLongWithDefaultValue(key, 0);
}

bool SimpleSharedDataPlatformService::getBool(const std::string &key)
{
    return getBoolWithDefaultValue(key, false);
}

float SimpleSharedDataPlatformService::getFloat(const std::string &key)
{
    return getFloatWithDefaultValue(key, 0);
}

double SimpleSharedDataPlatformService::getDouble(const std::string &key)
{
    return getDoubleWithDefaultValue(key, 0);
}

std::string SimpleSharedDataPlatformService::getStringWithDefaultValue(const std::string &key, const std::string &defaultValue)
{
    if (initialized)
    {
        if (json.HasMember(key.c_str()))
        {
            const rapidjson::Value &value = json[key.c_str()];

            if (value.IsString())
            {
                return value.GetString();
            }
        }
    }

    return defaultValue;
}

int32_t SimpleSharedDataPlatformService::getIntegerWithDefaultValue(const std::string &key, int32_t defaultValue)
{
    if (initialized)
    {
        if (json.HasMember(key.c_str()))
        {
            const rapidjson::Value &value = json[key.c_str()];

            if (value.IsInt())
            {
                return value.GetInt();
            }
        }
    }

    return defaultValue;
}

int64_t SimpleSharedDataPlatformService::getLongWithDefaultValue(const std::string &key, int64_t defaultValue)
{
    if (initialized)
    {
        if (json.HasMember(key.c_str()))
        {
            const rapidjson::Value &value = json[key.c_str()];

            if (value.IsInt64())
            {
                return value.GetInt64();
            }
        }
    }

    return defaultValue;
}

bool SimpleSharedDataPlatformService::getBoolWithDefaultValue(const std::string &key, bool defaultValue)
{
    if (initialized)
    {
        if (json.HasMember(key.c_str()))
        {
            const rapidjson::Value &value = json[key.c_str()];

            if (value.IsBool())
            {
                return value.GetBool();
            }
        }
    }

    return defaultValue;
}

float SimpleSharedDataPlatformService::getFloatWithDefaultValue(const std::string &key, float defaultValue)
{
    if (initialized)
    {
        if (json.HasMember(key.c_str()))
        {
            const rapidjson::Value &value = json[key.c_str()];

            if (value.IsFloat())
            {
                return value.GetFloat();
            }
        }
    }

    return defaultValue;
}

double SimpleSharedDataPlatformService::getDoubleWithDefaultValue(const std::string &key, double defaultValue)
{
    if (initialized)
    {
        if (json.HasMember(key.c_str()))
        {
            const rapidjson::Value &value = json[key.c_str()];

            if (value.IsDouble())
            {
                return value.GetDouble();
            }
        }
    }

    return defaultValue;
}

bool SimpleSharedDataPlatformService::has(const std::string &key)
{
    if (initialized)
    {
        if (json.HasMember(key.c_str()))
        {
            return true;
        }
    }

    return false;
}

void SimpleSharedDataPlatformService::remove(const std::string &key)
{
    if (initialized)
    {
        if (has(key))
        {
            json.RemoveMember(key.c_str());
        }
    }
}

void SimpleSharedDataPlatformService::clear()
{
    if (initialized)
    {
        json = rapidjson::Document();
        json.SetObject();
    }
}

void SimpleSharedDataPlatformService::save(bool async, bool autoFinish)
{
    if (initialized)
    {
        rapidjson::StringBuffer buffer;
        buffer.Clear();

        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        json.Accept(writer);

        FileHelper::createFileWithStringContent(filePath, std::string(buffer.GetString()));

        if (autoFinish)
        {
            finish();
        }
    }
}

void SimpleSharedDataPlatformService::saveAsync()
{
    save(true, true);
}

void SimpleSharedDataPlatformService::saveSync()
{
    save(false, true);
}

void SimpleSharedDataPlatformService::start(const std::string &groupName)
{
    // reset data
    initialized = false;
    json = rapidjson::Document();
    json.SetObject();

    // prepare data
    std::string homeDir = FileHelper::join(FileHelper::getHomeDir(), baseDir);
    FileHelper::createDir(homeDir);

    homeDir = FileHelper::join(homeDir, "shared-data");
    FileHelper::createDir(homeDir);

    std::string filename = groupName + ".json";
    filePath = FileHelper::join(homeDir, filename);

    // create file to check errors
    if (!FileHelper::isFile(filePath))
    {
        FileHelper::createFile(filePath);
    }

    // if at the end the file exists then continue
    if (FileHelper::isFile(filePath))
    {
        json.Parse(FileHelper::getFileContentAsString(filePath).c_str());
        initialized = true;
    }
}

void SimpleSharedDataPlatformService::finish()
{
    initialized = false;
    json = rapidjson::Document();
    json.SetObject();
}

} // namespace data
} // namespace ezored
