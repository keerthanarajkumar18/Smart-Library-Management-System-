#include <chrono>
#include <iostream>

#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"
#include "Library.h"
#include "LibraryException.h"

int main()
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    BorrowRecord record(
        "BR001",
        book.getISBN(),
        member.getMemberId(),
        borrowDate,
        dueDate
    );

    std::cout << "Record ID: "
              << record.getRecordId() << '\n';

    std::cout << "Returned: "
              << std::boolalpha
              << record.isReturned()
              << '\n';

    record.markReturned(
        std::chrono::system_clock::now()
    );

    std::cout << "Returned after update: "
              << record.isReturned()
              << '\n';

    Library library;
    
    try
    {
        Book invalidBook(
            "Invalid Book",
            "Unknown Author",
            "ABC",
            "Testing",
            5
        );

        library.addBook(invalidBook);
    }
    catch (const InvalidISBNException& e)
    {
        std::cout
            << "Error: "
            << e.what()
            << '\n';
    }

    try
    {
        library.getBook(
            "9780132350884"
        );
    }
    catch (const BookNotFoundException& e)
    {
        std::cout
            << "Error: "
            << e.what()
            << '\n';
    }

    Member student(
    "S001",
    "Student",
    MemberRole::Student
    );

    try
    {
        Book newBook(
            "Clean Architecture",
            "Robert C. Martin",
            "9780134494166",
            "Programming",
            5
        );

        library.addBook(
            student,
            newBook
        );
    }
    catch (const UnauthorizedActionException& e)
    {
        std::cout
            << "Error: "
            << e.what()
            << '\n';
    }
    
    std::cout
    << "Program continues normally."
    << '\n';

    return 0;
}