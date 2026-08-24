#include <gtest/gtest.h>
#include <memory>
#include "Library.h"
#include "LibraryService.h"
#include "Book.h"
#include "Member.h"
#include "LibraryException.h"
#include "StatisticsService.h"
#include "FineStrategy.h"
#include "RoleBasedFineStrategy.h"
#include "StandardFineStrategy.h"

class EndToEndTest : public ::testing::Test
{
protected:

    Library library;
    std::unique_ptr<LibraryService> service;

    void SetUp() override
    {
        service =
            std::make_unique<LibraryService>(library);

        library.setFineStrategy(
            std::make_shared<RoleBasedFineStrategy>()
        );

        Book bookA(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            2
        );

        Book bookB(
            "C++ Primer",
            "Stanley Lippman",
            "9780321714114",
            "Programming",
            2
        );

        Book bookC(
            "Effective C++",
            "Scott Meyers",
            "9780321334879",
            "Programming",
            1
        );

        library.addBook(bookA);
        library.addBook(bookB);
        library.addBook(bookC);

        Member student1(
            "S001",
            "Student One",
            MemberRole::Student
        );

        Member student2(
            "S002",
            "Student Two",
            MemberRole::Student
        );

        Member faculty(
            "F001",
            "Faculty One",
            MemberRole::Faculty
        );

        library.addMember(student1);
        library.addMember(student2);
        library.addMember(faculty);
    }
};

TEST_F(
    EndToEndTest,
    StudentCanBorrowBook
)
{
    EXPECT_NO_THROW(
        service->borrowBook(
            "S001",
            "9780132350884"
        )
    );

    EXPECT_EQ(
        library.getBook(
            "9780132350884"
        ).getAvailableCopies(),
        1
    );
}

TEST_F(
    EndToEndTest,
    FacultyCanBorrowBook
)
{
    EXPECT_NO_THROW(
        service->borrowBook(
            "F001",
            "9780321714114"
        )
    );

    EXPECT_EQ(
        library.getBook(
            "9780321714114"
        ).getAvailableCopies(),
        1
    );
}

TEST_F(
    EndToEndTest,
    StudentCanReserveUnavailableBook
)
{
    // First student borrows the only copy
    EXPECT_NO_THROW(
        service->borrowBook(
            "S001",
            "9780321334879"
        )
    );

    // No copies should remain
    EXPECT_EQ(
        library.getBook(
            "9780321334879"
        ).getAvailableCopies(),
        0
    );

    // Second student reserves the unavailable book
    EXPECT_NO_THROW(
        service->reserveBook(
            "S002",
            "9780321334879"
        )
    );

    // Verify reservation
    const ReservationQueue& queue =
        library.getReservationQueue(
            "9780321334879"
        );

    EXPECT_FALSE(
        queue.isEmpty()
    );

    EXPECT_EQ(
        queue.front(),
        "S002"
    );
}

TEST_F(
    EndToEndTest,
    ReturningBookProcessesReservation
)
{
    // S001 borrows the only copy
    service->borrowBook(
        "S001",
        "9780321334879"
    );

    // S002 reserves the unavailable book
    service->reserveBook(
        "S002",
        "9780321334879"
    );

    // S001 returns the book
    EXPECT_NO_THROW(
        service->returnBook(
            "S001",
            "9780321334879"
        )
    );

    // Book should become available again
    EXPECT_EQ(
        library.getBook(
            "9780321334879"
        ).getAvailableCopies(),
        1
    );

    // Reservation queue should now be empty
    const ReservationQueue& queue =
        library.getReservationQueue(
            "9780321334879"
        );

    EXPECT_TRUE(
        queue.isEmpty()
    );
}

TEST_F(
    EndToEndTest,
    StatisticsReflectLibraryActivity
)
{
    // S001 borrows Clean Code
    service->borrowBook(
        "S001",
        "9780132350884"
    );

    // F001 borrows C++ Primer
    service->borrowBook(
        "F001",
        "9780321714114"
    );

    // S001 borrows Effective C++
    service->borrowBook(
        "S001",
        "9780321334879"
    );

    // Generate statistics
    LibraryStatistics statistics =
        StatisticsService::generate(
            library
        );

    // We have 3 members registered
    EXPECT_EQ(
        statistics.activeMembers,
        3
    );

    // Clean Code has been borrowed once
    EXPECT_EQ(
        statistics.mostBorrowedBooks.front().borrowCount,
        1
    );

    // No book is overdue yet because the three
    // borrow operations happened just now.
    EXPECT_EQ(
        statistics.currentOverdueCount,
        0
    );
}

TEST_F(
    EndToEndTest,
    CompleteLibraryWorkflow
)
{
    // =====================================================
    // Day 1
    // =====================================================

    // Student borrows Book A
    EXPECT_NO_THROW(
        service->borrowBook(
            "S001",
            "9780132350884"
        )
    );

    // Faculty borrows Book B
    EXPECT_NO_THROW(
        service->borrowBook(
            "F001",
            "9780321714114"
        )
    );

    // Student 2 borrows Book C
    EXPECT_NO_THROW(
        service->borrowBook(
            "S002",
            "9780321334879"
        )
    );

    // Book C has no copies remaining
    EXPECT_EQ(
        library.getBook(
            "9780321334879"
        ).getAvailableCopies(),
        0
    );

    // =====================================================
    // Day 1 - Reservation
    // =====================================================

    // Student 1 reserves Book C
    EXPECT_NO_THROW(
        service->reserveBook(
            "S001",
            "9780321334879"
        )
    );

    const ReservationQueue& queue =
        library.getReservationQueue(
            "9780321334879"
        );

    EXPECT_FALSE(
        queue.isEmpty()
    );

    EXPECT_EQ(
        queue.front(),
        "S001"
    );

    // =====================================================
    // Day 2 - Return
    // =====================================================

    EXPECT_NO_THROW(
        service->returnBook(
            "S002",
            "9780321334879"
        )
    );

    // Book becomes available
    EXPECT_EQ(
        library.getBook(
            "9780321334879"
        ).getAvailableCopies(),
        1
    );

    // Reservation is processed
    EXPECT_TRUE(
        library
            .getReservationQueue(
                "9780321334879"
            )
            .isEmpty()
    );

    // =====================================================
    // Final Statistics
    // =====================================================

    LibraryStatistics statistics =
        StatisticsService::generate(
            library
        );

    // Three members exist
    EXPECT_EQ(
        statistics.activeMembers,
        3
    );
}