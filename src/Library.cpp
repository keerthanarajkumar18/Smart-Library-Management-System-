#include "Library.h"
#include <stdexcept>
#include <chrono>

//Add a book to the library. If a book with the same ISBN already exists, throw an exception.
void Library::addBook(const Book& book)
{
    const std::string& isbn = book.getISBN();

    if (books.find(isbn) != books.end())
    {
        throw std::runtime_error("Book with this ISBN already exists.");
    }

    books.emplace(isbn, book);
}

//Remove a book from the library by its ISBN. If the book does not exist, throw an exception.
void Library::removeBook(const std::string& isbn)
{
    auto it = books.find(isbn);

    if (it == books.end())
    {
        throw std::runtime_error("Book not found.");
    }

    books.erase(it);
}

//Get a reference to a book by its ISBN. If the book does not exist, throw an exception.
Book& Library::getBook(const std::string& isbn)
{
    auto it = books.find(isbn);

    if (it == books.end())
    {
        throw std::runtime_error("Book not found.");
    }

    return it->second;
}

//Get a const reference to a book by its ISBN. If the book does not exist, throw an exception.
const Book& Library::getBook(const std::string& isbn) const
{
    auto it = books.find(isbn);

    if (it == books.end())
    {
        throw std::runtime_error("Book not found.");
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
        throw std::runtime_error("Book not found.");
    }

    //3. Check if the book has available copies
    Book& book = bookIt->second;

    if(book.getAvailableCopies() <= 0)
    {
        throw std::runtime_error("No available copies of the book.");
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
}

void Library::returnBook(
    const std::string& memberId,
    const std::string& isbn
)
{
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
        throw std::runtime_error("Book not found.");
    }

    //3. Search member's borrowing history 
    const auto& history = memberIt->second.getBorrowingHistory();

    BorrowRecord* activeRecord = nullptr;

    //4. Find the active borrow record for this book
    for(const auto& recordId : history)
    {
        auto recordIt = borrowRecords.find(recordId);
        
        if(recordIt == borrowRecords.end())
        {
            continue; // Skip if record not found
        }

        BorrowRecord& record = recordIt->second;

        if(record.getBookISBN() == isbn && !record.isReturned())
        {
            activeRecord = &record;
            break;
        }
    }

    //5. If no active borrow record found, throw an exception
    if(activeRecord == nullptr)
    {
        throw std::runtime_error("No active borrow record found for this book and member.");
    }

    //6. Get return date
    auto returnDate = std::chrono::system_clock::now();

    //7. Close the borrow record
    activeRecord->markReturned(returnDate);

    //8.Increase the available copies of the book
    bookIt->second.returnCopy();
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