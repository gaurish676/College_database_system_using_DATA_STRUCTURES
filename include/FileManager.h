#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include "../datastructures/DoublyLinkedList.h"
#include "Student.h"
#include "Faculty.h"
#include "Fee.h"
#include "Award.h"
#include "Bill.h"
#include "Course.h"

// Purpose: Manages reading and writing database records to disk files.
// Responsibilities: Save/load lists of students, faculty, courses, fees, awards, and bills to/from binary files.
// Data Structure Used: DoublyLinkedList
// Time Complexity: O(N) for I/O operations | Space Complexity: O(1)
// Dependencies: <string>, "DoublyLinkedList.h", Student.h, Faculty.h, Fee.h, Award.h, Bill.h, Course.h
class FileManager {
public:
    // Purpose: Save Student records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Student>&) | Return Value: bool | Complexity: O(N)
    static bool saveStudents(const std::string& filepath, DoublyLinkedList<Student>& list);

    // Purpose: Load Student records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Student>&) | Return Value: bool | Complexity: O(N)
    static bool loadStudents(const std::string& filepath, DoublyLinkedList<Student>& list);

    // Purpose: Save Faculty records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Faculty>&) | Return Value: bool | Complexity: O(N)
    static bool saveFaculty(const std::string& filepath, DoublyLinkedList<Faculty>& list);

    // Purpose: Load Faculty records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Faculty>&) | Return Value: bool | Complexity: O(N)
    static bool loadFaculty(const std::string& filepath, DoublyLinkedList<Faculty>& list);

    // Purpose: Save Course records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Course>&) | Return Value: bool | Complexity: O(N)
    static bool saveCourses(const std::string& filepath, DoublyLinkedList<Course>& list);

    // Purpose: Load Course records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Course>&) | Return Value: bool | Complexity: O(N)
    static bool loadCourses(const std::string& filepath, DoublyLinkedList<Course>& list);

    // Purpose: Save Fee records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Fee>&) | Return Value: bool | Complexity: O(N)
    static bool saveFees(const std::string& filepath, DoublyLinkedList<Fee>& list);

    // Purpose: Load Fee records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Fee>&) | Return Value: bool | Complexity: O(N)
    static bool loadFees(const std::string& filepath, DoublyLinkedList<Fee>& list);

    // Purpose: Save Award records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Award>&) | Return Value: bool | Complexity: O(N)
    static bool saveAwards(const std::string& filepath, DoublyLinkedList<Award>& list);

    // Purpose: Load Award records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Award>&) | Return Value: bool | Complexity: O(N)
    static bool loadAwards(const std::string& filepath, DoublyLinkedList<Award>& list);

    // Purpose: Save Bill records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Bill>&) | Return Value: bool | Complexity: O(N)
    static bool saveBills(const std::string& filepath, DoublyLinkedList<Bill>& list);

    // Purpose: Load Bill records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Bill>&) | Return Value: bool | Complexity: O(N)
    static bool loadBills(const std::string& filepath, DoublyLinkedList<Bill>& list);
};

#endif // FILE_MANAGER_H
