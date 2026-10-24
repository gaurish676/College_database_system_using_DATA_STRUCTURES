#include "../include/Logger.h"
#include <iostream>

// Purpose: Print colored log to console | Parameters: message (const std::string&), level (LogLevel) | Return Value: None | Complexity: O(M)
void Logger::log(const std::string& message, LogLevel level) {
    switch (level) {
        case LogLevel::INFO:
            std::cout << "\033[36m[INFO] " << message << "\033[0m\n";
            break;
        case LogLevel::WARNING:
            std::cout << "\033[33m[WARNING] " << message << "\033[0m\n";
            break;
        case LogLevel::ERROR:
            std::cout << "\033[31m[ERROR] " << message << "\033[0m\n";
            break;
        case LogLevel::SUCCESS:
            std::cout << "\033[32m[SUCCESS] " << message << "\033[0m\n";
            break;
    }
}

// Purpose: Print info log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
void Logger::info(const std::string& msg) {
    log(msg, LogLevel::INFO);
}

// Purpose: Print warning log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
void Logger::warn(const std::string& msg) {
    log(msg, LogLevel::WARNING);
}

// Purpose: Print error log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
void Logger::error(const std::string& msg) {
    log(msg, LogLevel::ERROR);
}

// Purpose: Print success log | Parameters: msg (const std::string&) | Return Value: None | Complexity: O(M)
void Logger::success(const std::string& msg) {
    log(msg, LogLevel::SUCCESS);
}
