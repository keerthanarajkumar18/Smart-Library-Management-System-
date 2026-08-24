#include "RoleBasedFineStrategy.h"

#include <chrono>

RoleBasedFineStrategy::RoleBasedFineStrategy(
    double studentRate,
    double facultyRate,
    int studentGraceDays,
    int facultyGraceDays
)
    : studentRate(studentRate),
      facultyRate(facultyRate),
      studentGraceDays(studentGraceDays),
      facultyGraceDays(facultyGraceDays)
{
}

double RoleBasedFineStrategy::calculateFine(
    const BorrowRecord& record,
    const Member& member
) const
{
    auto returnDate = record.getReturnDate();
    auto dueDate = record.getDueDate();

    if (returnDate <= dueDate)
    {
        return 0.0;
    }

    auto duration =
        std::chrono::duration_cast<
            std::chrono::hours
        >(returnDate - dueDate);

    long daysLate =
        duration.count() / 24;

    int graceDays = 0;
    double dailyRate = 0.0;

    switch (member.getRole())
    {
        case MemberRole::Student:

            graceDays = studentGraceDays;
            dailyRate = studentRate;
            break;

        case MemberRole::Faculty:

            graceDays = facultyGraceDays;
            dailyRate = facultyRate;
            break;

        case MemberRole::Librarian:

            return 0.0;
    }

    long chargeableDays =
        daysLate - graceDays;

    if (chargeableDays <= 0)
    {
        return 0.0;
    }

    return chargeableDays * dailyRate;
}