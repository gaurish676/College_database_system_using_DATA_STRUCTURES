#ifndef AWARD_H
#define AWARD_H

#include <string>
#include <cstdint>

// Purpose: Represents academic honors, achievements, or scholarships awarded to students.
// Responsibilities: Tracks award details, associated student roll number, sponsoring bodies, and cash prizes.
// Data Structure Used: None
// Time Complexity: O(1) for all operations | Space Complexity: O(1)
// Dependencies: <string>, <cstdint>
class Award {
private:
    std::string awardId;
    std::string studentRollNumber;
    std::string awardName;
    std::string sponsoringBody;
    uint32_t cashPrize;
    std::string dateAwarded;

public:
    // Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Award();

    // Purpose: Parameterized Constructor | Parameters: aId (std::string), roll (std::string), name (std::string), sponsor (std::string), prize (uint32_t), date (std::string) | Return Value: None | Complexity: O(1)
    Award(std::string aId, std::string roll, std::string name, std::string sponsor, uint32_t prize, std::string date);

    // Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
    ~Award();

    // Purpose: Copy Constructor | Parameters: other (const Award&) | Return Value: None | Complexity: O(1)
    Award(const Award& other);

    // Purpose: Copy Assignment Operator | Parameters: other (const Award&) | Return Value: Award& | Complexity: O(1)
    Award& operator=(const Award& other);

    // Purpose: Get Award ID | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getAwardId() const;

    // Purpose: Set Award ID | Parameters: aId (std::string) | Return Value: None | Complexity: O(1)
    void setAwardId(std::string aId);

    // Purpose: Get Student Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getStudentRollNumber() const;

    // Purpose: Set Student Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
    void setStudentRollNumber(std::string roll);

    // Purpose: Get Award Name | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getAwardName() const;

    // Purpose: Set Award Name | Parameters: name (std::string) | Return Value: None | Complexity: O(1)
    void setAwardName(std::string name);

    // Purpose: Get Sponsoring Body | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getSponsoringBody() const;

    // Purpose: Set Sponsoring Body | Parameters: sponsor (std::string) | Return Value: None | Complexity: O(1)
    void setSponsoringBody(std::string sponsor);

    // Purpose: Get Cash Prize | Parameters: None | Return Value: uint32_t | Complexity: O(1)
    uint32_t getCashPrize() const;

    // Purpose: Set Cash Prize | Parameters: prize (uint32_t) | Return Value: None | Complexity: O(1)
    void setCashPrize(uint32_t prize);

    // Purpose: Get Date Awarded | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getDateAwarded() const;

    // Purpose: Set Date Awarded | Parameters: date (std::string) | Return Value: None | Complexity: O(1)
    void setDateAwarded(std::string date);
};

#endif // AWARD_H
