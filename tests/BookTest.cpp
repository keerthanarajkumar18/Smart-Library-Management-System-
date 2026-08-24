#include <gtest/gtest.h>
#include <Book.h>

// Test case to verify the creation of a Book object
TEST(BookTest, CreatesBookCorrectly)
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    EXPECT_EQ(book.getTitle(), "Clean Code");
    EXPECT_EQ(book.getAuthor(), "Robert C. Martin");
    EXPECT_EQ(book.getISBN(), "9780132350884");
    EXPECT_EQ(book.getCategory(), "Programming");
}

// Test case to verify the total copies and available copies of a Book object
TEST(BookTest, SetsTotalCopiesCorrectly)
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    EXPECT_EQ(book.getTotalCopies(), 5);
    EXPECT_EQ(book.getAvailableCopies(), 5);
}

//Test case to verify that borrowing a copy decreases the available copies of a Book object
TEST(BookTest, BorrowCopyDecreasesAvailability)
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    book.borrowCopy();

    EXPECT_EQ(book.getAvailableCopies(), 4);
}

// Test case to verify that returning a copy increases the available copies of a Book object
TEST(BookTest, ReturnCopyIncreasesAvailability)
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    book.borrowCopy();
    book.returnCopy();

    EXPECT_EQ(book.getAvailableCopies(), 5);
}

// Test case to verify that borrowing a copy when no copies are available throws an exception
// Test case to verify that borrowing a copy when no copies are available throws an exception
TEST(BookTest, CannotBorrowWhenNoCopiesAvailable)
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        2
    );

    book.borrowCopy();
    book.borrowCopy();

    EXPECT_THROW(
        book.borrowCopy(),
        std::runtime_error
    );

    EXPECT_EQ(book.getAvailableCopies(), 0);
}

// Test case to verify that returning a copy when all copies are already returned throws an exception
// Test case to verify that returning a copy when all copies are already returned throws an exception
TEST(BookTest, CannotReturnBeyondTotalCopies)
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        2
    );

    EXPECT_THROW(
        book.returnCopy(),
        std::runtime_error
    );

    EXPECT_EQ(book.getAvailableCopies(), 2);
}