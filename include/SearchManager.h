#ifndef SEARCH_MANAGER_H
#define SEARCH_MANAGER_H

#include <string>
#include "../datastructures/DynamicArray.h"
#include "Student.h"
#include "Faculty.h"

class StudentManager;
class FacultyManager;

// Purpose: Coordinates global queries and search operations across ERP indexes.
// Responsibilities: Execute exact roll/ID queries, name lookups, and auto-completion search operations.
// Data Structure Used: DynamicArray to return matched records.
// Time Complexity: O(1) roll/ID lookup, O(log N) exact name search, O(L + K) prefix auto-completion.
// Dependencies: "DynamicArray.h", Student.h, Faculty.h
class SearchManager {
public:
    // Purpose: Search student by Roll Number | Parameters: roll (const std::string&), studentMgr (const StudentManager&) | Return Value: Student* | Complexity: O(1) average
    static Student* searchStudentByRoll(const std::string& roll, const StudentManager& studentMgr);

    // Purpose: Search student by exact Name | Parameters: name (const std::string&), studentMgr (StudentManager&) | Return Value: Student* | Complexity: O(log N)
    static Student* searchStudentByNameExact(const std::string& name, StudentManager& studentMgr);

    // Purpose: Search students by Name prefix (Auto-complete) | Parameters: prefix (const std::string&), studentMgr (const StudentManager&), results (DynamicArray<Student*>&) | Return Value: None | Complexity: O(L + K)
    static void autoCompleteStudentName(const std::string& prefix, const StudentManager& studentMgr, DynamicArray<Student*>& results);

    // Purpose: Search faculty by ID | Parameters: id (const std::string&), facultyMgr (const FacultyManager&) | Return Value: Faculty* | Complexity: O(1) average
    static Faculty* searchFacultyById(const std::string& id, const FacultyManager& facultyMgr);
};

#endif // SEARCH_MANAGER_H
