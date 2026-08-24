#include <gtest/gtest.h>
#include "Library.h"

TEST(LibraryBorrowTest, BorrowDecreaseAvailability)
{
    Library library;

    library.addBook(Book("Clean Code", "Robert C. Martin", "9780132350884", "Programming", 2));
    library.addMember(Member("M001", "Keerthana", MemberRole::Student));
    library.borrowBook("M001", "9780132350884");

    EXPECT_EQ(library.getBook("9780132350884").getAvailableCopies(), 1);
}

TEST(LibraryBorrowTest, BorrowCreatesRecord)
{
    Library library;

    library.addBook(Book("Clean Code", "Robert C. Martin", "9780132350884", "Programming", 2));
    library.addMember(Member("M001", "Keerthana", MemberRole::Student));
    library.borrowBook("M001", "9780132350884");

    const BorrowRecord& record = library.getBorrowRecord("BR001");
    EXPECT_EQ(record.getMemberId(), "M001");
    EXPECT_EQ(record.getBookISBN(), "9780132350884");
    EXPECT_FALSE(record.isReturned());
}

TEST(LibraryBorrowTest, BorrowAddsHistory)
{
    Library library;

    library.addBook(Book("Clean Code", "Robert C. Martin", "9780132350884", "Programming", 2));
    library.addMember(Member("M001", "Keerthana", MemberRole::Student));
    library.borrowBook("M001", "9780132350884");

    const auto& history = library.getMember("M001").getBorrowingHistory();

    ASSERT_EQ(history.size(), 1);
    EXPECT_EQ(history[0], "BR001");
}

TEST(LibraryBorrowTest, CannotBorrowUnavailableBook)
{
    Library library;

    library.addBook(Book("Clean Code", "Robert C. Martin", "9780132350884", "Programming", 1));
    library.addMember(Member("M001", "Keerthana", MemberRole::Student));
    library.borrowBook("M001", "9780132350884");

    EXPECT_THROW(library.borrowBook("M001", "9780132350884"), std::runtime_error);
}

TEST(LibraryBorrowTest, CannotBorrowNonexistentBook)
{
    Library library;

    library.addMember(Member("M001", "Keerthana", MemberRole::Student));

    EXPECT_THROW(library.borrowBook("M001", "9780132350884"), std::runtime_error);
}

TEST(LibraryReturnTest, ReturnIncreasesAvailability)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            2
        )
    );

    library.addMember(
        Member(
            "M001",
            "Keerthana",
            MemberRole::Student
        )
    );

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    library.returnBook(
        "M001",
        "9780132350884"
    );

    EXPECT_EQ(
        library.getBook("9780132350884")
            .getAvailableCopies(),
        2
    );
}


TEST(LibraryReturnTest, ReturnClosesRecord)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            2
        )
    );

    library.addMember(
        Member(
            "M001",
            "Keerthana",
            MemberRole::Student
        )
    );

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    library.returnBook(
        "M001",
        "9780132350884"
    );

    const BorrowRecord& record =
        library.getBorrowRecord("BR001");

    EXPECT_TRUE(
        record.isReturned()
    );
}


TEST(LibraryReturnTest, CannotReturnTwice)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            2
        )
    );

    library.addMember(
        Member(
            "M001",
            "Keerthana",
            MemberRole::Student
        )
    );

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    library.returnBook(
        "M001",
        "9780132350884"
    );

    EXPECT_THROW(
        library.returnBook(
            "M001",
            "9780132350884"
        ),
        std::runtime_error
    );
}


TEST(LibraryReturnTest, CannotReturnWithoutBorrowing)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            2
        )
    );

    library.addMember(
        Member(
            "M001",
            "Keerthana",
            MemberRole::Student
        )
    );

    EXPECT_THROW(
        library.returnBook(
            "M001",
            "9780132350884"
        ),
        std::runtime_error
    );
}


TEST(LibraryReturnTest, WrongMemberCannotReturn)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            2
        )
    );

    library.addMember(
        Member(
            "M001",
            "Keerthana",
            MemberRole::Student
        )
    );

    library.addMember(
        Member(
            "M002",
            "Arun",
            MemberRole::Student
        )
    );

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    EXPECT_THROW(
        library.returnBook(
            "M002",
            "9780132350884"
        ),
        std::runtime_error
    );
}