#ifndef AWARD_MANAGER_H
#define AWARD_MANAGER_H

#include <string>
#include "../datastructures/DoublyLinkedList.h"
#include "../datastructures/HashTable.h"
#include "Award.h"

class StudentManager;

// Purpose: Manages student academic honors, awards, and scholarships.
// Responsibilities: Add award records and associate them with Student profiles.
// Data Structure Used: DoublyLinkedList (Master Storage), HashTable (Award ID Index).
// Time Complexity: Search Award: O(1), Insert: O(1) average | Space Complexity: O(N)
// Dependencies: "DoublyLinkedList.h", "HashTable.h", Award.h
class AwardManager {
private:
    DoublyLinkedList<Award> awardList;
    HashTable<std::string, Award*> awardIndex;

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    AwardManager();

    // Purpose: Add award record | Parameters: award (const Award&), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
    bool addAwardRecord(const Award& award, StudentManager& studentMgr);

    // Purpose: Search award by ID | Parameters: id (const std::string&) | Return Value: Award* | Complexity: O(1) average
    Award* getAwardById(const std::string& id) const;

    // Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Award>& | Complexity: O(1)
    DoublyLinkedList<Award>& getAwards();

    // Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Award>& | Complexity: O(1)
    const DoublyLinkedList<Award>& getAwards() const;

    // Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
    bool loadFromFile();

    // Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
    bool saveToFile();

    // Purpose: Rebuild index from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
    void rebuildIndex();
};

#endif // AWARD_MANAGER_H
