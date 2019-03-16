#pragma once

#include <memory>
#include "SQLiteCpp/Database.h"

namespace ezored { namespace helpers {

class DatabaseHelper {
public:
    virtual ~DatabaseHelper() {}
    static std::shared_ptr<SQLite::Database> initializeDatabase(const std::string path);
    static void migrateDatabase(std::shared_ptr<SQLite::Database> db);
    static bool canMigrateToVersion(int version);
};

} }
