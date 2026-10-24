#include "../include/BillingManager.h"
#include "../include/StudentManager.h"
#include "../include/FileManager.h"

// Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
BillingManager::BillingManager() : billList(), billIndex(16) {
    loadFromFile();
}

// Purpose: Rebuild index from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
void BillingManager::rebuildIndex() {
    billIndex.clear();
    auto current = billList.getHead();
    while (current != nullptr) {
        billIndex.insert(current->data.getBillId(), &(current->data));
        current = current->next;
    }
}

// Purpose: Add new bill record | Parameters: bill (const Bill&), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
bool BillingManager::addBillRecord(const Bill& bill, StudentManager& studentMgr) {
    Student* s = studentMgr.getStudentByRoll(bill.getStudentRollNumber());
    if (s == nullptr) {
        return false; // Student doesn't exist
    }

    Bill* existing = nullptr;
    if (billIndex.search(bill.getBillId(), existing)) {
        return false; // Bill ID already exists
    }

    billList.push_back(bill);
    Bill* bPtr = &(billList.getTail()->data);
    billIndex.insert(bPtr->getBillId(), bPtr);

    s->addBillRecord(bPtr->getBillId());
    studentMgr.saveToFile();
    saveToFile();
    return true;
}

// Purpose: Update bill payment status | Parameters: billId (const std::string&), status (BillStatus) | Return Value: bool | Complexity: O(1) average
bool BillingManager::updateBillStatus(const std::string& billId, BillStatus status) {
    Bill* b = getBillById(billId);
    if (b == nullptr) {
        return false;
    }
    b->setStatus(status);
    saveToFile();
    return true;
}

// Purpose: Search bill record by ID | Parameters: id (const std::string&) | Return Value: Bill* | Complexity: O(1) average
Bill* BillingManager::getBillById(const std::string& id) const {
    Bill* bPtr = nullptr;
    if (billIndex.search(id, bPtr)) {
        return bPtr;
    }
    return nullptr;
}

// Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Bill>& | Complexity: O(1)
DoublyLinkedList<Bill>& BillingManager::getBills() {
    return billList;
}

// Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Bill>& | Complexity: O(1)
const DoublyLinkedList<Bill>& BillingManager::getBills() const {
    return billList;
}

// Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
bool BillingManager::loadFromFile() {
    bool ok = FileManager::loadBills("data/bills.dat", billList);
    if (ok) {
        rebuildIndex();
    }
    return ok;
}

// Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
bool BillingManager::saveToFile() {
    return FileManager::saveBills("data/bills.dat", billList);
}
