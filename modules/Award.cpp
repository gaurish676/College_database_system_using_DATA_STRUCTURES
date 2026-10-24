#include "../include/Award.h"

// Purpose: Default Constructor | Parameters: None | Return Value: None | Complexity: O(1)
Award::Award()
    : awardId(""), studentRollNumber(""), awardName(""), sponsoringBody(""), cashPrize(0), dateAwarded("") {}

// Purpose: Parameterized Constructor | Parameters: aId (std::string), roll (std::string), name (std::string), sponsor (std::string), prize (uint32_t), date (std::string) | Return Value: None | Complexity: O(1)
Award::Award(std::string aId, std::string roll, std::string name, std::string sponsor, uint32_t prize, std::string date)
    : awardId(aId), studentRollNumber(roll), awardName(name), sponsoringBody(sponsor), cashPrize(prize), dateAwarded(date) {}

// Purpose: Destructor | Parameters: None | Return Value: None | Complexity: O(1)
Award::~Award() = default;

// Purpose: Copy Constructor | Parameters: other (const Award&) | Return Value: None | Complexity: O(1)
Award::Award(const Award& other)
    : awardId(other.awardId), studentRollNumber(other.studentRollNumber), awardName(other.awardName), sponsoringBody(other.sponsoringBody), cashPrize(other.cashPrize), dateAwarded(other.dateAwarded) {}

// Purpose: Copy Assignment Operator | Parameters: other (const Award&) | Return Value: Award& | Complexity: O(1)
Award& Award::operator=(const Award& other) {
    if (this != &other) {
        awardId = other.awardId;
        studentRollNumber = other.studentRollNumber;
        awardName = other.awardName;
        sponsoringBody = other.sponsoringBody;
        cashPrize = other.cashPrize;
        dateAwarded = other.dateAwarded;
    }
    return *this;
}

// Purpose: Get Award ID | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Award::getAwardId() const {
    return awardId;
}

// Purpose: Set Award ID | Parameters: aId (std::string) | Return Value: None | Complexity: O(1)
void Award::setAwardId(std::string aId) {
    awardId = aId;
}

// Purpose: Get Student Roll Number | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Award::getStudentRollNumber() const {
    return studentRollNumber;
}

// Purpose: Set Student Roll Number | Parameters: roll (std::string) | Return Value: None | Complexity: O(1)
void Award::setStudentRollNumber(std::string roll) {
    studentRollNumber = roll;
}

// Purpose: Get Award Name | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Award::getAwardName() const {
    return awardName;
}

// Purpose: Set Award Name | Parameters: name (std::string) | Return Value: None | Complexity: O(1)
void Award::setAwardName(std::string name) {
    awardName = name;
}

// Purpose: Get Sponsoring Body | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Award::getSponsoringBody() const {
    return sponsoringBody;
}

// Purpose: Set Sponsoring Body | Parameters: sponsor (std::string) | Return Value: None | Complexity: O(1)
void Award::setSponsoringBody(std::string sponsor) {
    sponsoringBody = sponsor;
}

// Purpose: Get Cash Prize | Parameters: None | Return Value: uint32_t | Complexity: O(1)
uint32_t Award::getCashPrize() const {
    return cashPrize;
}

// Purpose: Set Cash Prize | Parameters: prize (uint32_t) | Return Value: None | Complexity: O(1)
void Award::setCashPrize(uint32_t prize) {
    cashPrize = prize;
}

// Purpose: Get Date Awarded | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Award::getDateAwarded() const {
    return dateAwarded;
}

// Purpose: Set Date Awarded | Parameters: date (std::string) | Return Value: None | Complexity: O(1)
void Award::setDateAwarded(std::string date) {
    dateAwarded = date;
}
