#include "StandardFineStrategy.h"
#include <chrono>

StandardFineStrategy::StandardFineStrategy(
    double dailyRate
)
    : dailyRate(dailyRate)
{
}

double StandardFineStrategy::calculateFine(
    const BorrowRecord& record,
    const Member& member
) const
{
    (void)member; // Unused parameter
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

    return daysLate * dailyRate;
}