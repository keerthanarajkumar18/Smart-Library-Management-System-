#include <gtest/gtest.h>
#include "Library.h"

//Test case to reserve unavailable book and check if the reservation queue is updated correctly
TEST(LibraryReservationTest, CanReserveUnavailableBook)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            1
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

    // M001 borrows the only copy
    library.borrowBook(
        "M001",
        "9780132350884"
    );

    // M002 reserves it
    library.reserveBook(
        "M002",
        "9780132350884"
    );

    const ReservationQueue& queue =
        library.getReservationQueue(
            "9780132350884"
        );

    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), "M002");
}

//Test case to verify that reservations are handled in FIFO order
TEST(LibraryReservationTest, ReservationsAreFIFO)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            1
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

    library.addMember(
        Member(
            "M003",
            "Priya",
            MemberRole::Student
        )
    );

    // M001 takes the only copy
    library.borrowBook(
        "M001",
        "9780132350884"
    );

    // M002 and M003 wait
    library.reserveBook(
        "M002",
        "9780132350884"
    );

    library.reserveBook(
        "M003",
        "9780132350884"
    );

    const ReservationQueue& queue =
        library.getReservationQueue(
            "9780132350884"
        );

    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), "M002");
}

//Test case to verify that when a book is returned, the first member in the reservation queue is notified and removed from the queue
TEST(LibraryReservationTest, ReturnNotifiesFirstMember)
{
    Library library;

    library.addBook(
        Book(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            1
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

    library.addMember(
        Member(
            "M003",
            "Priya",
            MemberRole::Student
        )
    );

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    library.reserveBook(
        "M002",
        "9780132350884"
    );

    library.reserveBook(
        "M003",
        "9780132350884"
    );

    library.returnBook(
        "M001",
        "9780132350884"
    );

    const ReservationQueue& queue =
        library.getReservationQueue(
            "9780132350884"
        );

    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), "M003");
    }

    