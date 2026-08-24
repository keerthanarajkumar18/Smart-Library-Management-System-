#include "BorrowRecord.h"

BorrowRecord::BorrowRecord(
    const std::string& recordId,
    const std::string& bookISBN,
    const std::string& memberId,
    std::chrono::system_clock::time_point borrowDate,
    std::chrono::system_clock::time_point dueDate
) : recordId(recordId),
    bookISBN(bookISBN),
    memberId(memberId),
    borrowDate(borrowDate),
    dueDate(dueDate),
    returned(false) {}

const std::string& BorrowRecord::getRecordId() const 
{
    return recordId;
}

const std::string& BorrowRecord::getBookISBN() const 
{
    return bookISBN;
}

const std::string& BorrowRecord::getMemberId() const
{
    return memberId;
}

std::chrono::system_clock::time_point
BorrowRecord::getBorrowDate() const
{
    return borrowDate;
}

std::chrono::system_clock::time_point
BorrowRecord::getDueDate() const
{
    return dueDate;
}

std::chrono::system_clock::time_point
BorrowRecord::getReturnDate() const
{
    return returnDate;
}

bool BorrowRecord::isReturned() const
{
    return returned;
}

void BorrowRecord::markReturned(
    std::chrono::system_clock::time_point date
)
{
    if (!returned)
    {
        returnDate = date;
        returned = true;
    }
}