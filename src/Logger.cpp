#include "Logger.h"

#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

static std::string actionToString(
    LogAction action
)
{
    switch (action)
    {
        case LogAction::BORROW:
            return "BORROW";

        case LogAction::RETURN:
            return "RETURN";

        case LogAction::FINE:
            return "FINE";

        case LogAction::RESERVATION:
            return "RESERVATION";
    }

    return "UNKNOWN";
}

void Logger::log(
    LogAction action,
    const std::string& memberId,
    const std::string& details
)
{
    std::ofstream logFile(
        "library.log",
        std::ios::app
    );

    if (!logFile)
    {
        return;
    }

    auto now =
        std::chrono::system_clock::now();

    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

    localTime = *std::localtime(&currentTime);

    logFile
        << "["
        << std::put_time(
            &localTime,
            "%Y-%m-%d %H:%M:%S"
        )
        << "] "
        << actionToString(action)
        << " "
        << memberId
        << " "
        << details
        << '\n';
}