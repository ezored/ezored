#include "MapHelper.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace ezored
{
namespace helper
{

std::string MapHelper::toJsonString(const std::unordered_map<std::string, std::string> &data)
{
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    writer.StartObject();

    for (auto &kv : data)
    {
        writer.Key(kv.first.c_str());
        writer.String(kv.second.c_str());
    }

    writer.EndObject();

    return s.GetString();
}

std::unordered_map<std::string, std::string> MapHelper::fromJsonString(const std::string &data)
{
    auto map = std::unordered_map<std::string, std::string>{};

    rapidjson::Document json;
    json.Parse(data.c_str());

    if (json.IsObject())
    {
        for (rapidjson::Value::ConstMemberIterator itr = json.MemberBegin(); itr != json.MemberEnd(); ++itr)
        {
            map[itr->name.GetString()] = itr->value.GetString();
        }
    }

    return map;
}

std::string MapHelper::getValue(const std::string &key, const std::unordered_map<std::string, std::string> &data, const std::string &defaultValue)
{
    auto it = data.find(key);

    if (it == data.end())
    {
        return defaultValue;
    }

    return it->second;
}

} // namespace helper
} // namespace ezored
