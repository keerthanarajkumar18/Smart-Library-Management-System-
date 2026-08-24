#include <gtest/gtest.h>

#include "Library.h"
#include "LibraryException.h"

TEST(
    LibraryExceptionIntegrationTest,
    GetBookThrowsBookNotFoundException
)
{
    Library library;

    EXPECT_THROW(
        library.getBook("9780132350884"),
        BookNotFoundException
    );
}

TEST(
    LibraryExceptionIntegrationTest,
    RemoveBookThrowsBookNotFoundException
)
{
    Library library;

    EXPECT_THROW(
        library.removeBook("9780132350884"),
        BookNotFoundException
    );
}

TEST(
    LibraryExceptionIntegrationTest,
    BorrowBookThrowsBookUnavailableException
)
{
    Library library;

    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    library.addMember(student);

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        0
    );

    library.addBook(book);

    EXPECT_THROW(
        library.borrowBook(
            "S001",
            "9780132350884"
        ),
        BookUnavailableException
    );
}

TEST(
    LibraryExceptionIntegrationTest,
    BorrowBookThrowsBookNotFoundException
)
{
    Library library;

    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    library.addMember(student);

    EXPECT_THROW(
        library.borrowBook(
            "S001",
            "9780132350884"
        ),
        BookNotFoundException
    );
}

TEST(
    LibraryExceptionIntegrationTest,
    ReturnBookThrowsAlreadyReturnedException
)
{
    Library library;

    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    library.addMember(student);

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        1
    );

    library.addBook(book);

    // First borrow
    library.borrowBook(
        "S001",
        "9780132350884"
    );

    // First return
    library.returnBook(
        "S001",
        "9780132350884"
    );

    // Second return
    EXPECT_THROW(
        library.returnBook(
            "S001",
            "9780132350884"
        ),
        AlreadyReturnedException
    );
}

TEST(
    LibraryExceptionIntegrationTest,
    AddBookThrowsInvalidISBNException
)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "ABC",
        "Programming",
        5
    );

    EXPECT_THROW(
        library.addBook(book),
        InvalidISBNException
    );

    EXPECT_EQ(
        library.getBookCount(),
        0
    );
}

TEST(
    LibraryExceptionIntegrationTest,
    AddBookRejectsIncorrectISBNLength
)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "12345",
        "Programming",
        5
    );

    EXPECT_THROW(
        library.addBook(book),
        InvalidISBNException
    );
}