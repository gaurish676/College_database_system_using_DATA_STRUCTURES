#ifndef FACULTY_MANAGER_H
#define FACULTY_MANAGER_H

#include <string>
#include "../datastructures/DoublyLinkedList.h"
#include "../datastructures/HashTable.h"
#include "../datastructures/AVLTree.h"
#include "Faculty.h"

// Purpose: Manages in-memory Faculty storage, secondary indexing, and persistence.
// Responsibilities: Add, delete, update faculty records, query through indexes.
// Data Structure Used: DoublyLinkedList (Master Storage), HashTable (ID index), AVLTree (Name index).
// Time Complexity: Search ID: O(1), Search Name: O(log N), Insert: O(log N) | Space Complexity: O(N)
// Dependencies: "DoublyLinkedList.h", "HashTable.h", "AVLTree.h", Faculty.h
class FacultyManager {
private:
    DoublyLinkedList<Faculty> facultyList; // Master storage
    HashTable<std::string, Faculty*> idIndex;
    AVLTree<std::string, Faculty*> nameIndex;

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    FacultyManager();

    // Purpose: Add new faculty record | Parameters: faculty (const Faculty&) | Return Value: bool | Complexity: O(log N)
    bool addFaculty(const Faculty& faculty);

    // Purpose: Remove faculty record by ID | Parameters: id (const std::string&) | Return Value: bool | Complexity: O(N)
    bool removeFaculty(const std::string& id);

    // Purpose: Search faculty by ID | Parameters: id (const std::string&) | Return Value: Faculty* | Complexity: O(1) average
    Faculty* getFacultyById(const std::string& id) const;

    // Purpose: Search faculty by exact name | Parameters: name (const std::string&) | Return Value: Faculty* | Complexity: O(log N)
    Faculty* getFacultyByNameExact(const std::string& name) const;

    // Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Faculty>& | Complexity: O(1)
    DoublyLinkedList<Faculty>& getFaculty();

    // Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Faculty>& | Complexity: O(1)
    const DoublyLinkedList<Faculty>& getFaculty() const;

    // Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
    bool loadFromFile();

    // Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
    bool saveToFile();

    // Purpose: Rebuild indexes from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
    void rebuildIndexes();
};

#endif // FACULTY_MANAGER_H
