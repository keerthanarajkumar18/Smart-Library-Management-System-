#include <chrono>
#include <iostream>

#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"
#include "Library.h"
#include "LibraryException.h"
#include "StatisticsService.h"

int main()
{
    // =====================================================
    // Phase 8 — Exception Handling
    // =====================================================

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

    // =====================================================
    // Phase 7 — Access Control
    // =====================================================

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


    // =====================================================
    // Phase 10 — Statistics Dashboard
    // =====================================================

    Book book1(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    Book book2(
        "C++ Primer",
        "Stanley Lippman",
        "9780321714114",
        "Programming",
        5
    );

    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    library.addBook(book1);
    library.addBook(book2);

    library.addMember(member);

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    LibraryStatistics statistics =
        StatisticsService::generate(library);

    StatisticsService::display(
        statistics
    );

    return 0;
}