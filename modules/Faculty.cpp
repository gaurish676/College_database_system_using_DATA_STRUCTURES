#include "../include/Faculty.h"

// Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
Faculty::Faculty()
    : facultyId(""), name(""), email(""), department(Department::COMPUTER_SCIENCE), designation(""), salary(0), courseIds() {}

// Purpose: Parameterized Constructor | Parameters: id (std::string), nm (std::string), mail (std::string), dept (Department), des (std::string), sal (uint32_t) | Return Value: None | Complexity: O(1)
Faculty::Faculty(std::string id, std::string nm, std::string mail, Department dept, std::string des, uint32_t sal)
    : facultyId(id), name(nm), email(mail), department(dept), designation(des), salary(sal), courseIds() {}

// Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
Faculty::~Faculty() = default;

// Purpose: Copy Constructor | Parameters: other (const Faculty&) | Return Value: None | Complexity: O(C) where C is course count
Faculty::Faculty(const Faculty& other)
    : facultyId(other.facultyId), name(other.name), email(other.email), department(other.department), designation(other.designation), salary(other.salary), courseIds(other.courseIds) {}

// Purpose: Copy Assignment Operator | Parameters: other (const Faculty&) | Return Value: Faculty& | Complexity: O(C) where C is course count
Faculty& Faculty::operator=(const Faculty& other) {
    if (this != &other) {
        facultyId = other.facultyId;
        name = other.name;
        email = other.email;
        department = other.department;
        designation = other.designation;
        salary = other.salary;
        courseIds = other.courseIds;
    }
    return *this;
}

// Purpose: Get Faculty ID | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Faculty::getFacultyId() const {
    return facultyId;
}

// Purpose: Set Faculty ID | Parameters: id (std::string) | Return Value: None | Complexity: O(1)
void Faculty::setFacultyId(std::string id) {
    facultyId = id;
}

// Purpose: Get Name | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Faculty::getName() const {
    return name;
}

// Purpose: Set Name | Parameters: nm (std::string) | Return Value: None | Complexity: O(1)
void Faculty::setName(std::string nm) {
    name = nm;
}

// Purpose: Get Email | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Faculty::getEmail() const {
    return email;
}

// Purpose: Set Email | Parameters: mail (std::string) | Return Value: None | Complexity: O(1)
void Faculty::setEmail(std::string mail) {
    email = mail;
}

// Purpose: Get Department | Parameters: None | Return Value: Department | Complexity: O(1)
Department Faculty::getDepartment() const {
    return department;
}

// Purpose: Set Department | Parameters: dept (Department) | Return Value: None | Complexity: O(1)
void Faculty::setDepartment(Department dept) {
    department = dept;
}

// Purpose: Get Designation | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Faculty::getDesignation() const {
    return designation;
}

// Purpose: Set Designation | Parameters: des (std::string) | Return Value: None | Complexity: O(1)
void Faculty::setDesignation(std::string des) {
    designation = des;
}

// Purpose: Get Salary | Parameters: None | Return Value: uint32_t | Complexity: O(1)
uint32_t Faculty::getSalary() const {
    return salary;
}

// Purpose: Set Salary | Parameters: sal (uint32_t) | Return Value: None | Complexity: O(1)
void Faculty::setSalary(uint32_t sal) {
    salary = sal;
}

// Purpose: Assign a course to teach | Parameters: courseId (std::string) | Return Value: None | Complexity: O(C)
void Faculty::assignCourse(std::string courseId) {
    // Check for duplicates
    for (size_t i = 0; i < courseIds.getSize(); ++i) {
        if (courseIds[i] == courseId) {
            return;
        }
    }
    courseIds.push_back(courseId);
}

// Purpose: Unassign a course | Parameters: courseId (std::string) | Return Value: bool | Complexity: O(C)
bool Faculty::removeCourse(std::string courseId) {
    for (size_t i = 0; i < courseIds.getSize(); ++i) {
        if (courseIds[i] == courseId) {
            // Shift elements left to remove
            for (size_t j = i; j + 1 < courseIds.getSize(); ++j) {
                courseIds[j] = courseIds[j + 1];
            }
            courseIds.pop_back();
            return true;
        }
    }
    return false;
}

// Purpose: Get list of assigned courses | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
const DynamicArray<std::string>& Faculty::getCourseIds() const {
    return courseIds;
}
