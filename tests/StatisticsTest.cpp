#include <gtest/gtest.h>

#include "Library.h"
#include "StatisticsService.h"
#include "Book.h"
#include "Member.h"
#include <chrono>

TEST(StatisticsTest, InitialTotalFinesIsZero)
{
    Library library;

    EXPECT_DOUBLE_EQ(
        library.getTotalFinesCollected(),
        0.0
    );
}

TEST(
    StatisticsTest,
    NoOverdueBooksInitially
)
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

    LibraryStatistics statistics =
        StatisticsService::generate(
            library
        );

    EXPECT_EQ(
        statistics.currentOverdueCount,
        0
    );
}

TEST(
    StatisticsTest,
    CountsOverdueBooks
)
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

    auto now =
        std::chrono::system_clock::now();

    auto borrowDate =
        now - std::chrono::hours(24 * 20);

    auto dueDate =
        now - std::chrono::hours(24 * 6);

    library.addBorrowRecordForTesting(
        "BR001",
        "M001",
        "9780132350884",
        borrowDate,
        dueDate
    );

    LibraryStatistics statistics =
        StatisticsService::generate(
            library
        );

    EXPECT_EQ(
        statistics.currentOverdueCount,
        1
    );
}

TEST(
    StatisticsTest,
    CanDisplayStatistics
)
{
    LibraryStatistics statistics;

    statistics.mostBorrowedBooks.push_back(
        {
            "9780132350884",
            "Clean Code",
            12
        }
    );

    statistics.mostBorrowedBooks.push_back(
        {
            "9780321563842",
            "C++ Primer",
            9
        }
    );

    statistics.activeMembers = 25;

    statistics.totalFinesCollected = 450.0;

    statistics.currentOverdueCount = 3;

    EXPECT_NO_THROW(
        StatisticsService::display(statistics)
    );
}