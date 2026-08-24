#include <gtest/gtest.h>
#include "Library.h"

TEST(LibraryAccessControlTest, StudentCannotAddBook)
{
    Library library;

    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    bool result = library.addBook(
        student,
        book
    );

    EXPECT_FALSE(result);

    EXPECT_EQ(
        library.getBookCount(),
        0
    );
}

TEST(LibraryAccessControlTest, FacultyCannotAddBook)
{
    Library library;

    Member faculty(
        "F001",
        "Faculty",
        MemberRole::Faculty
    );

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    bool result = library.addBook(
        faculty,
        book
    );

    EXPECT_FALSE(result);

    EXPECT_EQ(
        library.getBookCount(),
        0
    );
}

TEST(LibraryAccessControlTest, LibrarianCanAddBook)
{
    Library library;

    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    bool result = library.addBook(
        librarian,
        book
    );

    EXPECT_TRUE(result);

    EXPECT_EQ(
        library.getBookCount(),
        1
    );
}

TEST(LibraryAccessControlTest, StudentCannotRemoveBook)
{
    Library library;

    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    library.addBook(book);

    bool result = library.removeBook(
        student,
        "9780132350884"
    );

    EXPECT_FALSE(result);

    EXPECT_EQ(
        library.getBookCount(),
        1
    );
}

TEST(LibraryAccessControlTest, LibrarianCanRemoveBook)
{
    Library library;

    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    library.addBook(book);

    bool result = library.removeBook(
        librarian,
        "9780132350884"
    );

    EXPECT_TRUE(result);

    EXPECT_EQ(
        library.getBookCount(),
        0
    );
}