#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <cstdint>

enum class Department : uint8_t {
    COMPUTER_SCIENCE = 1,
    ELECTRICAL_ENG = 2,
    MECHANICAL_ENG = 3,
    CIVIL_ENG = 4,
    PHYSICS = 5,
    CHEMISTRY = 6,
    MATHEMATICS = 7
};

enum class Semester : uint8_t {
    SEMESTER_1 = 1,
    SEMESTER_2 = 2,
    SEMESTER_3 = 3,
    SEMESTER_4 = 4,
    SEMESTER_5 = 5,
    SEMESTER_6 = 6,
    SEMESTER_7 = 7,
    SEMESTER_8 = 8
};

// Purpose: Represents an academic course model.
// Responsibilities: Maintain course details including ID, name, credits, department, and semester.
// Data Structure Used: None
// Time Complexity: O(1) for all operations | Space Complexity: O(1)
// Dependencies: <string>, <cstdint>
class Course {
private:
    std::string courseId;
    std::string courseName;
    uint8_t credits;
    Department department;
    Semester semester;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Course();

    // Purpose: Parameterized Constructor | Parameters: id (std::string), name (std::string), cr (uint8_t), dept (Department), sem (Semester) | Return Value: None | Complexity: O(1)
    Course(std::string id, std::string name, uint8_t cr, Department dept, Semester sem);

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
    ~Course();

    // Purpose: Copy Constructor | Parameters: other (const Course&) | Return Value: None | Complexity: O(1)
    Course(const Course& other);

    // Purpose: Copy Assignment Operator | Parameters: other (const Course&) | Return Value: Course& | Complexity: O(1)
    Course& operator=(const Course& other);

    // Purpose: Get Course ID | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getCourseId() const;

    // Purpose: Set Course ID | Parameters: id (std::string) | Return Value: None | Complexity: O(1)
    void setCourseId(std::string id);

    // Purpose: Get Course Name | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getCourseName() const;

    // Purpose: Set Course Name | Parameters: name (std::string) | Return Value: None | Complexity: O(1)
    void setCourseName(std::string name);

    // Purpose: Get Course Credits | Parameters: None | Return Value: uint8_t | Complexity: O(1)
    uint8_t getCredits() const;

    // Purpose: Set Course Credits | Parameters: cr (uint8_t) | Return Value: None | Complexity: O(1)
    void setCredits(uint8_t cr);

    // Purpose: Get Course Department | Parameters: None | Return Value: Department | Complexity: O(1)
    Department getDepartment() const;

    // Purpose: Set Course Department | Parameters: dept (Department) | Return Value: None | Complexity: O(1)
    void setDepartment(Department dept);

    // Purpose: Get Course Semester | Parameters: None | Return Value: Semester | Complexity: O(1)
    Semester getSemester() const;

    // Purpose: Set Course Semester | Parameters: sem (Semester) | Return Value: None | Complexity: O(1)
    void setSemester(Semester sem);
};

#endif // COURSE_H
