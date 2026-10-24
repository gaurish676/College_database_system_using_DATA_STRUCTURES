#ifndef FEE_MANAGER_H
#define FEE_MANAGER_H

#include <string>
#include "../datastructures/DoublyLinkedList.h"
#include "../datastructures/HashTable.h"
#include "Fee.h"

// Forward declaration
class StudentManager;

// Purpose: Manages Student Fee records, payments, and persistence.
// Responsibilities: Create, update fee payments, and link them to Student profiles.
// Data Structure Used: DoublyLinkedList (Master Storage), HashTable (Fee ID Index).
// Time Complexity: Search Fee: O(1), Insert: O(1) average | Space Complexity: O(N)
// Dependencies: "DoublyLinkedList.h", "HashTable.h", Fee.h
class FeeManager {
private:
    DoublyLinkedList<Fee> feeList;
    HashTable<std::string, Fee*> feeIndex;

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    FeeManager();

    // Purpose: Add fee record | Parameters: fee (const Fee&), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
    bool addFeeRecord(const Fee& fee, StudentManager& studentMgr);

    // Purpose: Pay student fee | Parameters: feeId (const std::string&), amount (uint32_t), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
    bool recordPayment(const std::string& feeId, uint32_t amount, StudentManager& studentMgr);

    // Purpose: Search fee record by ID | Parameters: id (const std::string&) | Return Value: Fee* | Complexity: O(1) average
    Fee* getFeeById(const std::string& id) const;

    // Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Fee>& | Complexity: O(1)
    DoublyLinkedList<Fee>& getFees();

    // Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Fee>& | Complexity: O(1)
    const DoublyLinkedList<Fee>& getFees() const;

    // Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
    bool loadFromFile();

    // Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
    bool saveToFile();

    // Purpose: Rebuild index from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
    void rebuildIndex();
};

#endif // FEE_MANAGER_H
