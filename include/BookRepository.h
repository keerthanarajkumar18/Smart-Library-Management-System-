#ifndef BOOK_REPOSITORY_H
#define BOOK_REPOSITORY_H

#include <vector>
#include "Book.h"

class Database;

class BookRepository
{
private:
    Database& database;

public:
    explicit BookRepository(Database& database);

    void save(const Book& book);

    std::vector<Book> findAll() const;
};

#endif