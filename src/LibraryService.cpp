#include "LibraryService.h"
#include "Library.h"
#include "StatisticsService.h"

LibraryService::LibraryService(
    Library& library
)
    : library(library)
{
}

void LibraryService::addBook(
    const Book& book
)
{
    library.addBook(book);
}

void LibraryService::removeBook(
    const std::string& isbn
)
{
    library.removeBook(isbn);
}

void LibraryService::borrowBook(
    const std::string& memberId,
    const std::string& isbn
)
{
    library.borrowBook(
        memberId,
        isbn
    );
}

double LibraryService::returnBook(
    const std::string& memberId,
    const std::string& isbn
)
{
    return library.returnBook(
        memberId,
        isbn
    );
}

void LibraryService::reserveBook(
    const std::string& memberId,
    const std::string& isbn
)
{
    library.reserveBook(
        memberId,
        isbn
    );
}

std::vector<Book>
LibraryService::searchByTitle(
    const std::string& title
) const
{
    return library.searchByTitle(title);
}

std::vector<Book>
LibraryService::searchByAuthor(
    const std::string& author
) const
{
    return library.searchByAuthor(author);
}

std::vector<Book>
LibraryService::searchByCategory(
    const std::string& category
) const
{
    return library.searchByCategory(category);
}

LibraryStatistics
LibraryService::getStatistics() const
{
    return StatisticsService::generate(
        library
    );
}

void LibraryService::addMember(
    const Member& member
)
{
    library.addMember(member);
}

void LibraryService::removeMember(
    const std::string& memberId
)
{
    library.removeMember(memberId);
}

void LibraryService::addBook(
    const Member& member,
    const Book& book
)
{
    library.addBook(
        member,
        book
    );
}

void LibraryService::removeBook(
    const Member& member,
    const std::string& isbn
)
{
    library.removeBook(
        member,
        isbn
    );
}

Member& LibraryService::getMember(
    const std::string& memberId
)
{
    return library.getMember(memberId);
}

const Member& LibraryService::getMember(
    const std::string& memberId
) const
{
    return library.getMember(memberId);
}

const std::unordered_map<std::string, Book>&
LibraryService::getBooks() const
{
    return library.getBooks();
}

const std::unordered_map<std::string, Member>&
LibraryService::getMembers() const
{
    return library.getMembers();
}

const std::unordered_map<std::string, BorrowRecord>&
LibraryService::getBorrowRecords() const
{
    return library.getBorrowRecords();
}