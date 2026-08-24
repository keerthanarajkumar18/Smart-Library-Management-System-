#ifndef LIBRARY_EXCEPTION_H
#define LIBRARY_EXCEPTION_H

#include <stdexcept>
#include <string>

class LibraryException : public std::runtime_error
{
public:
    explicit LibraryException(
        const std::string& message
    )
        : std::runtime_error(message)
    {
    }
};

class BookNotFoundException
    : public LibraryException
{
public:
    explicit BookNotFoundException(
        const std::string& isbn
    )
        : LibraryException(
            "Book not found: " + isbn
        )
    {
    }
};

class BookUnavailableException
    : public LibraryException
{
public:
    explicit BookUnavailableException(
        const std::string& isbn
    )
        : LibraryException(
            "Book is currently unavailable: " + isbn
        )
    {
    }
};

class UnauthorizedActionException
    : public LibraryException
{
public:
    explicit UnauthorizedActionException(
        const std::string& action
    )
        : LibraryException(
            "Unauthorized action: " + action
        )
    {
    }
};

class InvalidISBNException
    : public LibraryException
{
public:
    explicit InvalidISBNException(
        const std::string& isbn
    )
        : LibraryException(
            "Invalid ISBN: " + isbn
        )
    {
    }
};

class AlreadyReturnedException
    : public LibraryException
{
public:
    explicit AlreadyReturnedException(
        const std::string& isbn
    )
        : LibraryException(
            "Book has already been returned: " + isbn
        )
    {
    }
};

#endif