#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

// Purpose: Business logic input validator.
// Responsibilities: Enforces structure validation for emails, roll numbers, GPAs, and dates.
// Data Structure Used: None
// Time Complexity: O(N) | Space Complexity: O(1)
// Dependencies: <string>
class Validator {
public:
    // Purpose: Check if email structure is valid | Parameters: email (const std::string&) | Return Value: bool | Complexity: O(N)
    static bool isValidEmail(const std::string& email);

    // Purpose: Check if roll number is non-empty | Parameters: roll (const std::string&) | Return Value: bool | Complexity: O(N)
    static bool isValidRollNumber(const std::string& roll);

    // Purpose: Check if CGPA is in [0.0, 10.0] range | Parameters: cgpa (double) | Return Value: bool | Complexity: O(1)
    static bool isValidCgpa(double cgpa);

    // Purpose: Check if date format is non-empty | Parameters: date (const std::string&) | Return Value: bool | Complexity: O(N)
    static bool isValidDate(const std::string& date);
};

#endif // VALIDATOR_H
