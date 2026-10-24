#include "../include/FeeManager.h"
#include "../include/StudentManager.h"
#include "../include/FileManager.h"

// Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
FeeManager::FeeManager() : feeList(), feeIndex(16) {
    loadFromFile();
}

// Purpose: Rebuild index from master storage | Parameters: None | Return Value: None | Complexity: O(N log N)
void FeeManager::rebuildIndex() {
    feeIndex.clear();
    auto current = feeList.getHead();
    while (current != nullptr) {
        feeIndex.insert(current->data.getFeeId(), &(current->data));
        current = current->next;
    }
}

// Purpose: Add fee record | Parameters: fee (const Fee&), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
bool FeeManager::addFeeRecord(const Fee& fee, StudentManager& studentMgr) {
    Student* s = studentMgr.getStudentByRoll(fee.getStudentRollNumber());
    if (s == nullptr) {
        return false; // Student doesn't exist
    }

    Fee* existing = nullptr;
    if (feeIndex.search(fee.getFeeId(), existing)) {
        return false; // Fee ID already exists
    }

    feeList.push_back(fee);
    Fee* fPtr = &(feeList.getTail()->data);
    feeIndex.insert(fPtr->getFeeId(), fPtr);

    s->addFeeRecord(fPtr->getFeeId());
    studentMgr.saveToFile();
    saveToFile();
    return true;
}

// Purpose: Pay student fee | Parameters: feeId (const std::string&), amount (uint32_t), studentMgr (StudentManager&) | Return Value: bool | Complexity: O(1) average
bool FeeManager::recordPayment(const std::string& feeId, uint32_t amount, StudentManager& studentMgr) {
    static_cast<void>(studentMgr);
    Fee* f = getFeeById(feeId);
    if (f == nullptr) {
        return false;
    }

    uint32_t newPaid = f->getPaidAmount() + amount;
    if (newPaid > f->getTotalAmount()) {
        return false; // Overpayment check
    }

    f->setPaidAmount(newPaid);
    if (newPaid == f->getTotalAmount()) {
        f->setStatus(FeeStatus::FULLY_PAID);
    } else {
        f->setStatus(FeeStatus::PARTIALLY_PAID);
    }

    saveToFile();
    return true;
}

// Purpose: Search fee record by ID | Parameters: id (const std::string&) | Return Value: Fee* | Complexity: O(1) average
Fee* FeeManager::getFeeById(const std::string& id) const {
    Fee* fPtr = nullptr;
    if (feeIndex.search(id, fPtr)) {
        return fPtr;
    }
    return nullptr;
}

// Purpose: Get reference to master storage | Parameters: None | Return Value: DoublyLinkedList<Fee>& | Complexity: O(1)
DoublyLinkedList<Fee>& FeeManager::getFees() {
    return feeList;
}

// Purpose: Get reference to master storage (const) | Parameters: None | Return Value: const DoublyLinkedList<Fee>& | Complexity: O(1)
const DoublyLinkedList<Fee>& FeeManager::getFees() const {
    return feeList;
}

// Purpose: Load records from disk | Parameters: None | Return Value: bool | Complexity: O(N log N)
bool FeeManager::loadFromFile() {
    bool ok = FileManager::loadFees("data/fees.dat", feeList);
    if (ok) {
        rebuildIndex();
    }
    return ok;
}

// Purpose: Save records to disk | Parameters: None | Return Value: bool | Complexity: O(N)
bool FeeManager::saveToFile() {
    return FileManager::saveFees("data/fees.dat", feeList);
}
