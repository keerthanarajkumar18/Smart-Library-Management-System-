#include <gtest/gtest.h>
#include "LibraryException.h"

//Base Exception Test for LibraryException and its derived classes
TEST(LibraryExceptionTest, BaseException)
{
    try
    {
        throw LibraryException("Library error");
    }
    catch (const LibraryException& e)
    {
        EXPECT_STREQ(
            e.what(),
            "Library error"
        );
    }
}

TEST(
    LibraryExceptionTest,
    BookNotFoundException
)
{
    try
    {
        throw BookNotFoundException(
            "9780132350884"
        );
    }
    catch (const BookNotFoundException& e)
    {
        EXPECT_STREQ(
            e.what(),
            "Book not found: 9780132350884"
        );
    }
}

TEST(
    LibraryExceptionTest,
    BookUnavailableException
)
{
    try
    {
        throw BookUnavailableException(
            "9780132350884"
        );
    }
    catch (const BookUnavailableException& e)
    {
        EXPECT_STREQ(
            e.what(),
            "Book is currently unavailable: 9780132350884"
        );
    }
}

TEST(
    LibraryExceptionTest,
    InvalidISBNException
)
{
    try
    {
        throw InvalidISBNException("ABC");
    }
    catch (const InvalidISBNException& e)
    {
        EXPECT_STREQ(
            e.what(),
            "Invalid ISBN: ABC"
        );
    }
}

TEST(
    LibraryExceptionTest,
    DerivedExceptionCanBeCaughtAsStdException
)
{
    try
    {
        throw BookNotFoundException(
            "9780132350884"
        );
    }
    catch (const std::exception& e)
    {
        EXPECT_STREQ(
            e.what(),
            "Book not found: 9780132350884"
        );
    }
}

