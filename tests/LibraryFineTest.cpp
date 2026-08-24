#include <gtest/gtest.h>

#include "Library.h"
#include "FineStrategy.h"

#include <memory>

// Test Strategy
class TestFineStrategy : public FineStrategy
{
public:

    double calculateFine(
        const BorrowRecord& record,
        const Member& member
    ) const override
    {
        // Fixed value used only to verify
        // that Library calls the injected strategy.
        return 999.0;
    }
};

// Test Fixture
class LibraryFineTest : public ::testing::Test
{
protected:

    Library library;

    void SetUp() override
    {
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
    }
};

// Test 1
TEST_F(
    LibraryFineTest,
    LibraryUsesInjectedFineStrategy
)
{
    library.setFineStrategy(
        std::make_shared<TestFineStrategy>()
    );

    library.borrowBook(
        "M001",
        "9780132350884"
    );

    double fine = library.returnBook(
        "M001",
        "9780132350884"
    );

    EXPECT_DOUBLE_EQ(fine, 999.0);
}

// Test 2
TEST_F(
    LibraryFineTest,
    ReturnWithoutStrategyReturnsZeroFine
)
{
    library.borrowBook(
        "M001",
        "9780132350884"
    );

    double fine = library.returnBook(
        "M001",
        "9780132350884"
    );

    EXPECT_DOUBLE_EQ(fine, 0.0);
}