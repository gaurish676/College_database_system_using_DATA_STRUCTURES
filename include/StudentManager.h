#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <string>
#include "../datastructures/DoublyLinkedList.h"
#include "../datastructures/HashTable.h"
#include "../datastructures/AVLTree.h"
#include "../datastructures/TernarySearchTree.h"
#include "../datastructures/Heap.h"
#include "Student.h"

struct StudentCgpaCompare {
    // Purpose: Comparator to rank students by CGPA in the heap | Parameters: lhs (const Student*), rhs (const Student*) | Return Value: bool | Complexity: O(1)
    bool operator()(const Student* lhs, const Student* rhs) const {
        return lhs->getScaledCgpa() < rhs->getScaledCgpa(); // Yields Max Heap for CGPA
    }
};

// Purpose: Manages in-memory Student storage, secondary indexing, and persistence.
// Responsibilities: Add, delete, update students, query through multiple indexes, rank by CGPA.
// Data Structure Used: DoublyLinkedList (Master Storage), HashTable (Roll index), AVLTree (Name index), TST (Prefix Search), Heap (CGPA rank).
// Time Complexity: Search Roll: O(1), Search Name: O(log N), Insert: O(log N) | Space Complexity: O(N)
// Dependencies: "DoublyLinkedList.h", "HashTable.h", "AVLTree.h", "TernarySearchTree.h", "Heap.h", Student.h
class StudentManager {
private:
    DoublyLinkedList<Student> students; // Master storage
    HashTable<std::string, Student*> rollIndex;
    AVLTree<std::string, Student*> nameIndex;
    TernarySearchTree<Student*> nameTst;
    Heap<Student*, StudentCgpaCompare> cgpaHeap;

    // Purpose: Rebuild the CGPA Heap index | Parameters: None | Return Value: None | Complexity: O(N log N)
    void rebuildHeap();

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    StudentManager();

    // Purpose: Add new student | Parameters: student (const Student&) | Return Value: bool | Complexity: O(log N)
    bool addStudent(const Student& student);

    // Purpose: Remove student by roll number | Parameters: roll (const std::string&) | Return Value: bool | Complexity: O(N log N)
    bool removeStudent(const std::string& roll);

    // Purpose: Search student by roll number | Parameters: roll (const std::string&) | Return Value: Student* | Complexity: O(1) average
    Student* getStudentByRoll(const std::string& roll) const;

    // Purpose: Search student by exact name | Parameters: name (const std::string&) | Return Value: Student* | Complexity: O(log N)
    Student* getStudentByNameExact(const std::string& name) const;

    // Purpose: Search student by name prefix | Parameters: prefix (const std::string&), results (DynamicArray<Student*>&) | Return Value: None | Complexity: O(L + K) where K matches
    void getStudentsByNamePrefix(const std::string& prefix, DynamicArray<Student*>& results) const;

    // Purpose: Get top K performing students | Parameters: k (size_t), results (DynamicArray<Student*>&) | Return Value: None | Complexity: O(k log N)
    void getTopKStudents(size_t k, DynamicArray<Student*>& results);

    // Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Student>& | Complexity: O(1)
    DoublyLinkedList<Student>& getStudents();

    // Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Student>& | Complexity: O(1)
    const DoublyLinkedList<Student>& getStudents() const;

    // Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
    bool loadFromFile();

    // Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
    bool saveToFile();

    // Purpose: Rebuild all indexing from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
    void rebuildIndexes();
};

#endif // STUDENT_MANAGER_H
