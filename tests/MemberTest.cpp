#include <gtest/gtest.h>
#include "Member.h"

// Test case to verify the creation of a Member object with Student role
TEST(MemberTest, CreatesStudentCorrectly)
{
    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    EXPECT_EQ(member.getMemberId(), "M001");
    EXPECT_EQ(member.getName(), "Keerthana");
    EXPECT_EQ(member.getRole(), MemberRole::Student);
}

// Test case to verify the creation of a Member object with Faculty role
TEST(MemberTest, CreatesFacultyCorrectly)
{
    Member member(
        "M002",
        "Arun",
        MemberRole::Faculty
    );

    EXPECT_EQ(member.getRole(), MemberRole::Faculty);
}

// Test case to verify the creation of a Member object with Librarian role
TEST(MemberTest, CreatesLibrarianCorrectly)
{
    Member member(
        "M003",
        "Admin",
        MemberRole::Librarian
    );

    EXPECT_EQ(member.getRole(), MemberRole::Librarian);
}

// Test case to verify that borrowing history is initially empty for a new Member object
TEST(MemberTest, BorrowingHistoryStartsEmpty)
{
    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    EXPECT_TRUE(member.getBorrowingHistory().empty());
}

// Test case to verify that adding a borrow record updates the borrowing history of a Member object
TEST(MemberTest, AddsBorrowRecord)
{
    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    member.addBorrowRecord("BR001");

    ASSERT_EQ(member.getBorrowingHistory().size(), 1);
    EXPECT_EQ(member.getBorrowingHistory()[0], "BR001");
}

// Test case to verify that multiple borrow records can be added to the borrowing history of a Member object
TEST(MemberTest, StoresMultipleBorrowRecords)
{
    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    member.addBorrowRecord("BR001");
    member.addBorrowRecord("BR002");
    member.addBorrowRecord("BR003");

    ASSERT_EQ(member.getBorrowingHistory().size(), 3);

    EXPECT_EQ(member.getBorrowingHistory()[0], "BR001");
    EXPECT_EQ(member.getBorrowingHistory()[1], "BR002");
    EXPECT_EQ(member.getBorrowingHistory()[2], "BR003");
}