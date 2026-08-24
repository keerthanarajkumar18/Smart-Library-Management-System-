#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"
#include "ReservationQueue.h"

class Library
{
private:
    // ISBN -> Book
    std::unordered_map<std::string, Book> books;

    // Member ID -> Member
    std::unordered_map<std::string, Member> members;

    // Borrow Record ID -> BorrowRecord
    std::unordered_map<std::string, BorrowRecord> borrowRecords;

    int nextRecordId = 1; // For generating unique borrow record IDs

    // ISBN -> ReservationQueue
    std::unordered_map<std::string, ReservationQueue> reservationQueues; 

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

    // Statistics
    std::size_t getBookCount() const;
    std::size_t getMemberCount() const;

    // Borrowing and returning books
    void borrowBook(
        const std::string& memberId,
        const std::string&isbn
    );

    void returnBook(
        const std::string& memberId,
        const std::string& isbn
    );

    // Borrow record lookup
    const BorrowRecord& getBorrowRecord(
        const std::string& recordId
    ) const;

    //Reservation management
    void reserveBook(
        const std::string& memberId,
        const std::string& isbn
    );

    const ReservationQueue& getReservationQueue(
        const std::string& isbn
    ) const;
};

#endif