#include "BookRepository.h"
#include "Database.h"

#include <stdexcept>

BookRepository::BookRepository(Database& database)
    : database(database)
{
}

void BookRepository::save(const Book& book)
{
    sqlite3* db = database.getHandle();

    const char* sql = R"(
        INSERT OR REPLACE INTO books
        (
            isbn,
            title,
            author,
            category,
            total_copies,
            available_copies
        )
        VALUES (?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db,
            sql,
            -1,
            &statement,
            nullptr) != SQLITE_OK)
    {
        throw std::runtime_error(
            "Failed to prepare book insert."
        );
    }

    sqlite3_bind_text(
        statement,
        1,
        book.getISBN().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        2,
        book.getTitle().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        3,
        book.getAuthor().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        4,
        book.getCategory().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_int(
        statement,
        5,
        book.getTotalCopies()
    );

    sqlite3_bind_int(
        statement,
        6,
        book.getAvailableCopies()
    );

    if (sqlite3_step(statement) != SQLITE_DONE)
    {
        sqlite3_finalize(statement);

        throw std::runtime_error(
            "Failed to save book."
        );
    }

    sqlite3_finalize(statement);
}

std::vector<Book> BookRepository::findAll() const
{
    std::vector<Book> books;

    sqlite3* db = database.getHandle();

    const char* sql = R"(
        SELECT
            isbn,
            title,
            author,
            category,
            total_copies,
            available_copies
        FROM books;
    )";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(
            db,
            sql,
            -1,
            &statement,
            nullptr) != SQLITE_OK)
    {
        throw std::runtime_error(
            "Failed to prepare book query."
        );
    }

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        std::string isbn =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 0)
            );

        std::string title =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 1)
            );

        std::string author =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 2)
            );

        std::string category =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 3)
            );

        int totalCopies =
            sqlite3_column_int(statement, 4);

        int availableCopies =
            sqlite3_column_int(statement, 5);

        Book book(
            title,
            author,
            isbn,
            category,
            totalCopies
        );

        /*
         * The constructor sets the initial
         * available copies equal to total copies.
         *
         * If availableCopies differs because
         * someone has borrowed the book,
         * we need to restore that state.
         */
        while (
            book.getAvailableCopies() > availableCopies
        )
        {
            book.borrowCopy();
        }

        books.push_back(book);
    }

    sqlite3_finalize(statement);

    return books;
}