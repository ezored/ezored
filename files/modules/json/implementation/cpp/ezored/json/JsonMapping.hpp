
#pragma once

#include "ezored/domain/Response.hpp"
#include "ezored/domain/Todo.hpp"

#include "nlohmann/json.hpp"

#include <chrono>

using namespace ezored::domain;

// json library
namespace nlohmann
{
template <typename Clock, typename Duration>
struct adl_serializer<std::chrono::time_point<Clock, Duration>>
{
    static void to_json(json &j, const std::chrono::time_point<Clock, Duration> &tp)
    {
        j = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
    }

    static void from_json(const json &j, std::chrono::time_point<Clock, Duration> &value)
    {
        if (j.is_null())
        {
            auto dur = std::chrono::milliseconds(0);
            value = std::chrono::time_point<std::chrono::system_clock>(dur);
        }
        else
        {
            auto dur = std::chrono::milliseconds(j);
            value = std::chrono::time_point<std::chrono::system_clock>(dur);
        }
    }
};
} // namespace nlohmann

// ezored library
namespace ezored
{
namespace domain
{

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Response, success, message)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Todo, id, title, body, data, done, createdAt, updatedAt)

} // namespace domain
} // namespace ezored
