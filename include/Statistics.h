#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>
#include <vector>

struct BookBorrowStatistics
{
    std::string isbn;
    std::string title;
    int borrowCount;
};

struct LibraryStatistics
{
    std::vector<BookBorrowStatistics> mostBorrowedBooks;

    std::size_t activeMembers;

    double totalFinesCollected;

    std::size_t currentOverdueCount;
};

#endif