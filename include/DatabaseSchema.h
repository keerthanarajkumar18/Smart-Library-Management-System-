#ifndef DATABASE_SCHEMA_H
#define DATABASE_SCHEMA_H

class Database;

class DatabaseSchema
{
public:
    static void createTables(Database& database);
};

#endif