#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "Library.h"
#include "Book.h"
#include "Member.h"

static std::string readLogFile()
{
    std::ifstream logFile("library.log");

    if (!logFile)
    {
        return "";
    }

    std::string content;
    std::string line;

    while (std::getline(logFile, line))
    {
        content += line;
        content += '\n';
    }

    return content;
}

TEST(LibraryLoggerTest, LogsBorrow)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    Member student(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    library.addBook(book);
    library.addMember(student);

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    std::string log =
        readLogFile();

    EXPECT_NE(
        log.find("BORROW M001 9780132350884"),
        std::string::npos
    );
}

TEST(LibraryLoggerTest, LogsReturn)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    Member student(
        "M002",
        "Student",
        MemberRole::Student
    );

    library.addBook(book);
    library.addMember(student);

    library.borrowBook(
        "M002",
        "9780132350884"
    );

    library.returnBook(
        "M002",
        "9780132350884"
    );

    std::string log =
        readLogFile();

    EXPECT_NE(
        log.find("RETURN M002 9780132350884"),
        std::string::npos
    );
}

TEST(LibraryLoggerTest, LogsReservation)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        1
    );

    Member student1(
        "M003",
        "Student One",
        MemberRole::Student
    );

    Member student2(
        "M004",
        "Student Two",
        MemberRole::Student
    );

    library.addBook(book);

    library.addMember(student1);
    library.addMember(student2);

    // First member borrows the only copy
    library.borrowBook(
        "M003",
        "9780132350884"
    );

    // Second member reserves it
    library.reserveBook(
        "M004",
        "9780132350884"
    );

    std::string log =
        readLogFile();

    EXPECT_NE(
        log.find(
            "RESERVATION M004 9780132350884"
        ),
        std::string::npos
    );
}

