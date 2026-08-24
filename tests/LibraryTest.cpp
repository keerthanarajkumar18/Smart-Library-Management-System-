#include <gtest/gtest.h>
#include "Library.h"

// Test case to verify that a book can be added to the library and retrieved correctly
TEST(LibraryTest, AddsBook)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    library.addBook(book);

    EXPECT_EQ(library.getBookCount(), 1);
}

//Test case to find a book by its ISBN in the library and verify that the correct book is returned
TEST(LibraryTest, FindsBookByISBN)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    library.addBook(book);

    Book& result =
        library.getBook("9780132350884");

    EXPECT_EQ(result.getTitle(), "Clean Code");
}

// Test case to verify that a book can be removed from the library and that the book count is updated accordingly
TEST(LibraryTest, RemovesBook)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    library.addBook(book);

    library.removeBook("9780132350884");

    EXPECT_EQ(library.getBookCount(), 0);
}

//Test case to verify that a member can be added to the library and retrieved correctly
TEST(LibraryTest, AddsMember)
{
    Library library;

    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    library.addMember(member);

    EXPECT_EQ(library.getMemberCount(), 1);
}

//Test case to find a member by their ID in the library and verify that the correct member is returned
TEST(LibraryTest, FindsMemberById)
{
    Library library;

    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    library.addMember(member);

    Member& result =
        library.getMember("M001");

    EXPECT_EQ(result.getName(), "Keerthana");
}

//Test case to search for books by title in the library and verify that the correct books are returned
TEST(LibraryTest, SearchesBookByTitle)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            5
        )
    );

    library.addBook(
        Book(
            "Effective C++",
            "Scott Meyers",
            "9780321334879",
            "Programming",
            3
        )
    );

    auto results =
        library.searchByTitle("Clean Code");

    ASSERT_EQ(results.size(), 1);

    EXPECT_EQ(
        results[0].getISBN(),
        "9780132350884"
    );
}