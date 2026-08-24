#ifndef FINE_STRATEGY_H
#define FINE_STRATEGY_H

#include "BorrowRecord.h"
#include "Member.h"

class FineStrategy
{
    public:
        virtual double calculateFine(const BorrowRecord& record, const Member& member) const = 0;
        virtual ~FineStrategy() = default;
};

#endif // FINE_STRATEGY_H