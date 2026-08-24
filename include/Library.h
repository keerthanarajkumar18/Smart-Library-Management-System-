#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Book.h"
#include "Member.h"

class Library
{
private:
    // ISBN -> Book
    std::unordered_map<std::string, Book> books;

    // Member ID -> Member
    std::unordered_map<std::string, Member> members;

public:

    // Book management
    void addBook(const Book& book);
    void removeBook(const std::string& isbn);

    // Book lookup
    Book& getBook(const std::string& isbn);
    const Book& getBook(const std::string& isbn) const;

    // Member management
    void addMember(const Member& member);
    void removeMember(const std::string& memberId);

    // Member lookup
    Member& getMember(const std::string& memberId);
    const Member& getMember(const std::string& memberId) const;

    // Searching
    std::vector<Book> searchByTitle(const std::string& title) const;
    std::vector<Book> searchByAuthor(const std::string& author) const;
    std::vector<Book> searchByCategory(const std::string& category) const;

    // Statistics/basic information
    std::size_t getBookCount() const;
    std::size_t getMemberCount() const;
};

#endif