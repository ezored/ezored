
#pragma once

#include "ezored/domain/Response.hpp"
#include "ezored/domain/Todo.hpp"

#include "nlohmann/json.hpp"

using namespace ezored::domain;

namespace ezored
{
namespace domain
{

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Response, success, message)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Todo, id, title, body, data, done)

} // namespace domain
} // namespace ezored
