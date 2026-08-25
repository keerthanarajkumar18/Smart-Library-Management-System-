#include "Database.h"

#include <stdexcept>

Database::Database(const std::string& filename)
{
    int result = sqlite3_open(
        filename.c_str(),
        &db
    );

    if (result != SQLITE_OK)
    {
        std::string message = sqlite3_errmsg(db);

        sqlite3_close(db);
        db = nullptr;

        throw std::runtime_error(
            "Failed to open database: " + message
        );
    }
}

Database::~Database()
{
    if (db != nullptr)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

void Database::execute(const std::string& sql)
{
    char* errorMessage = nullptr;

    int result = sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        &errorMessage
    );

    if (result != SQLITE_OK)
    {
        std::string message =
            errorMessage != nullptr
                ? errorMessage
                : "Unknown SQLite error";

        sqlite3_free(errorMessage);

        throw std::runtime_error(
            "Database error: " + message
        );
    }
}

sqlite3* Database::getHandle() const
{
    return db;
}
