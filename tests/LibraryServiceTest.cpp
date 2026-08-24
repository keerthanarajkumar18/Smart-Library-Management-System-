#include <gtest/gtest.h>

#include "LibraryService.h"
#include "Library.h"
#include "Book.h"
#include "Member.h"
#include "LibraryException.h"

TEST(
    LibraryServiceTest,
    CanAddBook
)
{
    Library library;
    LibraryService service(library);

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    service.addBook(book);

    EXPECT_EQ(
        library.getBookCount(),
        1
    );

    EXPECT_EQ(
        library.getBook(
            "9780132350884"
        ).getTitle(),
        "Clean Code"
    );
}

TEST(
    LibraryServiceTest,
    CanBorrowBook
)
{
    Library library;
    LibraryService service(library);

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

    service.addBook(book);

    library.addMember(member);

    service.borrowBook(
        "M001",
        "9780132350884"
    );

    EXPECT_EQ(
        library.getBook(
            "9780132350884"
        ).getAvailableCopies(),
        4
    );
}

TEST(
    LibraryServiceTest,
    CanSearchBooks
)
{
    Library library;
    LibraryService service(library);

    Book book1(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    Book book2(
        "Clean Architecture",
        "Robert C. Martin",
        "9780134494166",
        "Programming",
        5
    );

    service.addBook(book1);
    service.addBook(book2);

    auto results =
        service.searchByAuthor(
            "Robert C. Martin"
        );

    EXPECT_EQ(
        results.size(),
        2
    );
}

TEST(
    LibraryServiceTest,
    CanReserveBook
)
{
    Library library;
    LibraryService service(library);

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        1
    );

    Member member1(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    Member member2(
        "M002",
        "Student2",
        MemberRole::Student
    );

    service.addBook(book);

    library.addMember(member1);
    library.addMember(member2);

    // First member borrows the only copy
    service.borrowBook(
        "M001",
        "9780132350884"
    );

    // Second member reserves it
    EXPECT_NO_THROW(
        service.reserveBook(
            "M002",
            "9780132350884"
        )
    );

    EXPECT_FALSE(
        library.getReservationQueue(
            "9780132350884"
        ).isEmpty()
    );
}

TEST(
    LibraryServiceTest,
    CanGetStatistics
)
{
    Library library;
    LibraryService service(library);

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

    service.addBook(book);
    library.addMember(member);

    service.borrowBook(
        "M001",
        "9780132350884"
    );

    LibraryStatistics statistics =
        service.getStatistics();

    EXPECT_EQ(
        statistics.activeMembers,
        1
    );

    ASSERT_EQ(
        statistics.mostBorrowedBooks.size(),
        1
    );

    EXPECT_EQ(
        statistics.mostBorrowedBooks[0].title,
        "Clean Code"
    );

    EXPECT_EQ(
        statistics.mostBorrowedBooks[0].borrowCount,
        1
    );
}

TEST(
    LibraryServiceTest,
    StudentCannotAddBook
)
{
    Library library;
    LibraryService service(library);

    Member student(
        "S001",
        "Student",
        MemberRole::Student
    );

    Book book(
        "Clean Architecture",
        "Robert C. Martin",
        "9780134494166",
        "Programming",
        5
    );

    EXPECT_THROW(
        service.addBook(
            student,
            book
        ),
        UnauthorizedActionException
    );

    EXPECT_EQ(
        library.getBookCount(),
        0
    );
}

TEST(
    LibraryServiceTest,
    FacultyCannotAddBook
)
{
    Library library;
    LibraryService service(library);

    Member faculty(
        "F001",
        "Faculty",
        MemberRole::Faculty
    );

    Book book(
        "Effective C++",
        "Scott Meyers",
        "9780321334879",
        "Programming",
        5
    );

    EXPECT_THROW(
        service.addBook(
            faculty,
            book
        ),
        UnauthorizedActionException
    );

    EXPECT_EQ(
        library.getBookCount(),
        0
    );
}

TEST(
    LibraryServiceTest,
    LibrarianCanAddBook
)
{
    Library library;
    LibraryService service(library);

    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    Book book(
        "Effective C++",
        "Scott Meyers",
        "9780321334879",
        "Programming",
        5
    );

    EXPECT_NO_THROW(
        service.addBook(
            librarian,
            book
        )
    );

    EXPECT_EQ(
        library.getBookCount(),
        1
    );

    EXPECT_EQ(
        library.getBook(
            "9780321334879"
        ).getTitle(),
        "Effective C++"
    );
}

TEST(
    LibraryServiceTest,
    StudentCannotRemoveBook
)
{
    Library library;
    LibraryService service(library);

    Member student(
        "S001",
        "Student",
        MemberRole::Student
    );

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    // Add book normally
    service.addBook(book);

    EXPECT_THROW(
        service.removeBook(
            student,
            "9780132350884"
        ),
        UnauthorizedActionException
    );

    // Book must still exist
    EXPECT_EQ(
        library.getBookCount(),
        1
    );
}

TEST(
    LibraryServiceTest,
    FacultyCannotRemoveBook
)
{
    Library library;
    LibraryService service(library);

    Member faculty(
        "F001",
        "Faculty",
        MemberRole::Faculty
    );

    Book book(
        "C++ Primer",
        "Stanley Lippman",
        "9780321714114",
        "Programming",
        5
    );

    service.addBook(book);

    EXPECT_THROW(
        service.removeBook(
            faculty,
            "9780321714114"
        ),
        UnauthorizedActionException
    );

    EXPECT_EQ(
        library.getBookCount(),
        1
    );
}

TEST(
    LibraryServiceTest,
    LibrarianCanRemoveBook
)
{
    Library library;
    LibraryService service(library);

    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    Book book(
        "Effective C++",
        "Scott Meyers",
        "9780321334879",
        "Programming",
        5
    );

    service.addBook(book);

    EXPECT_NO_THROW(
        service.removeBook(
            librarian,
            "9780321334879"
        )
    );

    EXPECT_EQ(
        library.getBookCount(),
        0
    );
}

TEST(
    LibraryServiceTest,
    CanReturnBook
)
{
    Library library;
    LibraryService service(library);

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

    service.addBook(book);
    service.addMember(member);

    // Borrow
    service.borrowBook(
        "M001",
        "9780132350884"
    );

    EXPECT_EQ(
        library.getBook(
            "9780132350884"
        ).getAvailableCopies(),
        4
    );

    // Return
    EXPECT_NO_THROW(
        service.returnBook(
            "M001",
            "9780132350884"
        )
    );

    EXPECT_EQ(
        library.getBook(
            "9780132350884"
        ).getAvailableCopies(),
        5
    );
}

TEST(
    LibraryServiceTest,
    CanSearchBooksByTitle
)
{
    Library library;
    LibraryService service(library);

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

    auto results =
        service.searchByTitle("Clean Code");

    ASSERT_EQ(
        results.size(),
        1
    );

    EXPECT_EQ(
        results[0].getTitle(),
        "Clean Code"
    );
}