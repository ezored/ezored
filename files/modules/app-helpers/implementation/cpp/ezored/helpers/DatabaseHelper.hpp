#pragma once

#include "SQLiteCpp/Database.h"
#include <memory>

namespace ezored
{
namespace helpers
{

class DatabaseHelper
{
public:
    virtual ~DatabaseHelper() {}
    static std::shared_ptr<SQLite::Database> initializeDatabase(const std::string path);
    static void migrateDatabase(std::shared_ptr<SQLite::Database> db);
    static bool canMigrateToVersion(int version);
};

} // namespace helpers
} // namespace ezored
