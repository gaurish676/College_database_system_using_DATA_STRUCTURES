#ifndef BILL_H
#define BILL_H

#include <string>
#include <cstdint>

enum class BillCategory : uint8_t {
    TUITION = 0,
    HOSTEL = 1,
    LIBRARY = 2,
    MESS = 3,
    OTHER = 4
};

enum class BillStatus : uint8_t {
    PENDING = 0,
    PAID = 1,
    CANCELLED = 2
};

// Purpose: Represents transactional billing and invoices issued to students.
// Responsibilities: Tracks invoice details, category type (Tuition, Hostel, etc.), payment status, and dates.
// Data Structure Used: None
// Time Complexity: O(1) for all operations | Space Complexity: O(1)
// Dependencies: <string>, <cstdint>
class Bill {
private:
    std::string billId;
    std::string studentRollNumber;
    uint32_t amount;
    BillCategory category;
    BillStatus status;
    std::string billingDate;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Bill();

    // Purpose: Parameterized Constructor | Parameters: bId (std::string), roll (std::string), amt (uint32_t), cat (BillCategory), stat (BillStatus), date (std::string) | Return Value: None | Complexity: O(1)
    Bill(std::string bId, std::string roll, uint32_t amt, BillCategory cat, BillStatus stat, std::string date);

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
    ~Bill();

    // Purpose: Copy Constructor | Parameters: other (const Bill&) | Return Value: None | Complexity: O(1)
    Bill(const Bill& other);

    // Purpose: Copy Assignment Operator | Parameters: other (const Bill&) | Return Value: Bill& | Complexity: O(1)
    Bill& operator=(const Bill& other);

    // Purpose: Get Bill ID | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getBillId() const;

    // Purpose: Set Bill ID | Parameters: bId (std::string) | Return Value: None | Complexity: O(1)
    void setBillId(std::string bId);

    // Purpose: Get Student Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getStudentRollNumber() const;

    // Purpose: Set Student Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
    void setStudentRollNumber(std::string roll);

    // Purpose: Get Amount | Parameters: None | Return Value: uint32_t | Complexity: O(1)
    uint32_t getAmount() const;

    // Purpose: Set Amount | Parameters: amt (uint32_t) | Return Value: None | Complexity: O(1)
    void setAmount(uint32_t amt);

    // Purpose: Get Bill Category | Parameters: None | Return Value: BillCategory | Complexity: O(1)
    BillCategory getCategory() const;

    // Purpose: Set Bill Category | Parameters: cat (BillCategory) | Return Value: None | Complexity: O(1)
    void setCategory(BillCategory cat);

    // Purpose: Get Bill Status | Parameters: None | Return Value: BillStatus | Complexity: O(1)
    BillStatus getStatus() const;

    // Purpose: Set Bill Status | Parameters: stat (BillStatus) | Return Value: None | Complexity: O(1)
    void setStatus(BillStatus stat);

    // Purpose: Get Billing Date | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getBillingDate() const;

    // Purpose: Set Billing Date | Parameters: date (std::string) | Return Value: None | Complexity: O(1)
    void setBillingDate(std::string date);
};

#endif // BILL_H
