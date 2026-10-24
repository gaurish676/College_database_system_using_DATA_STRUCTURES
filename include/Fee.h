#ifndef FEE_H
#define FEE_H

#include <string>
#include <cstdint>

enum class FeeStatus : uint8_t {
    UNPAID = 0,
    PARTIALLY_PAID = 1,
    FULLY_PAID = 2
};

// Purpose: Represents the fee structure and payment records for students.
// Responsibilities: Maintain fee status, total/paid amounts, and associated student tracking.
// Data Structure Used: None
// Time Complexity: O(1) for all operations | Space Complexity: O(1)
// Dependencies: <string>, <cstdint>
class Fee {
private:
    std::string feeId;
    std::string studentRollNumber;
    uint32_t totalAmount;
    uint32_t paidAmount;
    FeeStatus status;
    std::string dueDate;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Fee();

    // Purpose: Parameterized Constructor | Parameters: fId (std::string), roll (std::string), total (uint32_t), paid (uint32_t), stat (FeeStatus), due (std::string) | Return Value: None | Complexity: O(1)
    Fee(std::string fId, std::string roll, uint32_t total, uint32_t paid, FeeStatus stat, std::string due);

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
    ~Fee();

    // Purpose: Copy Constructor | Parameters: other (const Fee&) | Return Value: None | Complexity: O(1)
    Fee(const Fee& other);

    // Purpose: Copy Assignment Operator | Parameters: other (const Fee&) | Return Value: Fee& | Complexity: O(1)
    Fee& operator=(const Fee& other);

    // Purpose: Get Fee ID | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getFeeId() const;

    // Purpose: Set Fee ID | Parameters: fId (std::string) | Return Value: None | Complexity: O(1)
    void setFeeId(std::string fId);

    // Purpose: Get Student Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getStudentRollNumber() const;

    // Purpose: Set Student Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
    void setStudentRollNumber(std::string roll);

    // Purpose: Get Total Amount | Parameters: None | Return Value: uint32_t | Complexity: O(1)
    uint32_t getTotalAmount() const;

    // Purpose: Set Total Amount | Parameters: total (uint32_t) | Return Value: None | Complexity: O(1)
    void setTotalAmount(uint32_t total);

    // Purpose: Get Paid Amount | Parameters: None | Return Value: uint32_t | Complexity: O(1)
    uint32_t getPaidAmount() const;

    // Purpose: Set Paid Amount | Parameters: paid (uint32_t) | Return Value: None | Complexity: O(1)
    void setPaidAmount(uint32_t paid);

    // Purpose: Get Fee Status | Parameters: None | Return Value: FeeStatus | Complexity: O(1)
    FeeStatus getStatus() const;

    // Purpose: Set Fee Status | Parameters: stat (FeeStatus) | Return Value: None | Complexity: O(1)
    void setStatus(FeeStatus stat);

    // Purpose: Get Due Date | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getDueDate() const;

    // Purpose: Set Due Date | Parameters: due (std::string) | Return Value: None | Complexity: O(1)
    void setDueDate(std::string due);
};

#endif // FEE_H
