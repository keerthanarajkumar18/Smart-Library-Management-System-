#include <gtest/gtest.h>

#include "StandardFineStrategy.h"
#include "RoleBasedFineStrategy.h"

#include <chrono>

using Clock = std::chrono::system_clock;

BorrowRecord createRecord(int daysLate)
{
    auto dueDate = Clock::now();

    auto returnDate =
        dueDate + std::chrono::hours(24 * daysLate);

    BorrowRecord record(
        "BR001",
        "9780132350884",
        "M001",
        dueDate - std::chrono::hours(24 * 7),
        dueDate
    );

    record.markReturned(returnDate);

    return record;
}

// Test case to verify no fine is calculated when a book is returned on time
TEST(StandardFineStrategyTest, NoFineWhenReturnedOnTime)
{
    StandardFineStrategy strategy;

    Member student(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    BorrowRecord record = createRecord(0);

    EXPECT_DOUBLE_EQ(
        strategy.calculateFine(record, student),
        0.0
    );
}

// Test case to verify the standard fine calculation for an overdue book
TEST(StandardFineStrategyTest, CalculatesFineForOverdueBook)
{
    StandardFineStrategy strategy(10.0);

    Member student(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    BorrowRecord record = createRecord(3);

    EXPECT_DOUBLE_EQ(
        strategy.calculateFine(record, student),
        30.0
    );
}

// Test case for student role in RoleBasedFineStrategy
TEST(RoleBasedFineStrategyTest, StudentPaysStandardRate)
{
    RoleBasedFineStrategy strategy(
        10.0,  // student rate
        5.0,   // faculty rate
        0,     // student grace days
        2      // faculty grace days
    );

    Member student(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    BorrowRecord record = createRecord(3);

    EXPECT_DOUBLE_EQ(
        strategy.calculateFine(record, student),
        30.0
    );
}

// Test case for faculty role in RoleBasedFineStrategy in grace period
TEST(RoleBasedFineStrategyTest, FacultyGetsGracePeriod)
{
    RoleBasedFineStrategy strategy(
        10.0,
        5.0,
        0,
        2
    );

    Member faculty(
        "M002",
        "Professor",
        MemberRole::Faculty
    );

    BorrowRecord record = createRecord(2);

    EXPECT_DOUBLE_EQ(
        strategy.calculateFine(record, faculty),
        0.0
    );
}

// Test case for faculty role in RoleBasedFineStrategy after grace period
TEST(RoleBasedFineStrategyTest, FacultyPaysAfterGracePeriod)
{
    RoleBasedFineStrategy strategy(
        10.0,
        5.0,
        0,
        2
    );

    Member faculty(
        "M002",
        "Professor",
        MemberRole::Faculty
    );

    BorrowRecord record = createRecord(5);

    EXPECT_DOUBLE_EQ(
        strategy.calculateFine(record, faculty),
        15.0
    );
}

