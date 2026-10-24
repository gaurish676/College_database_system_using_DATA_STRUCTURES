#include "../include/AwardManager.h"
#include "../include/StudentManager.h"
#include "../include/FileManager.h"

// Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
AwardManager::AwardManager() : awardList(), awardIndex(16) {
    loadFromFile();
}

// Purpose: Rebuild index from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
void AwardManager::rebuildIndex() {
    awardIndex.clear();
    auto current = awardList.getHead();
    while (current != nullptr) {
        awardIndex.insert(current->data.getAwardId(), &(current->data));
        current = current->next;
    }
}

// Purpose: Add award record | Parameters: award (const Award&), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
bool AwardManager::addAwardRecord(const Award& award, StudentManager& studentMgr) {
    Student* s = studentMgr.getStudentByRoll(award.getStudentRollNumber());
    if (s == nullptr) {
        return false; // Student doesn't exist
    }

    Award* existing = nullptr;
    if (awardIndex.search(award.getAwardId(), existing)) {
        return false; // Award ID already exists
    }

    awardList.push_back(award);
    Award* aPtr = &(awardList.getTail()->data);
    awardIndex.insert(aPtr->getAwardId(), aPtr);

    s->addAwardRecord(aPtr->getAwardId());
    studentMgr.saveToFile();
    saveToFile();
    return true;
}

// Purpose: Search award by ID | Parameters: id (const std::string&) | Return Value: Award* | Complexity: O(1) average
Award* AwardManager::getAwardById(const std::string& id) const {
    Award* aPtr = nullptr;
    if (awardIndex.search(id, aPtr)) {
        return aPtr;
    }
    return nullptr;
}

// Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Award>& | Complexity: O(1)
DoublyLinkedList<Award>& AwardManager::getAwards() {
    return awardList;
}

// Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Award>& | Complexity: O(1)
const DoublyLinkedList<Award>& AwardManager::getAwards() const {
    return awardList;
}

// Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
bool AwardManager::loadFromFile() {
    bool ok = FileManager::loadAwards("data/awards.dat", awardList);
    if (ok) {
        rebuildIndex();
    }
    return ok;
}

// Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
bool AwardManager::saveToFile() {
    return FileManager::saveAwards("data/awards.dat", awardList);
}
