#ifndef LIBRARY_SERVICE_H
#define LIBRARY_SERVICE_H

#include <string>
#include <vector>

#include "Book.h"
#include "Statistics.h"
#include "Member.h"
#include "StatisticsService.h"

class Library;

class LibraryService
{
private:
    Library& library;

public:

    explicit LibraryService(
        Library& library
    );

    // Book operations
    void addBook(
        const Book& book
    );

    void addBook(
    const Member& member,
    const Book& book
    );

    void removeBook(
        const std::string& isbn
    );

    void removeBook(
    const Member& member,
    const std::string& isbn
    );

    // Borrowing
    void borrowBook(
        const std::string& memberId,
        const std::string& isbn
    );

    double returnBook(
        const std::string& memberId,
        const std::string& isbn
    );

    // Reservation
    void reserveBook(
        const std::string& memberId,
        const std::string& isbn
    );

    // Searching
    std::vector<Book> searchByTitle(
        const std::string& title
    ) const;

    std::vector<Book> searchByAuthor(
        const std::string& author
    ) const;

    std::vector<Book> searchByCategory(
        const std::string& category
    ) const;

    // Statistics
    LibraryStatistics getStatistics() const;

    void addMember(
        const Member& member
    );

    void removeMember(
        const std::string& memberId
    );



};

#endif