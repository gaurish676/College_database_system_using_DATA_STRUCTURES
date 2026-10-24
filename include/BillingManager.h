#ifndef BILLING_MANAGER_H
#define BILLING_MANAGER_H

#include <string>
#include "../datastructures/DoublyLinkedList.h"
#include "../datastructures/HashTable.h"
#include "Bill.h"

class StudentManager;

// Purpose: Manages Student invoicing, bills, and persistence.
// Responsibilities: Issue new bills, modify bill status, and link to Student profiles.
// Data Structure Used: DoublyLinkedList (Master Storage), HashTable (Bill ID Index).
// Time Complexity: Search Bill: O(1), Insert: O(1) average | Space Complexity: O(N)
// Dependencies: "DoublyLinkedList.h", "HashTable.h", Bill.h
class BillingManager {
private:
    DoublyLinkedList<Bill> billList;
    HashTable<std::string, Bill*> billIndex;

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    BillingManager();

    // Purpose: Add new bill record | Parameters: bill (const Bill&), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
    bool addBillRecord(const Bill& bill, StudentManager& studentMgr);

    // Purpose: Update bill payment status | Parameters: billId (const std::string&), status (BillStatus) | Return Value: bool | Complexity: O(1) average
    bool updateBillStatus(const std::string& billId, BillStatus status);

    // Purpose: Search bill record by ID | Parameters: id (const std::string&) | Return Value: Bill* | Complexity: O(1) average
    Bill* getBillById(const std::string& id) const;

    // Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Bill>& | Complexity: O(1)
    DoublyLinkedList<Bill>& getBills();

    // Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Bill>& | Complexity: O(1)
    const DoublyLinkedList<Bill>& getBills() const;

    // Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
    bool loadFromFile();

    // Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
    bool saveToFile();

    // Purpose: Rebuild index from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
    void rebuildIndex();
};

#endif // BILLING_MANAGER_H
