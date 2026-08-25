#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"

class Database
{
private:
    sqlite3* db = nullptr;

public:
    explicit Database(const std::string& filename);
    ~Database();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    void execute(const std::string& sql);

    sqlite3* getHandle() const;
};

#endif