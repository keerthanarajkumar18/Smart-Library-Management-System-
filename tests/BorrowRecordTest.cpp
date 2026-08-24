#include <gtest/gtest.h>
#include "BorrowRecord.h"
#include <chrono>

// Test case to verify the creation of a BorrowRecord object and its properties
TEST(BorrowRecordTest, CreatesRecordCorrectly)
{
    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    BorrowRecord record(
        "BR001",
        "ISBN001",
        "M001",
        borrowDate,
        dueDate
    );

    EXPECT_EQ(record.getRecordId(), "BR001");
    EXPECT_EQ(record.getBookISBN(), "ISBN001");
    EXPECT_EQ(record.getMemberId(), "M001");
}

// Test case to verify that a BorrowRecord object is initially marked as not returned
TEST(BorrowRecordTest, RecordIsInitiallyNotReturned)
{
    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    BorrowRecord record(
        "BR001",
        "ISBN001",
        "M001",
        borrowDate,
        dueDate
    );

    EXPECT_FALSE(record.isReturned());
}

// Test case to verify that marking a BorrowRecord as returned updates its state correctly
TEST(BorrowRecordTest, MarkReturnedChangesState)
{
    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    BorrowRecord record(
        "BR001",
        "ISBN001",
        "M001",
        borrowDate,
        dueDate
    );

    auto returnDate =
        borrowDate + std::chrono::hours(24 * 5);

    record.markReturned(returnDate);

    EXPECT_TRUE(record.isReturned());
}

// Test case to verify that the return date is stored correctly when a BorrowRecord is marked as returned
TEST(BorrowRecordTest, StoresReturnDate)
{
    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    auto returnDate =
        borrowDate + std::chrono::hours(24 * 10);

    BorrowRecord record(
        "BR001",
        "ISBN001",
        "M001",
        borrowDate,
        dueDate
    );

    record.markReturned(returnDate);

    EXPECT_EQ(record.getReturnDate(), returnDate);
}

// Test case to verify that the due date is stored correctly in a BorrowRecord object
TEST(BorrowRecordTest, StoresDueDateCorrectly)
{
    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    BorrowRecord record(
        "BR001",
        "ISBN001",
        "M001",
        borrowDate,
        dueDate
    );

    EXPECT_EQ(record.getDueDate(), dueDate);
}

// Test case to verify that the borrow date is stored correctly in a BorrowRecord object
TEST(BorrowRecordTest, StoresBorrowDateCorrectly)
{
    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    BorrowRecord record(
        "BR001",
        "ISBN001",
        "M001",
        borrowDate,
        dueDate
    );

    EXPECT_EQ(record.getBorrowDate(), borrowDate);
}