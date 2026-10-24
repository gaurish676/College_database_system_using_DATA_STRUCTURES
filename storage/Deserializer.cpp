#include "../include/Deserializer.h"

// Purpose: Deserialize a std::string | Parameters: is (std::istream&) | Return Value: std::string | Complexity: O(S)
std::string Deserializer::readString(std::istream& is) {
    uint32_t len = 0;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!is || len == 0) {
        return "";
    }
    std::string str;
    str.resize(len);
    is.read(&str[0], len);
    return str;
}

// Purpose: Deserialize uint8_t | Parameters: is (std::istream&) | Return Value: uint8_t | Complexity: O(1)
uint8_t Deserializer::readU8(std::istream& is) {
    uint8_t val = 0;
    is.read(reinterpret_cast<char*>(&val), sizeof(val));
    return val;
}

// Purpose: Deserialize uint16_t | Parameters: is (std::istream&) | Return Value: uint16_t | Complexity: O(1)
uint16_t Deserializer::readU16(std::istream& is) {
    uint16_t val = 0;
    is.read(reinterpret_cast<char*>(&val), sizeof(val));
    return val;
}

// Purpose: Deserialize uint32_t | Parameters: is (std::istream&) | Return Value: uint32_t | Complexity: O(1)
uint32_t Deserializer::readU32(std::istream& is) {
    uint32_t val = 0;
    is.read(reinterpret_cast<char*>(&val), sizeof(val));
    return val;
}

// Purpose: Deserialize Student record | Parameters: is (std::istream&) | Return Value: Student | Complexity: O(C + F + A + B)
Student Deserializer::deserializeStudent(std::istream& is) {
    std::string roll = readString(is);
    std::string name = readString(is);
    std::string email = readString(is);
    Department dept = static_cast<Department>(readU8(is));
    Semester sem = static_cast<Semester>(readU8(is));
    uint16_t scaledCgpa = readU16(is);

    Student s(roll, name, email, dept, sem, 0.0);
    s.setScaledCgpa(scaledCgpa);

    // Enrolled Courses
    uint32_t courseCount = readU32(is);
    for (uint32_t i = 0; i < courseCount; ++i) {
        s.enrollCourse(readString(is));
    }

    // Fee records
    uint32_t feeCount = readU32(is);
    for (uint32_t i = 0; i < feeCount; ++i) {
        s.addFeeRecord(readString(is));
    }

    // Award records
    uint32_t awardCount = readU32(is);
    for (uint32_t i = 0; i < awardCount; ++i) {
        s.addAwardRecord(readString(is));
    }

    // Bill records
    uint32_t billCount = readU32(is);
    for (uint32_t i = 0; i < billCount; ++i) {
        s.addBillRecord(readString(is));
    }

    return s;
}

// Purpose: Deserialize Faculty record | Parameters: is (std::istream&) | Return Value: Faculty | Complexity: O(C)
Faculty Deserializer::deserializeFaculty(std::istream& is) {
    std::string id = readString(is);
    std::string name = readString(is);
    std::string email = readString(is);
    Department dept = static_cast<Department>(readU8(is));
    std::string designation = readString(is);
    uint32_t salary = readU32(is);

    Faculty f(id, name, email, dept, designation, salary);

    uint32_t courseCount = readU32(is);
    for (uint32_t i = 0; i < courseCount; ++i) {
        f.assignCourse(readString(is));
    }

    return f;
}

// Purpose: Deserialize Course record | Parameters: is (std::istream&) | Return Value: Course | Complexity: O(1)
Course Deserializer::deserializeCourse(std::istream& is) {
    std::string id = readString(is);
    std::string name = readString(is);
    uint8_t cr = readU8(is);
    Department dept = static_cast<Department>(readU8(is));
    Semester sem = static_cast<Semester>(readU8(is));
    return Course(id, name, cr, dept, sem);
}

// Purpose: Deserialize Fee record | Parameters: is (std::istream&) | Return Value: Fee | Complexity: O(1)
Fee Deserializer::deserializeFee(std::istream& is) {
    std::string id = readString(is);
    std::string roll = readString(is);
    uint32_t total = readU32(is);
    uint32_t paid = readU32(is);
    FeeStatus stat = static_cast<FeeStatus>(readU8(is));
    std::string due = readString(is);
    return Fee(id, roll, total, paid, stat, due);
}

// Purpose: Deserialize Award record | Parameters: is (std::istream&) | Return Value: Award | Complexity: O(1)
Award Deserializer::deserializeAward(std::istream& is) {
    std::string id = readString(is);
    std::string roll = readString(is);
    std::string name = readString(is);
    std::string sponsor = readString(is);
    uint32_t prize = readU32(is);
    std::string date = readString(is);
    return Award(id, roll, name, sponsor, prize, date);
}

// Purpose: Deserialize Bill record | Parameters: is (std::istream&) | Return Value: Bill | Complexity: O(1)
Bill Deserializer::deserializeBill(std::istream& is) {
    std::string id = readString(is);
    std::string roll = readString(is);
    uint32_t amt = readU32(is);
    BillCategory cat = static_cast<BillCategory>(readU8(is));
    BillStatus stat = static_cast<BillStatus>(readU8(is));
    std::string date = readString(is);
    return Bill(id, roll, amt, cat, stat, date);
}
