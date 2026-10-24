#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

// Purpose: General utility functions for string formatting and safe terminal I/O.
// Responsibilities: Parse input safely, manipulate strings, clear output displays.
// Data Structure Used: None
// Time Complexity: O(N) for string transformations | Space Complexity: O(N)
// Dependencies: <string>
class Utilities {
public:
    // Purpose: Clear console display | Parameters: None | Return Value: None | Complexity: O(1)
    static void clearConsole();

    // Purpose: Pause execution waiting for Enter | Parameters: None | Return Value: None | Complexity: O(1)
    static void pressEnterToContinue();

    // Purpose: Trim leading and trailing whitespace | Parameters: str (const std::string&) | Return Value: std::string | Complexity: O(N)
    static std::string trim(const std::string& str);

    // Purpose: Convert string to uppercase | Parameters: str (const std::string&) | Return Value: std::string | Complexity: O(N)
    static std::string toUpper(const std::string& str);

    // Purpose: Safely get integer from standard input | Parameters: prompt (const std::string&), minVal (int), maxVal (int) | Return Value: int | Complexity: O(1)
    static int getIntegerInput(const std::string& prompt, int minVal, int maxVal);

    // Purpose: Safely get double from standard input | Parameters: prompt (const std::string&), minVal (double), maxVal (double) | Return Value: double | Complexity: O(1)
    static double getDoubleInput(const std::string& prompt, double minVal, double maxVal);

    // Purpose: Safely get string from standard input | Parameters: prompt (const std::string&), allowEmpty (bool) | Return Value: std::string | Complexity: O(1)
    static std::string getStringInput(const std::string& prompt, bool allowEmpty = false);
};

#endif // UTILITIES_H
