#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <cstdint>
#include "Course.h"
#include "../datastructures/DynamicArray.h"

// Purpose: Represents a faculty member in the ERP system.
// Responsibilities: Maintain faculty profile (ID, name, email, department, designation, salary) and track taught courses.
// Data Structure Used: DynamicArray<std::string> for taught course IDs.
// Time Complexity: O(1) for profile operations, O(C) for courses | Space Complexity: O(C) where C is course count
// Dependencies: <string>, <cstdint>, "Course.h", "../datastructures/DynamicArray.h"
class Faculty {
private:
    std::string facultyId;
    std::string name;
    std::string email;
    Department department;
    std::string designation;
    uint32_t salary;
    DynamicArray<std::string> courseIds;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Faculty();

    // Purpose: Parameterized Constructor | Parameters: id (std::string), nm (std::string), mail (std::string), dept (Department), des (std::string), sal (uint32_t) | Return Value: None | Complexity: O(1)
    Faculty(std::string id, std::string nm, std::string mail, Department dept, std::string des, uint32_t sal);

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
    ~Faculty();

    // Purpose: Copy Constructor | Parameters: other (const Faculty&) | Return Value: None | Complexity: O(C)
    Faculty(const Faculty& other);

    // Purpose: Copy Assignment Operator | Parameters: other (const Faculty&) | Return Value: Faculty& | Complexity: O(C)
    Faculty& operator=(const Faculty& other);

    // Purpose: Get Faculty ID | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getFacultyId() const;

    // Purpose: Set Faculty ID | Parameters: id (std::string) | Return Value: None | Complexity: O(1)
    void setFacultyId(std::string id);

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

    // Purpose: Get Designation | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getDesignation() const;

    // Purpose: Set Designation | Parameters: des (std::string) | Return Value: None | Complexity: O(1)
    void setDesignation(std::string des);

    // Purpose: Get Salary | Parameters: None | Return Value: uint32_t | Complexity: O(1)
    uint32_t getSalary() const;

    // Purpose: Set Salary | Parameters: sal (uint32_t) | Return Value: None | Complexity: O(1)
    void setSalary(uint32_t sal);

    // Purpose: Assign a course to teach | Parameters: courseId (std::string) | Return Value: None | Complexity: O(C)
    void assignCourse(std::string courseId);

    // Purpose: Unassign a course | Parameters: courseId (std::string) | Return Value: bool | Complexity: O(C)
    bool removeCourse(std::string courseId);

    // Purpose: Get list of assigned courses | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
    const DynamicArray<std::string>& getCourseIds() const;
};

#endif // FACULTY_H
