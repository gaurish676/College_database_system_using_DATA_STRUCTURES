#include "../include/FacultyManager.h"
#include "../include/FileManager.h"

// Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
FacultyManager::FacultyManager() : facultyList(), idIndex(16), nameIndex() {
    loadFromFile();
}

// Purpose: Rebuild indexes from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
void FacultyManager::rebuildIndexes() {
    idIndex.clear();
    nameIndex.clear();

    auto current = facultyList.getHead();
    while (current != nullptr) {
        Faculty* fPtr = &(current->data);
        idIndex.insert(fPtr->getFacultyId(), fPtr);
        nameIndex.insert(fPtr->getName(), fPtr);
        current = current->next;
    }
}

// Purpose: Add new faculty record | Parameters: faculty (const Faculty&) | Return Value: bool | Complexity: O(log N)
bool FacultyManager::addFaculty(const Faculty& faculty) {
    std::string id = faculty.getFacultyId();
    Faculty* existing = nullptr;
    if (idIndex.search(id, existing)) {
        return false; // ID already exists
    }

    facultyList.push_back(faculty);
    Faculty* fPtr = &(facultyList.getTail()->data);

    idIndex.insert(fPtr->getFacultyId(), fPtr);
    nameIndex.insert(fPtr->getName(), fPtr);

    saveToFile();
    return true;
}

// Purpose: Remove faculty record by ID | Parameters: id (const std::string&) | Return Value: bool | Complexity: O(N)
bool FacultyManager::removeFaculty(const std::string& id) {
    Faculty* fPtr = nullptr;
    if (!idIndex.search(id, fPtr)) {
        return false;
    }

    // Remove from indexes
    idIndex.remove(id);
    nameIndex.remove(fPtr->getName());

    // Remove from master list
    auto current = facultyList.getHead();
    while (current != nullptr) {
        if (&(current->data) == fPtr) {
            facultyList.removeNode(current);
            break;
        }
        current = current->next;
    }

    saveToFile();
    return true;
}

// Purpose: Search faculty by ID | Parameters: id (const std::string&) | Return Value: Faculty* | Complexity: O(1) average
Faculty* FacultyManager::getFacultyById(const std::string& id) const {
    Faculty* fPtr = nullptr;
    if (idIndex.search(id, fPtr)) {
        return fPtr;
    }
    return nullptr;
}

// Purpose: Search faculty by exact name | Parameters: name (const std::string&) | Return Value: Faculty* | Complexity: O(log N)
Faculty* FacultyManager::getFacultyByNameExact(const std::string& name) const {
    Faculty* fPtr = nullptr;
    if (nameIndex.search(name, fPtr)) {
        return fPtr;
    }
    return nullptr;
}

// Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Faculty>& | Complexity: O(1)
DoublyLinkedList<Faculty>& FacultyManager::getFaculty() {
    return facultyList;
}

// Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Faculty>& | Complexity: O(1)
const DoublyLinkedList<Faculty>& FacultyManager::getFaculty() const {
    return facultyList;
}

// Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
bool FacultyManager::loadFromFile() {
    bool ok = FileManager::loadFaculty("data/faculty.dat", facultyList);
    if (ok) {
        rebuildIndexes();
    }
    return ok;
}

// Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
bool FacultyManager::saveToFile() {
    return FileManager::saveFaculty("data/faculty.dat", facultyList);
}
