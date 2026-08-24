#include <chrono>
#include <iostream>

#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"

int main()
{
    Book book(
        "Clean Code",
        "Robert C. Martin",
        "9780132350884",
        "Programming",
        5
    );

    Member member(
        "M001",
        "Keerthana",
        MemberRole::Student
    );

    auto borrowDate =
        std::chrono::system_clock::now();

    auto dueDate =
        borrowDate + std::chrono::hours(24 * 7);

    BorrowRecord record(
        "BR001",
        book.getISBN(),
        member.getMemberId(),
        borrowDate,
        dueDate
    );

    std::cout << "Record ID: "
              << record.getRecordId() << '\n';

    std::cout << "Returned: "
              << std::boolalpha
              << record.isReturned()
              << '\n';

    record.markReturned(
        std::chrono::system_clock::now()
    );

    std::cout << "Returned after update: "
              << record.isReturned()
              << '\n';

    return 0;
}