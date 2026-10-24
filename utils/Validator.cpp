#include "../include/Validator.h"

// Purpose: Check if email structure is valid | Parameters: email (const std::string&) | Return Value: bool | Complexity: O(N)
bool Validator::isValidEmail(const std::string& email) {
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0 || atPos == email.length() - 1) {
        return false;
    }
    size_t dotPos = email.find('.', atPos);
    if (dotPos == std::string::npos || dotPos == atPos + 1 || dotPos == email.length() - 1) {
        return false;
    }
    return true;
}

// Purpose: Check if roll number is non-empty | Parameters: roll (const std::string&) | Return Value: bool | Complexity: O(N)
bool Validator::isValidRollNumber(const std::string& roll) {
    return !roll.empty();
}

// Purpose: Check if CGPA is in [0.0, 10.0] range | Parameters: cgpa (double) | Return Value: bool | Complexity: O(1)
bool Validator::isValidCgpa(double cgpa) {
    return cgpa >= 0.0 && cgpa <= 10.0;
}

// Purpose: Check if date format is non-empty | Parameters: date (const std::string&) | Return Value: bool | Complexity: O(N)
bool Validator::isValidDate(const std::string& date) {
    // Simple non-empty and minimum length check for DD/MM/YYYY or YYYY-MM-DD
    return date.length() >= 8;
}
