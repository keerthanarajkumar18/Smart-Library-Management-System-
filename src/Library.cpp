#include "Library.h"
#include <stdexcept>

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