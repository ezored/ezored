// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include "ezored/enumerator/CustomerStatusEnumerator.hpp"
#include <cstdint>
#include <string>
#include <utility>

namespace ezored { namespace domain {

struct Customer final {
    int64_t id;
    std::string name;
    std::string token;
    ::ezored::enumerator::CustomerStatusEnumerator status;

    Customer(int64_t id_,
             std::string name_,
             std::string token_,
             ::ezored::enumerator::CustomerStatusEnumerator status_)
    : id(std::move(id_))
    , name(std::move(name_))
    , token(std::move(token_))
    , status(std::move(status_))
    {}
};

} }  // namespace ezored::domain
