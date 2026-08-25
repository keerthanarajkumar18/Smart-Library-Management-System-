#include "DatabaseSchema.h"
#include "Database.h"

void DatabaseSchema::createTables(Database& database)
{
    database.execute(R"(
        CREATE TABLE IF NOT EXISTS books (
            isbn TEXT PRIMARY KEY,
            title TEXT NOT NULL,
            author TEXT NOT NULL,
            category TEXT NOT NULL,
            total_copies INTEGER NOT NULL,
            available_copies INTEGER NOT NULL
        );
    )");

    database.execute(R"(
        CREATE TABLE IF NOT EXISTS members (
            member_id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            role INTEGER NOT NULL
        );
    )");

    database.execute(R"(
        CREATE TABLE IF NOT EXISTS borrow_records (
            record_id TEXT PRIMARY KEY,
            isbn TEXT NOT NULL,
            member_id TEXT NOT NULL,
            borrow_date INTEGER NOT NULL,
            due_date INTEGER NOT NULL,
            return_date INTEGER,
            returned INTEGER NOT NULL DEFAULT 0,

            FOREIGN KEY (isbn)
                REFERENCES books(isbn),

            FOREIGN KEY (member_id)
                REFERENCES members(member_id)
        );
    )");

    database.execute(R"(
        CREATE TABLE IF NOT EXISTS reservations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            isbn TEXT NOT NULL,
            member_id TEXT NOT NULL,
            position INTEGER NOT NULL,

            FOREIGN KEY (isbn)
                REFERENCES books(isbn),

            FOREIGN KEY (member_id)
                REFERENCES members(member_id)
        );
    )");
}