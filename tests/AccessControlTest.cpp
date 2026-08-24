#include <gtest/gtest.h>
#include "AccessControl.h"

// Test case to verify that a student cannot add a book to the library
TEST(AccessControlTest, StudentCannotAddBook)
{
    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    AccessControl accessControl;

    bool result = accessControl.isAuthorized(
        student,
        Operation::AddBook
    );

    EXPECT_FALSE(result);
}

// Test case to verify that a faculty member cannot add a book to the library
TEST(AccessControlTest, FacultyCannotAddBook)
{
    Member faculty(
        "F001",
        "Dr. Smith",
        MemberRole::Faculty
    );

    AccessControl accessControl;

    bool result = accessControl.isAuthorized(
        faculty,
        Operation::AddBook
    );

    EXPECT_FALSE(result);
}

// Test case to verify that a librarian can add a book to the library
TEST(AccessControlTest, LibrarianCanAddBook)
{
    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    AccessControl accessControl;

    bool result = accessControl.isAuthorized(
        librarian,
        Operation::AddBook
    );

    EXPECT_TRUE(result);
}

// Test case to verify that a student cannot remove a book from the library
TEST(AccessControlTest, StudentCannotRemoveBook)
{
    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    AccessControl accessControl;

    EXPECT_FALSE(
        accessControl.isAuthorized(
            student,
            Operation::RemoveBook
        )
    );
}

// Test case to verify that a faculty member cannot remove a book from the library
TEST(AccessControlTest, FacultyCannotRemoveBook)  
{
    Member faculty(
        "F001",
        "Dr. Smith",
        MemberRole::Faculty
    );

    AccessControl accessControl;

    EXPECT_FALSE(
        accessControl.isAuthorized(
            faculty,
            Operation::RemoveBook
        )
    );
}       

// Test case to verify that a librarian can remove a book from the library
TEST(AccessControlTest, LibrarianCanRemoveBook) 
{
    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    AccessControl accessControl;

    EXPECT_TRUE(
        accessControl.isAuthorized(
            librarian,
            Operation::RemoveBook
        )
    );
}

// Test case to verify that a student cannot update a book in the library
TEST(AccessControlTest, StudentCannotUpdateBook)
{
    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    AccessControl accessControl;

    EXPECT_FALSE(
        accessControl.isAuthorized(
            student,
            Operation::UpdateBook
        )
    );
}

// Test case to verify that a faculty member cannot update a book in the library
TEST(AccessControlTest, FacultyCannotUpdateBook)
{
    Member faculty(
        "F001",
        "Dr. Smith",
        MemberRole::Faculty
    );

    AccessControl accessControl;

    EXPECT_FALSE(
        accessControl.isAuthorized(
            faculty,
            Operation::UpdateBook
        )
    );
}

// Test case to verify that a librarian can update a book in the library
TEST(AccessControlTest, LibrarianCanUpdateBook)
{
    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    AccessControl accessControl;

    EXPECT_TRUE(
        accessControl.isAuthorized(
            librarian,
            Operation::UpdateBook
        )
    );
}

// Test case to verify that a student can search for a book in the library
TEST(AccessControlTest, StudentCanSearchBook)
{
    Member student(
        "S001",
        "Keerthana",
        MemberRole::Student
    );

    AccessControl accessControl;

    EXPECT_TRUE(
        accessControl.isAuthorized(
            student,
            Operation::SearchBook
        )
    );
}

// Test case to verify that a faculty member can search for a book in the library
TEST(AccessControlTest, FacultyCanSearchBook)
{
    Member faculty(
        "F001",
        "Faculty Member",
        MemberRole::Faculty
    );

    AccessControl accessControl;

    EXPECT_TRUE(
        accessControl.isAuthorized(
            faculty,
            Operation::SearchBook
        )
    );
}

// Test case to verify that a librarian can search for a book in the library
TEST(AccessControlTest, LibrarianCanSearchBook)
{
    Member librarian(
        "L001",
        "Librarian",
        MemberRole::Librarian
    );

    AccessControl accessControl;

    EXPECT_TRUE(
        accessControl.isAuthorized(
            librarian,
            Operation::SearchBook
        )
    );
}