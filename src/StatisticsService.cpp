#include "StatisticsService.h"
#include <iostream>
#include <iomanip>
#include "Library.h"

#include <algorithm>
#include <chrono>
#include <unordered_map>

LibraryStatistics StatisticsService::generate(
    const Library& library
)
{
    LibraryStatistics statistics{};

    statistics.activeMembers =
        library.getMembers().size();

    statistics.totalFinesCollected =
    library.getTotalFinesCollected();

    statistics.currentOverdueCount = 0;

    std::unordered_map<std::string, int> borrowCounts;

    for (const auto& entry :
         library.getBorrowRecords())
    {
        const BorrowRecord& record =
            entry.second;

        borrowCounts[
            record.getBookISBN()
        ]++;
    }

    for (const auto& entry : borrowCounts)
    {
        const std::string& isbn =
            entry.first;

        int count =
            entry.second;

        const Book& book =
            library.getBook(isbn);

        statistics.mostBorrowedBooks.push_back(
            {
                isbn,
                book.getTitle(),
                count
            }
        );
    }

    std::sort(
        statistics.mostBorrowedBooks.begin(),
        statistics.mostBorrowedBooks.end(),
        [](const BookBorrowStatistics& a,
        const BookBorrowStatistics& b)
        {
            return a.borrowCount >
                b.borrowCount;
        }
    );

    if (statistics.mostBorrowedBooks.size() > 3)
    {
        statistics.mostBorrowedBooks.resize(3);
    }

    auto now =
    std::chrono::system_clock::now();

for (const auto& entry :
     library.getBorrowRecords())
{
    const BorrowRecord& record =
        entry.second;

    if (!record.isReturned() &&
        now > record.getDueDate())
    {
        statistics.currentOverdueCount++;
    }
}

    return statistics;
}

void StatisticsService::display(
    const LibraryStatistics& statistics
)
{
    std::cout
        << "\n========== LIBRARY STATISTICS ==========\n\n";

    std::cout << "Most Borrowed:\n";

    int rank = 1;

    for (const auto& book :
         statistics.mostBorrowedBooks)
    {
        std::cout
            << rank
            << ". "
            << std::left
            << std::setw(20)
            << book.title
            << book.borrowCount
            << " borrows\n";

        rank++;
    }

    std::cout << '\n';

    std::cout
        << "Active Members:      "
        << statistics.activeMembers
        << '\n';

    std::cout
        << "Total Fines:         Rs."
        << std::fixed
        << std::setprecision(2)
        << statistics.totalFinesCollected
        << '\n';

    std::cout
        << "Overdue Books:       "
        << statistics.currentOverdueCount
        << '\n';

    std::cout
        << "\n=========================================\n";
}