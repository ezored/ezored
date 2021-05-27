#pragma once

#include "ezored/dataservices/TodoDataService.hpp"
#include "ezored/domain/Todo.hpp"

#include "SQLiteCpp/SQLiteCpp.h"

namespace ezored
{
namespace dataservices
{

using namespace domain;

class EZRTodoDataService : TodoDataService
{
public:
    virtual ~EZRTodoDataService() {}
    static Todo bindFromRow(SQLite::Statement &row);
};

} // namespace dataservices
} // namespace ezored
