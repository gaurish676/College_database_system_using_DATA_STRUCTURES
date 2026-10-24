#include "../include/Serializer.h"

// Purpose: Serialize a std::string with length prefix | Parameters: os (std::ostream&), str (const std::string&) | Return Value: None | Complexity: O(S)
void Serializer::writeString(std::ostream& os, const std::string& str) {
    uint32_t len = static_cast<uint32_t>(str.length());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        os.write(str.data(), len);
    }
}

// Purpose: Serialize uint8_t | Parameters: os (std::ostream&), val (uint8_t) | Return Value: None | Complexity: O(1)
void Serializer::writeU8(std::ostream& os, uint8_t val) {
    os.write(reinterpret_cast<const char*>(&val), sizeof(val));
}

// Purpose: Serialize uint16_t | Parameters: os (std::ostream&), val (uint16_t) | Return Value: None | Complexity: O(1)
void Serializer::writeU16(std::ostream& os, uint16_t val) {
    os.write(reinterpret_cast<const char*>(&val), sizeof(val));
}

// Purpose: Serialize uint32_t | Parameters: os (std::ostream&), val (uint32_t) | Return Value: None | Complexity: O(1)
void Serializer::writeU32(std::ostream& os, uint32_t val) {
    os.write(reinterpret_cast<const char*>(&val), sizeof(val));
}

// Purpose: Serialize Student record | Parameters: os (std::ostream&), student (const Student&) | Return Value: None | Complexity: O(C + F + A + B)
void Serializer::serializeStudent(std::ostream& os, const Student& student) {
    writeString(os, student.getRollNumber());
    writeString(os, student.getName());
    writeString(os, student.getEmail());
    writeU8(os, static_cast<uint8_t>(student.getDepartment()));
    writeU8(os, static_cast<uint8_t>(student.getSemester()));
    writeU16(os, student.getScaledCgpa());

    // Enrolled Courses
    const DynamicArray<std::string>& courses = student.getEnrolledCourseIds();
    uint32_t courseCount = static_cast<uint32_t>(courses.getSize());
    writeU32(os, courseCount);
    for (size_t i = 0; i < courseCount; ++i) {
        writeString(os, courses[i]);
    }

    // Fee records
    const DynamicArray<std::string>& fees = student.getFeeIds();
    uint32_t feeCount = static_cast<uint32_t>(fees.getSize());
    writeU32(os, feeCount);
    for (size_t i = 0; i < feeCount; ++i) {
        writeString(os, fees[i]);
    }

    // Award records
    const DynamicArray<std::string>& awards = student.getAwardIds();
    uint32_t awardCount = static_cast<uint32_t>(awards.getSize());
    writeU32(os, awardCount);
    for (size_t i = 0; i < awardCount; ++i) {
        writeString(os, awards[i]);
    }

    // Bill records
    const DynamicArray<std::string>& bills = student.getBillIds();
    uint32_t billCount = static_cast<uint32_t>(bills.getSize());
    writeU32(os, billCount);
    for (size_t i = 0; i < billCount; ++i) {
        writeString(os, bills[i]);
    }
}

// Purpose: Serialize Faculty record | Parameters: os (std::ostream&), faculty (const Faculty&) | Return Value: None | Complexity: O(C)
void Serializer::serializeFaculty(std::ostream& os, const Faculty& faculty) {
    writeString(os, faculty.getFacultyId());
    writeString(os, faculty.getName());
    writeString(os, faculty.getEmail());
    writeU8(os, static_cast<uint8_t>(faculty.getDepartment()));
    writeString(os, faculty.getDesignation());
    writeU32(os, faculty.getSalary());

    const DynamicArray<std::string>& courses = faculty.getCourseIds();
    uint32_t courseCount = static_cast<uint32_t>(courses.getSize());
    writeU32(os, courseCount);
    for (size_t i = 0; i < courseCount; ++i) {
        writeString(os, courses[i]);
    }
}

// Purpose: Serialize Course record | Parameters: os (std::ostream&), course (const Course&) | Return Value: None | Complexity: O(1)
void Serializer::serializeCourse(std::ostream& os, const Course& course) {
    writeString(os, course.getCourseId());
    writeString(os, course.getCourseName());
    writeU8(os, course.getCredits());
    writeU8(os, static_cast<uint8_t>(course.getDepartment()));
    writeU8(os, static_cast<uint8_t>(course.getSemester()));
}

// Purpose: Serialize Fee record | Parameters: os (std::ostream&), fee (const Fee&) | Return Value: None | Complexity: O(1)
void Serializer::serializeFee(std::ostream& os, const Fee& fee) {
    writeString(os, fee.getFeeId());
    writeString(os, fee.getStudentRollNumber());
    writeU32(os, fee.getTotalAmount());
    writeU32(os, fee.getPaidAmount());
    writeU8(os, static_cast<uint8_t>(fee.getStatus()));
    writeString(os, fee.getDueDate());
}

// Purpose: Serialize Award record | Parameters: os (std::ostream&), award (const Award&) | Return Value: None | Complexity: O(1)
void Serializer::serializeAward(std::ostream& os, const Award& award) {
    writeString(os, award.getAwardId());
    writeString(os, award.getStudentRollNumber());
    writeString(os, award.getAwardName());
    writeString(os, award.getSponsoringBody());
    writeU32(os, award.getCashPrize());
    writeString(os, award.getDateAwarded());
}

// Purpose: Serialize Bill record | Parameters: os (std::ostream&), bill (const Bill&) | Return Value: None | Complexity: O(1)
void Serializer::serializeBill(std::ostream& os, const Bill& bill) {
    writeString(os, bill.getBillId());
    writeString(os, bill.getStudentRollNumber());
    writeU32(os, bill.getAmount());
    writeU8(os, static_cast<uint8_t>(bill.getCategory()));
    writeU8(os, static_cast<uint8_t>(bill.getStatus()));
    writeString(os, bill.getBillingDate());
}
