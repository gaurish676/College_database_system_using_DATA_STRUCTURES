#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <cstdint>

enum class LogLevel : uint8_t {
    INFO,
    WARNING,
    ERROR,
    SUCCESS
};

// Purpose: Manages formatting and output of system logs with rich console styling.
// Responsibilities: Format messages based on LogLevel, output colored status logs.
// Data Structure Used: None
// Time Complexity: O(M) where M is message length | Space Complexity: O(1)
// Dependencies: <string>, <cstdint>
class Logger {
public:
    // Purpose: Print colored log to console | Parameters: message (const std::string&), level (LogLevel) | Return Value: None | Complexity: O(M)
    static void log(const std::string& message, LogLevel level = LogLevel::INFO);

    // Purpose: Print info log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
    static void info(const std::string& msg);

    // Purpose: Print warning log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
    static void warn(const std::string& msg);

    // Purpose: Print error log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
    static void error(const std::string& msg);

    // Purpose: Print success log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
    static void success(const std::string& msg);
};

#endif // LOGGER_H
