#include <iostream>

#include "Book.h"
#include "Member.h"
#include "Library.h"
#include "LibraryService.h"
#include "LibraryException.h"

int main()
{
    // =====================================================
    // Create Library and Service
    // =====================================================

    Library library;

    LibraryService service(library);


    // =====================================================
    // Phase 8 — Exception Handling
    // =====================================================

    try
    {
        Book invalidBook(
            "Invalid Book",
            "Unknown Author",
            "ABC",
            "Testing",
            5
        );

        service.addBook(invalidBook);
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
        service.searchByTitle(
            "Non Existing Book"
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

        /*
         * Access-controlled addBook is still handled
         * directly by Library for now.
         *
         * We will move this behind LibraryService
         * in the next Phase 11 step.
         */

        service.addBook(
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

    Member librarian(
    "L001",
    "Librarian",
    MemberRole::Librarian
    );

    Book librarianBook(
    "Effective C++",
    "Scott Meyers",
    "9780321334879",
    "Programming",
    5
    );

    try
    {
        service.addBook(
            librarian,
            librarianBook
        );

        std::cout
            << "Librarian successfully added book."
            << '\n';
    }
    catch (const UnauthorizedActionException& e)
    {
        std::cout
            << "Error: "
            << e.what()
            << '\n';
    }

    try
    {
        service.removeBook(
            librarian,
            "9780321334879"
        );

        std::cout
            << "Librarian successfully removed book."
            << '\n';
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
    // Add Books
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

    service.addBook(book1);
    service.addBook(book2);


    // =====================================================
    // Add Member
    // =====================================================

    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    service.addMember(member);


    // =====================================================
    // Borrow Book
    // =====================================================

    service.borrowBook(
        "M001",
        "9780132350884"
    );


    // =====================================================
    // Search Books
    // =====================================================

    std::vector<Book> searchResults =
        service.searchByTitle(
            "Clean Code"
        );

    std::cout
        << "\nSearch Results:\n";

    for (const Book& book : searchResults)
    {
        std::cout
            << "- "
            << book.getTitle()
            << " by "
            << book.getAuthor()
            << '\n';
    }


    // =====================================================
    // Statistics
    // =====================================================

    LibraryStatistics statistics =
        service.getStatistics();

    std::cout
        << "\n========== LIBRARY STATISTICS ==========\n";

    std::cout
        << "\nMost Borrowed:\n";

    int rank = 1;

    for (const auto& book :
         statistics.mostBorrowedBooks)
    {
        std::cout
            << rank
            << ". "
            << book.title
            << "          "
            << book.borrowCount
            << " borrows\n";

        rank++;
    }

    std::cout
        << "\nActive Members:      "
        << statistics.activeMembers
        << '\n';

    std::cout
        << "Total Fines:         Rs."
        << statistics.totalFinesCollected
        << '\n';

    std::cout
        << "Overdue Books:       "
        << statistics.currentOverdueCount
        << '\n';

    std::cout
        << "\n=========================================\n";


    std::cout
        << "\nProgram completed successfully.\n";

    return 0;
}