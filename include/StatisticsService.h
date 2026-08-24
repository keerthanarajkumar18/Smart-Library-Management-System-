#ifndef STATISTICS_SERVICE_H
#define STATISTICS_SERVICE_H

#include "Statistics.h"

class Library;

class StatisticsService
{
public:

    static LibraryStatistics generate(
        const Library& library
    );

    static void display(
        const LibraryStatistics& statistics
    );
};

#endif