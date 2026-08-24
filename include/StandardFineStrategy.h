#ifndef STANDARD_FINE_STRATEGY_H
#define STANDARD_FINE_STRATEGY_H

#include "FineStrategy.h"

class StandardFineStrategy : public FineStrategy
{
private:
    double dailyRate;

public:

    explicit StandardFineStrategy(
        double dailyRate = 10.0
    );

    double calculateFine(
        const BorrowRecord& record, 
        const Member& member
    ) const override;
};

#endif // STANDARD_FINE_STRATEGY_H