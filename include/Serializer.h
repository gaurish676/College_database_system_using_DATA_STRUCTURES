#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <ostream>
#include <string>
#include <cstdint>
#include "Student.h"
#include "Faculty.h"
#include "Fee.h"
#include "Award.h"
#include "Bill.h"
#include "Course.h"

// Purpose: Handles binary field-by-field serialization of business models.
// Responsibilities: Standardize string and primitive type output to binary streams.
// Data Structure Used: None
// Time Complexity: O(S) for strings of size S, O(1) for primitives | Space Complexity: O(1)
// Dependencies: <ostream>, <string>, <cstdint>, Student.h, Faculty.h, Fee.h, Award.h, Bill.h, Course.h
class Serializer {
public:
    // Purpose: Serialize a std::string with length prefix | Parameters: os (std::ostream&), str (const std::string&) | Return Value: None | Complexity: O(S)
    static void writeString(std::ostream& os, const std::string& str);

    // Purpose: Serialize uint8_t | Parameters: os (std::ostream&), val (uint8_t) | Return Value: None | Complexity: O(1)
    static void writeU8(std::ostream& os, uint8_t val);

    // Purpose: Serialize uint16_t | Parameters: os (std::ostream&), val (uint16_t) | Return Value: None | Complexity: O(1)
    static void writeU16(std::ostream& os, uint16_t val);

    // Purpose: Serialize uint32_t | Parameters: os (std::ostream&), val (uint32_t) | Return Value: None | Complexity: O(1)
    static void writeU32(std::ostream& os, uint32_t val);

    // Purpose: Serialize Student record | Parameters: os (std::ostream&), student (const Student&) | Return Value: None | Complexity: O(C + F + A + B)
    static void serializeStudent(std::ostream& os, const Student& student);

    // Purpose: Serialize Faculty record | Parameters: os (std::ostream&), faculty (const Faculty&) | Return Value: None | Complexity: O(C)
    static void serializeFaculty(std::ostream& os, const Faculty& faculty);

    // Purpose: Serialize Course record | Parameters: os (std::ostream&), course (const Course&) | Return Value: None | Complexity: O(1)
    static void serializeCourse(std::ostream& os, const Course& course);

    // Purpose: Serialize Fee record | Parameters: os (std::ostream&), fee (const Fee&) | Return Value: None | Complexity: O(1)
    static void serializeFee(std::ostream& os, const Fee& fee);

    // Purpose: Serialize Award record | Parameters: os (std::ostream&), award (const Award&) | Return Value: None | Complexity: O(1)
    static void serializeAward(std::ostream& os, const Award& award);

    // Purpose: Serialize Bill record | Parameters: os (std::ostream&), bill (const Bill&) | Return Value: None | Complexity: O(1)
    static void serializeBill(std::ostream& os, const Bill& bill);
};

#endif // SERIALIZER_H
