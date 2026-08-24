#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include <chrono>
#include <string>

class BorrowRecord
{
private:
    std::string recordId;
    std::string bookISBN;
    std::string memberId;

    std::chrono::system_clock::time_point borrowDate;
    std::chrono::system_clock::time_point dueDate;

    std::chrono::system_clock::time_point returnDate;

    bool returned;

public:
    BorrowRecord(
        const std::string& recordId,
        const std::string& bookISBN,
        const std::string& memberId,
        std::chrono::system_clock::time_point borrowDate,
        std::chrono::system_clock::time_point dueDate
    );

    const std::string& getRecordId() const;
    const std::string& getBookISBN() const;
    const std::string& getMemberId() const;

    std::chrono::system_clock::time_point getBorrowDate() const;
    std::chrono::system_clock::time_point getDueDate() const;
    std::chrono::system_clock::time_point getReturnDate() const;

    bool isReturned() const;

    void markReturned(
        std::chrono::system_clock::time_point returnDate
    );
};

#endif