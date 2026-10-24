#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <istream>
#include <string>
#include <cstdint>
#include "Student.h"
#include "Faculty.h"
#include "Fee.h"
#include "Award.h"
#include "Bill.h"
#include "Course.h"

// Purpose: Handles binary field-by-field deserialization of business models.
// Responsibilities: Standardize string and primitive type input parsing from binary streams.
// Data Structure Used: None
// Time Complexity: O(S) for strings of size S, O(1) for primitives | Space Complexity: O(1)
// Dependencies: <istream>, <string>, <cstdint>, Student.h, Faculty.h, Fee.h, Award.h, Bill.h, Course.h
class Deserializer {
public:
    // Purpose: Deserialize a std::string | Parameters: is (std::istream&) | Return Value: std::string | Complexity: O(S)
    static std::string readString(std::istream& is);

    // Purpose: Deserialize uint8_t | Parameters: is (std::istream&) | Return Value: uint8_t | Complexity: O(1)
    static uint8_t readU8(std::istream& is);

    // Purpose: Deserialize uint16_t | Parameters: is (std::istream&) | Return Value: uint16_t | Complexity: O(1)
    static uint16_t readU16(std::istream& is);

    // Purpose: Deserialize uint32_t | Parameters: is (std::istream&) | Return Value: uint32_t | Complexity: O(1)
    static uint32_t readU32(std::istream& is);

    // Purpose: Deserialize Student record | Parameters: is (std::istream&) | Return Value: Student | Complexity: O(C + F + A + B)
    static Student deserializeStudent(std::istream& is);

    // Purpose: Deserialize Faculty record | Parameters: is (std::istream&) | Return Value: Faculty | Complexity: O(C)
    static Faculty deserializeFaculty(std::istream& is);

    // Purpose: Deserialize Course record | Parameters: is (std::istream&) | Return Value: Course | Complexity: O(1)
    static Course deserializeCourse(std::istream& is);

    // Purpose: Deserialize Fee record | Parameters: is (std::istream&) | Return Value: Fee | Complexity: O(1)
    static Fee deserializeFee(std::istream& is);

    // Purpose: Deserialize Award record | Parameters: is (std::istream&) | Return Value: Award | Complexity: O(1)
    static Award deserializeAward(std::istream& is);

    // Purpose: Deserialize Bill record | Parameters: is (std::istream&) | Return Value: Bill | Complexity: O(1)
    static Bill deserializeBill(std::istream& is);
};

#endif // DESERIALIZER_H
