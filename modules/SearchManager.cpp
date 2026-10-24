#include "../include/SearchManager.h"
#include "../include/StudentManager.h"
#include "../include/FacultyManager.h"

// Purpose: Search student by Roll Number | Parameters: roll (const std::string&), studentMgr (const StudentManager&) | Return Value: Student* | Complexity: O(1) average
Student* SearchManager::searchStudentByRoll(const std::string& roll, const StudentManager& studentMgr) {
    return studentMgr.getStudentByRoll(roll);
}

// Purpose: Search student by exact Name | Parameters: name (const std::string&), studentMgr (StudentManager&) | Return Value: Student* | Complexity: O(log N)
Student* SearchManager::searchStudentByNameExact(const std::string& name, StudentManager& studentMgr) {
    return studentMgr.getStudentByNameExact(name);
}

// Purpose: Search students by Name prefix (Auto-complete) | Parameters: prefix (const std::string&), studentMgr (const StudentManager&), results (DynamicArray<Student*>&) | Return Value: None | Complexity: O(L + K)
void SearchManager::autoCompleteStudentName(const std::string& prefix, const StudentManager& studentMgr, DynamicArray<Student*>& results) {
    studentMgr.getStudentsByNamePrefix(prefix, results);
}

// Purpose: Search faculty by ID | Parameters: id (const std::string&), facultyMgr (const FacultyManager&) | Return Value: Faculty* | Complexity: O(1) average
Faculty* SearchManager::searchFacultyById(const std::string& id, const FacultyManager& facultyMgr) {
    return facultyMgr.getFacultyById(id);
}
