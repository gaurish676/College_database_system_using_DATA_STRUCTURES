#include "../include/StudentManager.h"
#include "../include/FileManager.h"
#include <iostream>

// Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
StudentManager::StudentManager() : students(), rollIndex(16), nameIndex(), nameTst(), cgpaHeap() {
    loadFromFile();
}

// Purpose: Rebuild all indexing from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
void StudentManager::rebuildIndexes() {
    rollIndex.clear();
    nameIndex.clear();
    nameTst.clear();
    cgpaHeap.clear();

    auto current = students.getHead();
    while (current != nullptr) {
        Student* sPtr = &(current->data);
        rollIndex.insert(sPtr->getRollNumber(), sPtr);
        nameIndex.insert(sPtr->getName(), sPtr);
        nameTst.insert(sPtr->getName(), sPtr);
        cgpaHeap.insert(sPtr);
        current = current->next;
    }
}

// Purpose: Rebuild the CGPA Heap index | Parameters: None | Return Value: None | Complexity: O(N log N)
void StudentManager::rebuildHeap() {
    cgpaHeap.clear();
    auto current = students.getHead();
    while (current != nullptr) {
        cgpaHeap.insert(&(current->data));
        current = current->next;
    }
}

// Purpose: Add new student | Parameters: student (const Student&) | Return Value: bool | Complexity: O(log N)
bool StudentManager::addStudent(const Student& student) {
    std::string roll = student.getRollNumber();
    Student* existing = nullptr;
    if (rollIndex.search(roll, existing)) {
        return false; // Roll number already exists
    }

    students.push_back(student);
    Student* sPtr = &(students.getTail()->data);

    rollIndex.insert(sPtr->getRollNumber(), sPtr);
    nameIndex.insert(sPtr->getName(), sPtr);
    nameTst.insert(sPtr->getName(), sPtr);
    cgpaHeap.insert(sPtr);
    
    saveToFile();
    return true;
}

// Purpose: Remove student by roll number | Parameters: roll (const std::string&) | Return Value: bool | Complexity: O(N log N)
bool StudentManager::removeStudent(const std::string& roll) {
    Student* sPtr = nullptr;
    if (!rollIndex.search(roll, sPtr)) {
        return false;
    }

    // Remove from indexes first
    rollIndex.remove(roll);
    nameIndex.remove(sPtr->getName());
    nameTst.remove(sPtr->getName());

    // Remove from master list
    auto current = students.getHead();
    while (current != nullptr) {
        if (&(current->data) == sPtr) {
            students.removeNode(current);
            break;
        }
        current = current->next;
    }

    // Rebuild heap since elements have changed
    rebuildHeap();
    saveToFile();
    return true;
}

// Purpose: Search student by roll number | Parameters: roll (const std::string&) | Return Value: Student* | Complexity: O(1) average
Student* StudentManager::getStudentByRoll(const std::string& roll) const {
    Student* sPtr = nullptr;
    if (rollIndex.search(roll, sPtr)) {
        return sPtr;
    }
    return nullptr;
}

// Purpose: Search student by exact name | Parameters: name (const std::string&) | Return Value: Student* | Complexity: O(log N)
Student* StudentManager::getStudentByNameExact(const std::string& name) const {
    Student* sPtr = nullptr;
    if (nameIndex.search(name, sPtr)) {
        return sPtr;
    }
    return nullptr;
}

// Purpose: Search student by name prefix | Parameters: prefix (const std::string&), results (DynamicArray<Student*>&) | Return Value: None | Complexity: O(L + K)
void StudentManager::getStudentsByNamePrefix(const std::string& prefix, DynamicArray<Student*>& results) const {
    nameTst.searchPrefix(prefix, results);
}

// Purpose: Get top K performing students | Parameters: k (size_t), results (DynamicArray<Student*>&) | Return Value: None | Complexity: O(k log N)
void StudentManager::getTopKStudents(size_t k, DynamicArray<Student*>& results) {
    results.clear();
    // Copy cgpaHeap so we don't destroy the index during extraction
    Heap<Student*, StudentCgpaCompare> tempHeap = cgpaHeap;
    for (size_t i = 0; i < k && !tempHeap.isEmpty(); ++i) {
        Student* topStudent = nullptr;
        if (tempHeap.extractTop(topStudent)) {
            results.push_back(topStudent);
        }
    }
}

// Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Student>& | Complexity: O(1)
DoublyLinkedList<Student>& StudentManager::getStudents() {
    return students;
}

// Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Student>& | Complexity: O(1)
const DoublyLinkedList<Student>& StudentManager::getStudents() const {
    return students;
}

// Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
bool StudentManager::loadFromFile() {
    bool ok = FileManager::loadStudents("data/students.dat", students);
    if (ok) {
        rebuildIndexes();
    }
    return ok;
}

// Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
bool StudentManager::saveToFile() {
    return FileManager::saveStudents("data/students.dat", students);
}
