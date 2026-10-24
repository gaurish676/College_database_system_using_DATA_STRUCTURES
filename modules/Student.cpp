#include "../include/Student.h"

// Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
Student::Student()
    : rollNumber(""), name(""), email(""), department(Department::COMPUTER_SCIENCE), semester(Semester::SEMESTER_1), scaledCgpa(0), enrolledCourseIds(), feeIds(), awardIds(), billIds() {}

// Purpose: Parameterized Constructor | Parameters: roll (std::string), nm (std::string), mail (std::string), dept (Department), sem (Semester), cgpaVal (double) | Return Value: None | Complexity: O(1)
Student::Student(std::string roll, std::string nm, std::string mail, Department dept, Semester sem, double cgpaVal)
    : rollNumber(roll), name(nm), email(mail), department(dept), semester(sem), scaledCgpa(static_cast<uint16_t>(cgpaVal * 100.0 + 0.5)), enrolledCourseIds(), feeIds(), awardIds(), billIds() {}

// Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
Student::~Student() = default;

// Purpose: Copy Constructor | Parameters: other (const Student&) | Return Value: None | Complexity: O(N) where N is items count
Student::Student(const Student& other)
    : rollNumber(other.rollNumber), name(other.name), email(other.email), department(other.department), semester(other.semester), scaledCgpa(other.scaledCgpa), enrolledCourseIds(other.enrolledCourseIds), feeIds(other.feeIds), awardIds(other.awardIds), billIds(other.billIds) {}

// Purpose: Copy Assignment Operator | Parameters: other (const Student&) | Return Value: Student& | Complexity: O(N) where N is items count
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        rollNumber = other.rollNumber;
        name = other.name;
        email = other.email;
        department = other.department;
        semester = other.semester;
        scaledCgpa = other.scaledCgpa;
        enrolledCourseIds = other.enrolledCourseIds;
        feeIds = other.feeIds;
        awardIds = other.awardIds;
        billIds = other.billIds;
    }
    return *this;
}

// Purpose: Get Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Student::getRollNumber() const {
    return rollNumber;
}

// Purpose: Set Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
void Student::setRollNumber(std::string roll) {
    rollNumber = roll;
}

// Purpose: Get Name | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Student::getName() const {
    return name;
}

// Purpose: Set Name | Parameters: nm (std::string) | Return Value: None | Complexity: O(1)
void Student::setName(std::string nm) {
    name = nm;
}

// Purpose: Get Email | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Student::getEmail() const {
    return email;
}

// Purpose: Set Email | Parameters: mail (std::string) | Return Value: None | Complexity: O(1)
void Student::setEmail(std::string mail) {
    email = mail;
}

// Purpose: Get Department | Parameters: None | Return Value: Department | Complexity: O(1)
Department Student::getDepartment() const {
    return department;
}

// Purpose: Set Department | Parameters: dept (Department) | Return Value: None | Complexity: O(1)
void Student::setDepartment(Department dept) {
    department = dept;
}

// Purpose: Get Semester | Parameters: None | Return Value: Semester | Complexity: O(1)
Semester Student::getSemester() const {
    return semester;
}

// Purpose: Set Semester | Parameters: sem (Semester) | Return Value: None | Complexity: O(1)
void Student::setSemester(Semester sem) {
    semester = sem;
}

// Purpose: Get CGPA (unscaled) | Parameters: None | Return Value: double | Complexity: O(1)
double Student::getCgpa() const {
    return scaledCgpa / 100.0;
}

// Purpose: Set CGPA (unscaled) | Parameters: cgpaVal (double) | Return Value: None | Complexity: O(1)
void Student::setCgpa(double cgpaVal) {
    scaledCgpa = static_cast<uint16_t>(cgpaVal * 100.0 + 0.5);
}

// Purpose: Get Scaled CGPA (integer representation) | Parameters: None | Return Value: uint16_t | Complexity: O(1)
uint16_t Student::getScaledCgpa() const {
    return scaledCgpa;
}

// Purpose: Set Scaled CGPA directly | Parameters: scaledVal (uint16_t) | Return Value: None | Complexity: O(1)
void Student::setScaledCgpa(uint16_t scaledVal) {
    scaledCgpa = scaledVal;
}

// Purpose: Enroll in a course | Parameters: courseId (std::string) | Return Value: None | Complexity: O(N)
void Student::enrollCourse(std::string courseId) {
    for (size_t i = 0; i < enrolledCourseIds.getSize(); ++i) {
        if (enrolledCourseIds[i] == courseId) {
            return;
        }
    }
    enrolledCourseIds.push_back(courseId);
}

// Purpose: Unenroll from a course | Parameters: courseId (std::string) | Return Value: bool | Complexity: O(N)
bool Student::unenrollCourse(std::string courseId) {
    for (size_t i = 0; i < enrolledCourseIds.getSize(); ++i) {
        if (enrolledCourseIds[i] == courseId) {
            for (size_t j = i; j + 1 < enrolledCourseIds.getSize(); ++j) {
                enrolledCourseIds[j] = enrolledCourseIds[j + 1];
            }
            enrolledCourseIds.pop_back();
            return true;
        }
    }
    return false;
}

// Purpose: Get enrolled course IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
const DynamicArray<std::string>& Student::getEnrolledCourseIds() const {
    return enrolledCourseIds;
}

// Purpose: Associate a fee record | Parameters: feeId (std::string) | Return Value: None | Complexity: O(N)
void Student::addFeeRecord(std::string feeId) {
    for (size_t i = 0; i < feeIds.getSize(); ++i) {
        if (feeIds[i] == feeId) {
            return;
        }
    }
    feeIds.push_back(feeId);
}

// Purpose: Get associated fee record IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
const DynamicArray<std::string>& Student::getFeeIds() const {
    return feeIds;
}

// Purpose: Associate an award record | Parameters: awardId (std::string) | Return Value: None | Complexity: O(N)
void Student::addAwardRecord(std::string awardId) {
    for (size_t i = 0; i < awardIds.getSize(); ++i) {
        if (awardIds[i] == awardId) {
            return;
        }
    }
    awardIds.push_back(awardId);
}

// Purpose: Get associated award record IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
const DynamicArray<std::string>& Student::getAwardIds() const {
    return awardIds;
}

// Purpose: Associate a billing record | Parameters: billId (std::string) | Return Value: None | Complexity: O(N)
void Student::addBillRecord(std::string billId) {
    for (size_t i = 0; i < billIds.getSize(); ++i) {
        if (billIds[i] == billId) {
            return;
        }
    }
    billIds.push_back(billId);
}

// Purpose: Get associated billing record IDs | Parameters: None | Return Value: const DynamicArray<std::string>& | Complexity: O(1)
const DynamicArray<std::string>& Student::getBillIds() const {
    return billIds;
}
