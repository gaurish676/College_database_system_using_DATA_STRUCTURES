#include "../include/Fee.h"

// Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
Fee::Fee()
    : feeId(""), studentRollNumber(""), totalAmount(0), paidAmount(0), status(FeeStatus::UNPAID), dueDate("") {}

// Purpose: Parameterized Constructor | Parameters: fId (std::string), roll (std::string), total (uint32_t), paid (uint32_t), stat (FeeStatus), due (std::string) | Return Value: None | Complexity: O(1)
Fee::Fee(std::string fId, std::string roll, uint32_t total, uint32_t paid, FeeStatus stat, std::string due)
    : feeId(fId), studentRollNumber(roll), totalAmount(total), paidAmount(paid), status(stat), dueDate(due) {}

// Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
Fee::~Fee() = default;

// Purpose: Copy Constructor | Parameters: other (const Fee&) | Return Value: None | Complexity: O(1)
Fee::Fee(const Fee& other)
    : feeId(other.feeId), studentRollNumber(other.studentRollNumber), totalAmount(other.totalAmount), paidAmount(other.paidAmount), status(other.status), dueDate(other.dueDate) {}

// Purpose: Copy Assignment Operator | Parameters: other (const Fee&) | Return Value: Fee& | Complexity: O(1)
Fee& Fee::operator=(const Fee& other) {
    if (this != &other) {
        feeId = other.feeId;
        studentRollNumber = other.studentRollNumber;
        totalAmount = other.totalAmount;
        paidAmount = other.paidAmount;
        status = other.status;
        dueDate = other.dueDate;
    }
    return *this;
}

// Purpose: Get Fee ID | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Fee::getFeeId() const {
    return feeId;
}

// Purpose: Set Fee ID | Parameters: fId (std::string) | Return Value: None | Complexity: O(1)
void Fee::setFeeId(std::string fId) {
    feeId = fId;
}

// Purpose: Get Student Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Fee::getStudentRollNumber() const {
    return studentRollNumber;
}

// Purpose: Set Student Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
void Fee::setStudentRollNumber(std::string roll) {
    studentRollNumber = roll;
}

// Purpose: Get Total Amount | Parameters: None | Return Value: uint32_t | Complexity: O(1)
uint32_t Fee::getTotalAmount() const {
    return totalAmount;
}

// Purpose: Set Total Amount | Parameters: total (uint32_t) | Return Value: None | Complexity: O(1)
void Fee::setTotalAmount(uint32_t total) {
    totalAmount = total;
}

// Purpose: Get Paid Amount | Parameters: None | Return Value: uint32_t | Complexity: O(1)
uint32_t Fee::getPaidAmount() const {
    return paidAmount;
}

// Purpose: Set Paid Amount | Parameters: paid (uint32_t) | Return Value: None | Complexity: O(1)
void Fee::setPaidAmount(uint32_t paid) {
    paidAmount = paid;
}

// Purpose: Get Fee Status | Parameters: None | Return Value: FeeStatus | Complexity: O(1)
FeeStatus Fee::getStatus() const {
    return status;
}

// Purpose: Set Fee Status | Parameters: stat (FeeStatus) | Return Value: None | Complexity: O(1)
void Fee::setStatus(FeeStatus stat) {
    status = stat;
}

// Purpose: Get Due Date | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Fee::getDueDate() const {
    return dueDate;
}

// Purpose: Set Due Date | Parameters: due (std::string) | Return Value: None | Complexity: O(1)
void Fee::setDueDate(std::string due) {
    dueDate = due;
}
