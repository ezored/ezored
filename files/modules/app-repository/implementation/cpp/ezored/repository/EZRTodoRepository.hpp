#pragma once

#include "ezored/domain/Todo.hpp"
#include "ezored/repository/TodoRepository.hpp"

#include "SQLiteCpp/SQLiteCpp.h"

namespace ezored
{
namespace repository
{

using namespace domain;

class EZRTodoRepository : TodoRepository
{
public:
    virtual ~EZRTodoRepository() {}
    static Todo bindFromRow(SQLite::Statement &row);
};

} // namespace repository
} // namespace ezored
