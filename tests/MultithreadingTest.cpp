#include <gtest/gtest.h>

#include <thread>
#include <vector>

#include "Library.h"
#include "Book.h"
#include "Member.h"
#include "LibraryException.h"

TEST(
    MultithreadingTest,
    OnlyOneThreadCanBorrowLastCopy
)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        1
    );

    Member member1(
        "M001",
        "Student 1",
        MemberRole::Student
    );

    Member member2(
        "M002",
        "Student 2",
        MemberRole::Student
    );

    library.addBook(book);

    library.addMember(member1);
    library.addMember(member2);

    std::vector<std::thread> threads;

    threads.emplace_back(
        [&library]()
        {
            try
            {
                library.borrowBook(
                    "M001",
                    "9780132350884"
                );
            }
            catch (const std::exception&)
            {
                // Expected for one of the threads
            }
        }
    );

    threads.emplace_back(
        [&library]()
        {
            try
            {
                library.borrowBook(
                    "M002",
                    "9780132350884"
                );
            }
            catch (const std::exception&)
            {
                // Expected for one of the threads
            }
        }
    );

    for (auto& thread : threads)
    {
        thread.join();
    }

    EXPECT_EQ(
        library.getBook(
            "9780132350884"
        ).getAvailableCopies(),
        0
    );
}

TEST(
    MultithreadingTest,
    ConcurrentReturnAndBorrow
)
{
    Library library;

    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        1
    );

    Member member1(
        "M001",
        "Student 1",
        MemberRole::Student
    );

    Member member2(
        "M002",
        "Student 2",
        MemberRole::Student
    );

    library.addBook(book);

    library.addMember(member1);
    library.addMember(member2);

    // M001 initially borrows the only copy
    library.borrowBook(
        "M001",
        "9780132350884"
    );

    EXPECT_EQ(
        library.getBook(
            "9780132350884"
        ).getAvailableCopies(),
        0
    );

    std::thread returnThread(
        [&library]()
        {
            try
            {
                library.returnBook(
                    "M001",
                    "9780132350884"
                );
            }
            catch (const std::exception&)
            {
                // Ignore exceptions for this test
            }
        }
    );

    std::thread borrowThread(
        [&library]()
        {
            try
            {
                library.borrowBook(
                    "M002",
                    "9780132350884"
                );
            }
            catch (const std::exception&)
            {
                // Borrow may happen before return
            }
        }
    );

    returnThread.join();
    borrowThread.join();

    EXPECT_GE(
        library.getBook(
            "9780132350884"
        ).getAvailableCopies(),
        0
    );
}

TEST(
    MultithreadingTest,
    MultipleThreadsCannotOverbookInventory
)
{
    Library library;

    Book book(
        "C++ Primer",
        "Stanley Lippman",
        "9780321714114",
        "Programming",
        3
    );

    library.addBook(book);

    // Create 10 members
    for (int i = 1; i <= 10; ++i)
    {
        std::string memberId =
            "M00" + std::to_string(i);

        std::string memberName =
            "Student " + std::to_string(i);

        Member member(
            memberId,
            memberName,
            MemberRole::Student
        );

        library.addMember(member);
    }

    std::vector<std::thread> threads;

    // 10 simultaneous borrowing attempts
    for (int i = 1; i <= 10; ++i)
    {
        std::string memberId =
            "M00" + std::to_string(i);

        threads.emplace_back(
            [&library, memberId]()
            {
                try
                {
                    library.borrowBook(
                        memberId,
                        "9780321714114"
                    );
                }
                catch (const std::exception&)
                {
                    // Expected when all copies are borrowed
                }
            }
        );
    }

    // Wait for every thread
    for (auto& thread : threads)
    {
        thread.join();
    }

    // Inventory must never become negative
    EXPECT_GE(
        library.getBook(
            "9780321714114"
        ).getAvailableCopies(),
        0
    );

    // All 3 copies should have been borrowed
    EXPECT_EQ(
        library.getBook(
            "9780321714114"
        ).getAvailableCopies(),
        0
    );
}