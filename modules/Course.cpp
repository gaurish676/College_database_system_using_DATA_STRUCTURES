#include "../include/Course.h"

// Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
Course::Course()
    : courseId(""), courseName(""), credits(0), department(Department::COMPUTER_SCIENCE), semester(Semester::SEMESTER_1) {}

// Purpose: Parameterized Constructor | Parameters: id (std::string), name (std::string), cr (uint8_t), dept (Department), sem (Semester) | Return Value: None | Complexity: O(1)
Course::Course(std::string id, std::string name, uint8_t cr, Department dept, Semester sem)
    : courseId(id), courseName(name), credits(cr), department(dept), semester(sem) {}

// Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
Course::~Course() = default;

// Purpose: Copy Constructor | Parameters: other (const Course&) | Return Value: None | Complexity: O(1)
Course::Course(const Course& other)
    : courseId(other.courseId), courseName(other.courseName), credits(other.credits), department(other.department), semester(other.semester) {}

// Purpose: Copy Assignment Operator | Parameters: other (const Course&) | Return Value: Course& | Complexity: O(1)
Course& Course::operator=(const Course& other) {
    if (this != &other) {
        courseId = other.courseId;
        courseName = other.courseName;
        credits = other.credits;
        department = other.department;
        semester = other.semester;
    }
    return *this;
}

// Purpose: Get Course ID | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Course::getCourseId() const {
    return courseId;
}

// Purpose: Set Course ID | Parameters: id (std::string) | Return Value: None | Complexity: O(1)
void Course::setCourseId(std::string id) {
    courseId = id;
}

// Purpose: Get Course Name | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Course::getCourseName() const {
    return courseName;
}

// Purpose: Set Course Name | Parameters: name (std::string) | Return Value: None | Complexity: O(1)
void Course::setCourseName(std::string name) {
    courseName = name;
}

// Purpose: Get Course Credits | Parameters: None | Return Value: uint8_t | Complexity: O(1)
uint8_t Course::getCredits() const {
    return credits;
}

// Purpose: Set Course Credits | Parameters: cr (uint8_t) | Return Value: None | Complexity: O(1)
void Course::setCredits(uint8_t cr) {
    credits = cr;
}

// Purpose: Get Course Department | Parameters: None | Return Value: Department | Complexity: O(1)
Department Course::getDepartment() const {
    return department;
}

// Purpose: Set Course Department | Parameters: dept (Department) | Return Value: None | Complexity: O(1)
void Course::setDepartment(Department dept) {
    department = dept;
}

// Purpose: Get Course Semester | Parameters: None | Return Value: Semester | Complexity: O(1)
Semester Course::getSemester() const {
    return semester;
}

// Purpose: Set Course Semester | Parameters: sem (Semester) | Return Value: None | Complexity: O(1)
void Course::setSemester(Semester sem) {
    semester = sem;
}
