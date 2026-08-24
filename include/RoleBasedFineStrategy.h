#ifndef ROLE_BASED_FINE_STRATEGY_H
#define ROLE_BASED_FINE_STRATEGY_H

#include "FineStrategy.h"

class RoleBasedFineStrategy : public FineStrategy
{
private:
    double studentRate;
    double facultyRate;

    int studentGraceDays;
    int facultyGraceDays;

public:

    RoleBasedFineStrategy(
        double studentRate = 10.0,
        double facultyRate = 5.0,
        int studentGraceDays = 0,
        int facultyGraceDays = 2
    );

    double calculateFine(
        const BorrowRecord& record,
        const Member& member
    ) const override;
};

#endif // ROLE_BASED_FINE_STRATEGY_H