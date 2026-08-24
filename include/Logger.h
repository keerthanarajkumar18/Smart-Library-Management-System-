#ifndef LOGGER_H
#define LOGGER_H

#include <string>
enum class LogAction
{
    BORROW,
    RETURN,
    FINE,
    RESERVATION
};

class Logger
{
public:

    static void log(
        LogAction action,
        const std::string& memberId,
        const std::string& details
    );
};

#endif