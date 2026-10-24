#include "../include/Bill.h"

// Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
Bill::Bill()
    : billId(""), studentRollNumber(""), amount(0), category(BillCategory::TUITION), status(BillStatus::PENDING), billingDate("") {}

// Purpose: Parameterized Constructor | Parameters: bId (std::string), roll (std::string), amt (uint32_t), cat (BillCategory), stat (BillStatus), date (std::string) | Return Value: None | Complexity: O(1)
Bill::Bill(std::string bId, std::string roll, uint32_t amt, BillCategory cat, BillStatus stat, std::string date)
    : billId(bId), studentRollNumber(roll), amount(amt), category(cat), status(stat), billingDate(date) {}

// Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
Bill::~Bill() = default;

// Purpose: Copy Constructor | Parameters: other (const Bill&) | Return Value: None | Complexity: O(1)
Bill::Bill(const Bill& other)
    : billId(other.billId), studentRollNumber(other.studentRollNumber), amount(other.amount), category(other.category), status(other.status), billingDate(other.billingDate) {}

// Purpose: Copy Assignment Operator | Parameters: other (const Bill&) | Return Value: Bill& | Complexity: O(1)
Bill& Bill::operator=(const Bill& other) {
    if (this != &other) {
        billId = other.billId;
        studentRollNumber = other.studentRollNumber;
        amount = other.amount;
        category = other.category;
        status = other.status;
        billingDate = other.billingDate;
    }
    return *this;
}

// Purpose: Get Bill ID | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Bill::getBillId() const {
    return billId;
}

// Purpose: Set Bill ID | Parameters: bId (std::string) | Return Value: None | Complexity: O(1)
void Bill::setBillId(std::string bId) {
    billId = bId;
}

// Purpose: Get Student Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Bill::getStudentRollNumber() const {
    return studentRollNumber;
}

// Purpose: Set Student Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
void Bill::setStudentRollNumber(std::string roll) {
    studentRollNumber = roll;
}

// Purpose: Get Amount | Parameters: None | Return Value: uint32_t | Complexity: O(1)
uint32_t Bill::getAmount() const {
    return amount;
}

// Purpose: Set Amount | Parameters: amt (uint32_t) | Return Value: None | Complexity: O(1)
void Bill::setAmount(uint32_t amt) {
    amount = amt;
}

// Purpose: Get Bill Category | Parameters: None | Return Value: BillCategory | Complexity: O(1)
BillCategory Bill::getCategory() const {
    return category;
}

// Purpose: Set Bill Category | Parameters: cat (BillCategory) | Return Value: None | Complexity: O(1)
void Bill::setCategory(BillCategory cat) {
    category = cat;
}

// Purpose: Get Bill Status | Parameters: None | Return Value: BillStatus | Complexity: O(1)
BillStatus Bill::getStatus() const {
    return status;
}

// Purpose: Set Bill Status | Parameters: stat (BillStatus) | Return Value: None | Complexity: O(1)
void Bill::setStatus(BillStatus stat) {
    status = stat;
}

// Purpose: Get Billing Date | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Bill::getBillingDate() const {
    return billingDate;
}

// Purpose: Set Billing Date | Parameters: date (std::string) | Return Value: None | Complexity: O(1)
void Bill::setBillingDate(std::string date) {
    billingDate = date;
}
