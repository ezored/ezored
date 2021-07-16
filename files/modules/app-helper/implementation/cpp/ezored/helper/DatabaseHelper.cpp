#include "DatabaseHelper.hpp"

#include "SQLiteCpp/SQLiteCpp.h"
#include "sqlite3.h"

#include "ezored/core/ApplicationCore.hpp"
#include "ezored/util/Logger.hpp"

namespace ezored
{
namespace helper
{

using namespace ezored::util;
using namespace ezored::core;

std::shared_ptr<SQLite::Database> DatabaseHelper::initializeDatabase(const std::string path)
{
    // some logs
    Logger::shared()->d("Initializing database...");
    Logger::shared()->i("SQlite3 version: " + std::string(SQLite::getLibVersion()));
    Logger::shared()->i("SQliteC++ version: " + std::string(SQLITECPP_VERSION));

    // create database
    std::string dbPath = path + "/database.db3";
    Logger::shared()->i("DB PATH: " + dbPath);

    auto db = std::make_shared<SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    Logger::shared()->d("Database initialized");

    return db;
}

void DatabaseHelper::migrateDatabase(std::shared_ptr<SQLite::Database> db)
{
    // database migrations
    const int dbVersion = db->execAndGet("PRAGMA user_version");
    int newDbVersion = 0;

    Logger::shared()->i("Database version: " + std::to_string(dbVersion));
    Logger::shared()->d("Migrating database...");

    // query list
    auto sqlCreateTodoTable =
        "CREATE TABLE todo ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title VARCHAR(255),"
        "body VARCHAR(255),"
        "data TEXT,"
        "done BOOLEAN,"
        "created_at DATETIME,"
        "updated_at DATETIME"
        ")";

    auto sqlCreateIndexTodoTitle = "CREATE INDEX todo_title ON todo (title)";

    // version 1
    newDbVersion = 1;

    if (dbVersion < newDbVersion)
    {
        if (canMigrateToVersion(newDbVersion))
        {
            // todo
            db->exec(sqlCreateTodoTable);
            db->exec(sqlCreateIndexTodoTitle);

            db->exec("PRAGMA user_version = " + std::to_string(newDbVersion));
        }
        else
        {
            Logger::shared()->d("Database migration ignore version: " + std::to_string(newDbVersion));
        }
    }

    // version 2
    /*
    newDbVersion = 2;

    if (dbVersion < newDbVersion) {
        if (canMigrateToVersion(newDbVersion)) {
            // add your queries

            db->exec("PRAGMA user_version = " + std::to_string(newDbVersion));
        } else {
            Logger::shared()->d("Database migration ignore version: " + std::to_string(newDbVersion));
        }
    }
    */

    /*
    - Always create a new code-block for new versions
    - Never update code-block from old versions
    - Old verions code-block never will be called again, only new code-blocks.
    */

    Logger::shared()->d("Database migrated");
}

bool DatabaseHelper::canMigrateToVersion(int version)
{
    if (ApplicationCore::shared()->getInitializationData().databaseMigrationMaxVersion <= 0)
    {
        return true;
    }
    else if (version <= ApplicationCore::shared()->getInitializationData().databaseMigrationMaxVersion)
    {
        return true;
    }

    return false;
}

int64_t DatabaseHelper::getChanges(std::shared_ptr<SQLite::Database> db)
{
    return sqlite3_changes(db->getHandle());
}

} // namespace helper
} // namespace ezored
