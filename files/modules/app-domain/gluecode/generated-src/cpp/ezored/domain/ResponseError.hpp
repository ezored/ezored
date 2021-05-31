// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include <string>
#include <utility>

namespace ezored
{
namespace domain
{

struct ResponseError final
{
    std::string field;
    std::string message;

    ResponseError(std::string field_,
                  std::string message_)
        : field(std::move(field_)), message(std::move(message_))
    {
    }
};

} // namespace domain
} // namespace ezored
