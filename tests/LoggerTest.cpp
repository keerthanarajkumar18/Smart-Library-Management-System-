#include <gtest/gtest.h>
#include <regex>
#include <fstream>
#include <string>

#include "Logger.h"

TEST(LoggerTest, CreatesLogFile)
{
    Logger::log(
    LogAction::BORROW,
    "M001",
    "ISBN123"
);

    std::ifstream logFile(
        "library.log"
    );

    EXPECT_TRUE(logFile.is_open());
}

TEST(LoggerTest, LogsMultipleOperations)
{
    Logger::log(
    LogAction::BORROW,
    "M001",
    "ISBN123"
);
   Logger::log(
    LogAction::RETURN,
    "M001",
    "ISBN123"
);

Logger::log(
    LogAction::FINE,
    "M001",
    "Rs20"
);

Logger::log(
    LogAction::RESERVATION,
    "M002",
    "ISBN123"
);

    std::ifstream logFile(
        "library.log"
    );

    ASSERT_TRUE(logFile.is_open());

    std::string line;

    int lineCount = 0;

    while (std::getline(logFile, line))
    {
        ++lineCount;
    }

    EXPECT_GE(lineCount, 4);
}

TEST(LoggerTest, LogFormatIsCorrect)
{
    Logger::log(
        LogAction::BORROW,
        "M001",
        "ISBN123"
    );

    std::ifstream logFile(
        "library.log"
    );

    ASSERT_TRUE(logFile.is_open());

    std::string lastLine;
    std::string line;

    while (std::getline(logFile, line))
    {
        lastLine = line;
    }

    std::regex pattern(
        R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\] BORROW M001 ISBN123)"
    );

    EXPECT_TRUE(
        std::regex_match(
            lastLine,
            pattern
        )
    );
}