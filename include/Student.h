#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <cstdint>
#include "Course.h"
#include "../datastructures/DynamicArray.h"

// Purpose: Represents a student record in the College ERP database.
// Responsibilities: Maintain student profile details, scaled CGPA, enrolled courses, and associated financial/academic records.
// Data Structure Used: DynamicArray<std::string> for course IDs, fee IDs, award IDs, and bill IDs.
// Time Complexity: O(1) profile access, O(N) list operations | Space Complexity: O(C + F + A + B)
// Dependencies: <string>, <cstdint>, "Course.h", "../datastructures/DynamicArray.h"
class Student {
private:
    std::string rollNumber;
    std::string name;
    std::string email;
    Department department;
    Semester semester;
    uint16_t scaledCgpa; // CGPA scaled by 100 (e.g., 9.81 stored as 981)

    DynamicArray<std::string> enrolledCourseIds;
    DynamicArray<std::string> feeIds;
    DynamicArray<std::string> awardIds;
    DynamicArray<std::string> billIds;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Student();

    // Purpose: Parameterized Constructor | Parameters: roll (std::string), nm (std::string), mail (std::string), dept (Department), sem (Semester), cgpaVal (double) | Return Value: None | Complexity: O(1)
    Student(std::string roll, std::string nm, std::string mail, Department dept, Semester sem, double cgpaVal);

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
    ~Student();

    // Purpose: Copy Constructor | Parameters: other (const Student&) | Return Value: None | Complexity: O(N)
    Student(const Student& other);

    // Purpose: Copy Assignment Operator | Parameters: other (const Student&) | Return Value: Student& | Complexity: O(N)
    Student& operator=(const Student& other);

    // Purpose: Get Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getRollNumber() const;

    // Purpose: Set Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
    void setRollNumber(std::string roll);

    // Purpose: Get Name | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getName() const;

    // Purpose: Set Name | Parameters: nm (std::string) | Return Value: None | Complexity: O(1)
    void setName(std::string nm);

    // Purpose: Get Email | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getEmail() const;

    // Purpose: Set Email | Parameters: mail (std::string) | Return Value: None | Complexity: O(1)
    void setEmail(std::string mail);

    // Purpose: Get Department | Parameters: None | Return Value: Department | Complexity: O(1)
    Department getDepartment() const;

    // Purpose: Set Department | Parameters: dept (Department) | Return Value: None | Complexity: O(1)
    void setDepartment(Department dept);

    // Purpose: Get Semester | Parameters: None | Return Value: Semester | Complexity: O(1)
    Semester getSemester() const;

    // Purpose: Set Semester | Parameters: sem (Semester) | Return Value: None | Complexity: O(1)
    void setSemester(Semester sem);

    // Purpose: Get CGPA (unscaled) | Parameters: None | Return Value: double | Complexity: O(1)
    double getCgpa() const;

    // Purpose: Set CGPA (unscaled) | Parameters: cgpaVal (double) | Return Value: None | Complexity: O(1)
    void setCgpa(double cgpaVal);

    // Purpose: Get Scaled CGPA (integer representation) | Parameters: None | Return Value: uint16_t | Complexity: O(1)
    uint16_t getScaledCgpa() const;

    // Purpose: Set Scaled CGPA directly | Parameters: scaledVal (uint16_t) | Return Value: None | Complexity: O(1)
    void setScaledCgpa(uint16_t scaledVal);

    // Purpose: Enroll in a course | Parameters: courseId (std::string) | Return Value: None | Complexity: O(N)
    void enrollCourse(std::string courseId);

    // Purpose: Unenroll from a course | Parameters: courseId (std::string) | Return Value: bool | Complexity: O(N)
    bool unenrollCourse(std::string courseId);

    // Purpose: Get enrolled course IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
    const DynamicArray<std::string>& getEnrolledCourseIds() const;

    // Purpose: Associate a fee record | Parameters: feeId (std::string) | Return Value: None | Complexity: O(N)
    void addFeeRecord(std::string feeId);

    // Purpose: Get associated fee record IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
    const DynamicArray<std::string>& getFeeIds() const;

    // Purpose: Associate an award record | Parameters: awardId (std::string) | Return Value: None | Complexity: O(N)
    void addAwardRecord(std::string awardId);

    // Purpose: Get associated award record IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
    const DynamicArray<std::string>& getAwardIds() const;

    // Purpose: Associate a billing record | Parameters: billId (std::string) | Return Value: None | Complexity: O(N)
    void addBillRecord(std::string billId);

    // Purpose: Get associated billing record IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
    const DynamicArray<std::string>& getBillIds() const;
};

#endif // STUDENT_H
