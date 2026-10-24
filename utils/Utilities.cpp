#include "../include/Utilities.h"
#include <iostream>
#include <limits>
#include <algorithm>

// Purpose: Clear console display | Parameters: None | Return Value: None | Complexity: O(1)
void Utilities::clearConsole() {
#if defined(_WIN32)
    int res = std::system("cls");
#else
    int res = std::system("clear");
#endif
    static_cast<void>(res);
}

// Purpose: Pause execution waiting for Enter | Parameters: None | Return Value: None | Complexity: O(1)
void Utilities::pressEnterToContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Purpose: Trim leading and trailing whitespace | Parameters: str (const std::string&) | Return Value: std::string | Complexity: O(N)
std::string Utilities::trim(const std::string& str) {
    if (str.empty()) return "";
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Purpose: Convert string to uppercase | Parameters: str (const std::string&) | Return Value: std::string | Complexity: O(N)
std::string Utilities::toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Purpose: Safely get integer from standard input | Parameters: prompt (const std::string&), minVal (int), maxVal (int) | Return Value: int | Complexity: O(1)
int Utilities::getIntegerInput(const std::string& prompt, int minVal, int maxVal) {
    int val = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (val >= minVal && val <= maxVal) {
                return val;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "\033[31m[ERROR] Invalid input! Enter an integer between " << minVal << " and " << maxVal << ".\033[0m\n";
    }
}

// Purpose: Safely get double from standard input | Parameters: prompt (const std::string&), minVal (double), maxVal (double) | Return Value: double | Complexity: O(1)
double Utilities::getDoubleInput(const std::string& prompt, double minVal, double maxVal) {
    double val = 0.0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (val >= minVal && val <= maxVal) {
                return val;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "\033[31m[ERROR] Invalid input! Enter a value between " << minVal << " and " << maxVal << ".\033[0m\n";
    }
}

// Purpose: Safely get string from standard input | Parameters: prompt (const std::string&), allowEmpty (bool) | Return Value: std::string | Complexity: O(1)
std::string Utilities::getStringInput(const std::string& prompt, bool allowEmpty) {
    std::string val;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, val);
        val = trim(val);
        if (allowEmpty || !val.empty()) {
            return val;
        }
        std::cout << "\033[31m[ERROR] Input cannot be empty. Please try again.\033[0m\n";
    }
}
