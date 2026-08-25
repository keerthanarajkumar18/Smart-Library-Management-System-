#ifndef LIBRARY_H
#define LIBRARY_H
#include <mutex> // std::mutex
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <chrono>

#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"
#include "ReservationQueue.h"
#include "FineStrategy.h"
#include "AccessControl.h"
#include "BookRepository.h"


class Library
{
private:
    // Database repository for books
    BookRepository* bookRepository = nullptr;

    // Mutex for thread safety
    std::mutex libraryMutex{};

    // ISBN -> Book
    std::unordered_map<std::string, Book> books;

    // Member ID -> Member
    std::unordered_map<std::string, Member> members;

    // Borrow Record ID -> BorrowRecord
    std::unordered_map<std::string, BorrowRecord> borrowRecords;

    int nextRecordId = 1; // For generating unique borrow record IDs

    // ISBN -> ReservationQueue
    std::unordered_map<std::string, ReservationQueue> reservationQueues; 

    // Fine strategy for calculating fines
    std::shared_ptr<FineStrategy> fineStrategy;

    // Access control
    AccessControl accessControl;

    // Helper function to validate ISBN format
    bool isValidISBN(
    const std::string& isbn) const;

    // Total fines collected by the library
    double totalFinesCollected = 0.0;



public:

    // Book management
    void addBook(const Book& book);
    void removeBook(const std::string& isbn);

    bool addBook(const Member& member, const Book& book);
    bool removeBook(const Member& member, const std::string& isbn);

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

    double returnBook(
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

    // Fine strategy management
    void setFineStrategy(
        std::shared_ptr<FineStrategy> strategy
    );

    //library.setFineStrategy(
    //     std::make_shared<RoleBasedFineStrategy>()
    //);

    // Access control management
    const std::unordered_map<std::string, Book>&
    getBooks() const;

    const std::unordered_map<std::string, Member>&
    getMembers() const;

    const std::unordered_map<std::string, BorrowRecord>&
    getBorrowRecords() const;

    double getTotalFinesCollected() const;

    void addBorrowRecordForTesting(
    const std::string& recordId,
    const std::string& memberId,
    const std::string& isbn,
    std::chrono::system_clock::time_point borrowDate,
    std::chrono::system_clock::time_point dueDate
    );

    // Display borrowing records
    void showMyLibraryRecords();
    void showAllBorrowRecords();

    // Set the book repository
    void setBookRepository(BookRepository& repository);
    // Load books from the repository
    void loadBooks(
    const std::vector<Book>& books
    );
};

#endif