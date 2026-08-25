#include "Library.h"
#include "LibraryException.h"
#include "Logger.h"

#include <mutex>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <cctype>

// Helper function to validate ISBN format
bool Library::isValidISBN(
    const std::string& isbn
) const
{
    // ISBN-13 must contain exactly 13 digits
    if (isbn.length() != 13)
    {
        return false;
    }

    // Every character must be a digit
    for (char c : isbn)
    {
        if (!std::isdigit(
                static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    int sum = 0;

    // Calculate ISBN-13 checksum
    for (int i = 0; i < 12; ++i)
    {
        int digit = isbn[i] - '0';

        if (i % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            sum += digit * 3;
        }
    }

    int checkDigit =
        (10 - (sum % 10)) % 10;

    return checkDigit ==
           (isbn[12] - '0');
}

//Add a book to the library. If a book with the same ISBN already exists, throw an exception.
void Library::addBook(const Book& book)
{
    const std::string& isbn =
        book.getISBN();

    // Validate ISBN before adding book
    if (!isValidISBN(isbn))
    {
        throw InvalidISBNException(isbn);
    }

    // Check duplicate ISBN
    if (books.find(isbn) != books.end())
    {
        throw std::runtime_error(
            "Book with this ISBN already exists."
        );
    }

    books.emplace(isbn, book);

    // persist to database
    if (bookRepository != nullptr)
    {
        bookRepository->save(book);
    }
}

//Add a book to the library if the member is authorized. Return true if the book was added, false otherwise.
bool Library::addBook(
    const Member& member,
    const Book& book
)
{
    // Check authorization
    if (!accessControl.isAuthorized(
            member,
            Operation::AddBook))
    {
        throw UnauthorizedActionException(
            "Add book"
        );
    }

    // Use existing addBook logic
    addBook(book);

    return true;
}

//Remove a book from the library by its ISBN. If the book does not exist, throw an exception.
void Library::removeBook(const std::string& isbn)
{
    auto it = books.find(isbn);

    if (it == books.end())
    {
        throw BookNotFoundException(isbn);
    }

    books.erase(it);
}

bool Library::removeBook(
    const Member& member,
    const std::string& isbn
)
{
    if (!accessControl.isAuthorized(
            member,
            Operation::RemoveBook))
    {
        throw UnauthorizedActionException(
            "Remove book"
        );
    }

    removeBook(isbn);

    return true;
}

//Get a reference to a book by its ISBN. If the book does not exist, throw an exception.
Book& Library::getBook(const std::string& isbn)
{
    auto it = books.find(isbn);

    if (it == books.end())
    {
        throw BookNotFoundException(isbn);
    }

    return it->second;
}

//Get a const reference to a book by its ISBN. If the book does not exist, throw an exception.
const Book& Library::getBook(
    const std::string& isbn
) const
{
    auto it = books.find(isbn);

    if (it == books.end())
    {
        throw BookNotFoundException(isbn);
    }

    return it->second;
}

//Add a member to the library. If a member with the same ID already exists, throw an exception.
void Library::addMember(const Member& member)
{
    const std::string& memberId = member.getMemberId();

    if (members.find(memberId) != members.end())
    {
        throw std::runtime_error("Member with this ID already exists.");
    }

    members.emplace(memberId, member);
}

//Remove a member from the library by their ID. If the member does not exist, throw an exception.
void Library::removeMember(const std::string& memberId)
{
    auto it = members.find(memberId);

    if (it == members.end())
    {
        throw std::runtime_error("Member not found.");
    }

    members.erase(it);
}

//Get a reference to a member by their ID. If the member does not exist, throw an exception.
Member& Library::getMember(const std::string& memberId)
{
    auto it = members.find(memberId);

    if (it == members.end())
    {
        throw std::runtime_error("Member not found.");
    }

    return it->second;
}

//Get a const reference to a member by their ID. If the member does not exist, throw an exception.
const Member& Library::getMember(
    const std::string& memberId
) const
{
    auto it = members.find(memberId);

    if (it == members.end())
    {
        throw std::runtime_error("Member not found.");
    }

    return it->second;
}

//Search for books by title. Return a vector of books that match the given title.
std::vector<Book> Library::searchByTitle(
    const std::string& title
) const
{
    std::vector<Book> results;

    for (const auto& entry : books)
    {
        const Book& book = entry.second;

        if (book.getTitle() == title)
        {
            results.push_back(book);
        }
    }

    return results;
}

//Search for books by author. Return a vector of books that match the given author.
std::vector<Book> Library::searchByAuthor(
    const std::string& author
) const
{
    std::vector<Book> results;

    for (const auto& entry : books)
    {
        const Book& book = entry.second;

        if (book.getAuthor() == author)
        {
            results.push_back(book);
        }
    }

    return results;
}

//Search for books by category. Return a vector of books that match the given category.
std::vector<Book> Library::searchByCategory(
    const std::string& category
) const
{
    std::vector<Book> results;

    for (const auto& entry : books)
    {
        const Book& book = entry.second;

        if (book.getCategory() == category)
        {
            results.push_back(book);
        }
    }

    return results;
}

//Get the total number of books in the library.
std::size_t Library::getBookCount() const
{
    return books.size();
}

//Get the total number of members in the library.
std::size_t Library::getMemberCount() const
{
    return members.size();
}

//Borrow a book for a member. If the member or book does not exist, or if there are no available copies of the book, throw an exception.
void Library::borrowBook(
    const std::string& memberId,
    const std::string& isbn
)
{
    std::lock_guard<std::mutex> lock(libraryMutex);

    //1. Check if the member exists
    auto memberIt = members.find(memberId);

    if(memberIt == members.end())
    {
        throw std::runtime_error("Member not found.");
    }

    //2. Check if the book exists
    auto bookIt = books.find(isbn);

    if(bookIt == books.end())
    {
        throw BookNotFoundException(isbn);
    }

    //3. Check if the book has available copies
    Book& book = bookIt->second;

    if(book.getAvailableCopies() <= 0)
    {
        throw BookUnavailableException(isbn);
    }   

    //4. Borrow the book and create a borrow record
    book.borrowCopy();

    std::string recordId =
    "BR" +
    std::string(3 - std::to_string(nextRecordId).length(), '0') +
    std::to_string(nextRecordId++);

    auto borrowDate = std::chrono::system_clock::now();

    auto dueDate = borrowDate + std::chrono::hours(24 * 14);    //2 weeks borrowing period

    BorrowRecord record(
        recordId,
        isbn,
        memberId,
        borrowDate,
        dueDate
    );

    borrowRecords.emplace(recordId, record);

    memberIt->second.addBorrowRecord(recordId);

    Logger::log(
        LogAction::BORROW,
        memberId,
        isbn
    );
}

double Library::returnBook(
    const std::string& memberId,
    const std::string& isbn
)
{
    std::lock_guard<std::mutex> lock(libraryMutex);

    //1. Check if the member exists
    auto memberIt = members.find(memberId);

    if(memberIt == members.end())
    {
        throw std::runtime_error("Member not found.");
    }

    //2. Check if the book exists
    auto bookIt = books.find(isbn);

    if(bookIt == books.end())
    {
        throw BookNotFoundException(isbn);
    }
        
    const auto& history =
        memberIt->second.getBorrowingHistory();

    BorrowRecord* activeRecord = nullptr;

    bool returnedRecordFound = false;

    for (const auto& recordId : history)
    {
        auto recordIt =
            borrowRecords.find(recordId);

        if (recordIt == borrowRecords.end())
        {
            continue;
        }

        BorrowRecord& record =
            recordIt->second;

        // Check whether this record belongs
        // to the requested book
        if (record.getBookISBN() == isbn)
        {
            // Book is currently borrowed
            if (!record.isReturned())
            {
                activeRecord = &record;
                break;
            }

            // Book was already returned
            returnedRecordFound = true;
        }
    }

        if (activeRecord == nullptr)
    {
        if (returnedRecordFound)
        {
            throw AlreadyReturnedException(isbn);
        }

        throw std::runtime_error(
            "No borrowing record found for this book and member."
        );
    }

    auto returnDate = std::chrono::system_clock::now();

    // Mark the borrowing record as returned first.
    // The fine strategy needs the actual return date.
    activeRecord->markReturned(returnDate);

    // Calculate fine if a fine strategy is set
    double fine = 0.0;

    if (fineStrategy)
    {
        fine =
            fineStrategy->calculateFine(
                *activeRecord,
                memberIt->second
            );
    }

    totalFinesCollected += fine;

    if (fine > 0.0)
{
    Logger::log(
    LogAction::FINE,
    memberId,
    std::to_string(fine)
);
}

    //8.Increase the available copies of the book
    bookIt->second.returnCopy();

     Logger::log(
    LogAction::RETURN,
    memberId,
    isbn
);

    //9.Check reservation queue
    auto queueIt = reservationQueues.find(isbn);

    if (queueIt != reservationQueues.end())
    {
    ReservationQueue& queue = queueIt->second;

        if (!queue.isEmpty())
        {
        const std::string nextMember = queue.front();

        // Remove member from queue
        queue.pop();

        // For now, simply notify using console output
        std::cout
            << "Book "
            << isbn
            << " is now available for member "
            << nextMember
            << std::endl;
        }
    }

    // 10. Return calculated fine
    return fine;
}

//Get a const reference to a borrow record by its ID. If the record does not exist, throw an exception.
const BorrowRecord& Library::getBorrowRecord(
    const std::string& recordId
) const
{
    auto it = borrowRecords.find(recordId);

    if(it == borrowRecords.end())
    {
        throw std::runtime_error("Borrow record not found.");
    }

    return it->second;
}

void Library::reserveBook(
    const std::string& memberId,
    const std::string& isbn
)
{
    // Check member
    auto memberIt = members.find(memberId);

    if (memberIt == members.end())
    {
        throw std::runtime_error(
            "Member not found."
        );
    }

    // Check book
    auto bookIt = books.find(isbn);

    if (bookIt == books.end())
    {
        throw BookNotFoundException(isbn);
    }

    // Book is available
    // No need to reserve it.
    if (bookIt->second.getAvailableCopies() > 0)
    {
        throw std::runtime_error(
            "Book is currently available. "
            "Borrow it instead of reserving."
        );
    }

    // Add member to reservation queue
    reservationQueues[isbn].addMember(memberId);

    Logger::log(
        LogAction::RESERVATION,
        memberId,
        isbn
    );
}

const ReservationQueue& Library::getReservationQueue(
    const std::string& isbn
) const
{
    auto it =
        reservationQueues.find(isbn);

    if (it == reservationQueues.end())
    {
        throw std::runtime_error(
            "No reservation queue exists for this book."
        );
    }

    return it->second;
}

// Set the fine strategy for calculating fines. This allows the library to switch between different fine calculation strategies at runtime.
void Library::setFineStrategy(
    std::shared_ptr<FineStrategy> strategy
)
{
    fineStrategy = strategy;
}

const std::unordered_map<std::string, Book>&
Library::getBooks() const
{
    return books;
}

const std::unordered_map<std::string, Member>&
Library::getMembers() const
{
    return members;
}

const std::unordered_map<std::string, BorrowRecord>&
Library::getBorrowRecords() const
{
    return borrowRecords;
}

double Library::getTotalFinesCollected() const
{
    return totalFinesCollected;
}

void Library::addBorrowRecordForTesting(
    const std::string& recordId,
    const std::string& memberId,
    const std::string& isbn,
    std::chrono::system_clock::time_point borrowDate,
    std::chrono::system_clock::time_point dueDate
)
{
    // Check member
    if (members.find(memberId) == members.end())
    {
        throw std::runtime_error(
            "Member not found."
        );
    }

    // Check book
    if (books.find(isbn) == books.end())
    {
        throw std::runtime_error(
            "Book not found."
        );
    }

    BorrowRecord record(
        recordId,
        isbn,
        memberId,
        borrowDate,
        dueDate
    );

    books.at(isbn).borrowCopy();

    borrowRecords.emplace(
        recordId,
        record
    );

    members.at(memberId).addBorrowRecord(recordId);
}

void Library::setBookRepository(
    BookRepository& repository
)
{
    bookRepository = &repository;
}
void Library::loadBooks(
    const std::vector<Book>& loadedBooks
)
{
    for (const Book& book : loadedBooks)
    {
        books.emplace(
            book.getISBN(),
            book
        );
    }
}