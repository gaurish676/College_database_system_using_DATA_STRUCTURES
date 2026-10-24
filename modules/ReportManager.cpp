#include "../include/ReportManager.h"
#include "../include/StudentManager.h"
#include "../include/FeeManager.h"
#include "../include/AwardManager.h"
#include "../include/BillingManager.h"
#include <iostream>
#include <iomanip>

// Purpose: Print detailed Student profile, financial status, and academic honors | Parameters: student (const Student*), feeMgr (const FeeManager&), awardMgr (const AwardManager&), billMgr (const BillingManager&) | Return Value: None | Complexity: O(F + A + B)
void ReportManager::generateStudentSummary(const Student* student, const FeeManager& feeMgr, const AwardManager& awardMgr, const BillingManager& billMgr) {
    if (student == nullptr) return;

    std::cout << "\n==================================================\n";
    std::cout << "\033[36m             STUDENT ACADEMIC SUMMARY             \033[0m\n";
    std::cout << "==================================================\n";
    std::cout << "Roll Number : " << student->getRollNumber() << "\n";
    std::cout << "Name        : " << student->getName() << "\n";
    std::cout << "Email       : " << student->getEmail() << "\n";
    std::cout << "Department  : ";
    switch (student->getDepartment()) {
        case Department::COMPUTER_SCIENCE: std::cout << "Computer Science\n"; break;
        case Department::ELECTRICAL_ENG: std::cout << "Electrical Engineering\n"; break;
        case Department::MECHANICAL_ENG: std::cout << "Mechanical Engineering\n"; break;
        case Department::CIVIL_ENG: std::cout << "Civil Engineering\n"; break;
        case Department::PHYSICS: std::cout << "Physics\n"; break;
        case Department::CHEMISTRY: std::cout << "Chemistry\n"; break;
        case Department::MATHEMATICS: std::cout << "Mathematics\n"; break;
    }
    std::cout << "Semester    : Semester " << static_cast<int>(student->getSemester()) << "\n";
    std::cout << "CGPA        : " << std::fixed << std::setprecision(2) << student->getCgpa() << "\n";
    std::cout << "--------------------------------------------------\n";

    // Courses
    std::cout << "\033[33m[Enrolled Courses]\033[0m\n";
    const auto& courses = student->getEnrolledCourseIds();
    if (courses.isEmpty()) {
        std::cout << "  No courses enrolled currently.\n";
    } else {
        for (size_t i = 0; i < courses.getSize(); ++i) {
            std::cout << "  - " << courses[i] << "\n";
        }
    }
    std::cout << "--------------------------------------------------\n";

    // Fees
    std::cout << "\033[33m[Fee Statements]\033[0m\n";
    const auto& feeIds = student->getFeeIds();
    if (feeIds.isEmpty()) {
        std::cout << "  No fee records available.\n";
    } else {
        for (size_t i = 0; i < feeIds.getSize(); ++i) {
            Fee* f = feeMgr.getFeeById(feeIds[i]);
            if (f != nullptr) {
                std::cout << "  Fee ID: " << f->getFeeId() 
                          << " | Due: $" << f->getTotalAmount() 
                          << " | Paid: $" << f->getPaidAmount() 
                          << " | Status: ";
                if (f->getStatus() == FeeStatus::FULLY_PAID) std::cout << "\033[32mFULLY PAID\033[0m";
                else if (f->getStatus() == FeeStatus::PARTIALLY_PAID) std::cout << "\033[33mPARTIALLY PAID\033[0m";
                else std::cout << "\033[31mUNPAID\033[0m";
                std::cout << "\n";
            }
        }
    }
    std::cout << "--------------------------------------------------\n";

    // Awards
    std::cout << "\033[33m[Awards & Scholarships]\033[0m\n";
    const auto& awardIds = student->getAwardIds();
    if (awardIds.isEmpty()) {
        std::cout << "  No awards or honors recorded.\n";
    } else {
        for (size_t i = 0; i < awardIds.getSize(); ++i) {
            Award* a = awardMgr.getAwardById(awardIds[i]);
            if (a != nullptr) {
                std::cout << "  - " << a->getAwardName() << " (Issued by " << a->getSponsoringBody() << ") - $" << a->getCashPrize() << "\n";
            }
        }
    }
    std::cout << "--------------------------------------------------\n";

    // Bills
    std::cout << "\033[33m[Invoice billing]\033[0m\n";
    const auto& billIds = student->getBillIds();
    if (billIds.isEmpty()) {
        std::cout << "  No outstanding bills.\n";
    } else {
        for (size_t i = 0; i < billIds.getSize(); ++i) {
            Bill* b = billMgr.getBillById(billIds[i]);
            if (b != nullptr) {
                std::cout << "  Bill ID: " << b->getBillId() << " | Amount: $" << b->getAmount() << " | Category: ";
                switch (b->getCategory()) {
                    case BillCategory::TUITION: std::cout << "Tuition"; break;
                    case BillCategory::HOSTEL: std::cout << "Hostel"; break;
                    case BillCategory::LIBRARY: std::cout << "Library"; break;
                    case BillCategory::MESS: std::cout << "Mess"; break;
                    case BillCategory::OTHER: std::cout << "Other"; break;
                }
                std::cout << " | Status: ";
                if (b->getStatus() == BillStatus::PAID) std::cout << "\033[32mPAID\033[0m";
                else if (b->getStatus() == BillStatus::PENDING) std::cout << "\033[33mPENDING\033[0m";
                else std::cout << "\033[31mCANCELLED\033[0m";
                std::cout << "\n";
            }
        }
    }
    std::cout << "==================================================\n";
}

// Purpose: Print Faculty profile and assigned schedule | Parameters: faculty (const Faculty*) | Return Value: None | Complexity: O(C)
void ReportManager::generateFacultySummary(const Faculty* faculty) {
    if (faculty == nullptr) return;

    std::cout << "\n==================================================\n";
    std::cout << "\033[36m             FACULTY MEMBER DIRECTORY             \033[0m\n";
    std::cout << "==================================================\n";
    std::cout << "Faculty ID  : " << faculty->getFacultyId() << "\n";
    std::cout << "Name        : " << faculty->getName() << "\n";
    std::cout << "Email       : " << faculty->getEmail() << "\n";
    std::cout << "Department  : ";
    switch (faculty->getDepartment()) {
        case Department::COMPUTER_SCIENCE: std::cout << "Computer Science\n"; break;
        case Department::ELECTRICAL_ENG: std::cout << "Electrical Engineering\n"; break;
        case Department::MECHANICAL_ENG: std::cout << "Mechanical Engineering\n"; break;
        case Department::CIVIL_ENG: std::cout << "Civil Engineering\n"; break;
        case Department::PHYSICS: std::cout << "Physics\n"; break;
        case Department::CHEMISTRY: std::cout << "Chemistry\n"; break;
        case Department::MATHEMATICS: std::cout << "Mathematics\n"; break;
    }
    std::cout << "Designation : " << faculty->getDesignation() << "\n";
    std::cout << "Salary      : $" << faculty->getSalary() << "\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "\033[33m[Teaching Assignment]\033[0m\n";
    const auto& courses = faculty->getCourseIds();
    if (courses.isEmpty()) {
        std::cout << "  No courses assigned to teach.\n";
    } else {
        for (size_t i = 0; i < courses.getSize(); ++i) {
            std::cout << "  - Course: " << courses[i] << "\n";
        }
    }
    std::cout << "==================================================\n";
}

// Purpose: Print Student leaderboard sorted by CGPA | Parameters: studentMgr (StudentManager&) | Return Value: None | Complexity: O(N log N)
void ReportManager::generateStudentGpaReport(StudentManager& studentMgr) {
    DynamicArray<Student*> leaderboard;
    studentMgr.getTopKStudents(studentMgr.getStudents().getSize(), leaderboard);

    std::cout << "\n============================================================\n";
    std::cout << "\033[32m             STUDENT ACADEMIC PERFORMANCE LEADERBOARD       \033[0m\n";
    std::cout << "============================================================\n";
    std::cout << std::left << std::setw(6) << "Rank" 
              << std::setw(15) << "Roll No" 
              << std::setw(25) << "Student Name" 
              << "CGPA\n";
    std::cout << "------------------------------------------------------------\n";
    for (size_t i = 0; i < leaderboard.getSize(); ++i) {
        std::cout << std::left << std::setw(6) << (i + 1)
                  << std::setw(15) << leaderboard[i]->getRollNumber()
                  << std::setw(25) << leaderboard[i]->getName()
                  << std::fixed << std::setprecision(2) << leaderboard[i]->getCgpa() << "\n";
    }
    std::cout << "============================================================\n";
}

// Purpose: Print outstanding fees and overdue ledger | Parameters: feeMgr (const FeeManager&) | Return Value: None | Complexity: O(N)
void ReportManager::generateOutstandingFeesReport(const FeeManager& feeMgr) {
    std::cout << "\n======================================================================\n";
    std::cout << "\033[31m                 OUTSTANDING STUDENT FEES REPORT                     \033[0m\n";
    std::cout << "======================================================================\n";
    std::cout << std::left << std::setw(12) << "Fee ID" 
              << std::setw(15) << "Student Roll" 
              << std::setw(15) << "Total Due" 
              << std::setw(15) << "Amount Paid" 
              << "Pending Balance\n";
    std::cout << "----------------------------------------------------------------------\n";

    uint64_t totalPending = 0;
    const auto& fees = feeMgr.getFees();
    auto current = fees.getHead();
    while (current != nullptr) {
        if (current->data.getStatus() != FeeStatus::FULLY_PAID) {
            uint32_t pending = current->data.getTotalAmount() - current->data.getPaidAmount();
            totalPending += pending;
            std::cout << std::left << std::setw(12) << current->data.getFeeId()
                      << std::setw(15) << current->data.getStudentRollNumber()
                      << "$" << std::setw(14) << current->data.getTotalAmount()
                      << "$" << std::setw(14) << current->data.getPaidAmount()
                      << "$" << pending << "\n";
        }
        current = current->next;
    }
    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "\033[33mTotal Deficit / Pending Account Balances: $" << totalPending << "\033[0m\n";
    std::cout << "======================================================================\n";
}

// Purpose: Generate valid prerequisite course schedule | Parameters: courseList (const DoublyLinkedList<Course>&), prerequisiteGraph (const Graph<std::string>&) | Return Value: None | Complexity: O(V + E)
void ReportManager::generateCourseSequenceReport(const DoublyLinkedList<Course>& courseList, const Graph<std::string>& prerequisiteGraph) {
    std::cout << "\n============================================================\n";
    std::cout << "\033[36m             CURRICULUM PREREQUISITE SEQUENCE REPORT        \033[0m\n";
    std::cout << "============================================================\n";

    DynamicArray<std::string> sortedSequence;
    if (!prerequisiteGraph.topologicalSort(sortedSequence)) {
        std::cout << "\033[31m[ERROR] Cyclic course prerequisite dependencies detected!\033[0m\n";
        std::cout << "Cannot generate a valid course order sequence. Please resolve cyclic requirements.\n";
        std::cout << "============================================================\n";
        return;
    }

    if (sortedSequence.isEmpty()) {
        std::cout << "  No courses in prerequisite database.\n";
        std::cout << "============================================================\n";
        return;
    }

    std::cout << "Suggested semester/course take sequence:\n\n";
    int step = 1;
    for (size_t i = 0; i < sortedSequence.getSize(); ++i) {
        std::string cId = sortedSequence[i];
        
        // Find course name
        std::string cName = "Unknown Course";
        auto curr = courseList.getHead();
        while (curr != nullptr) {
            if (curr->data.getCourseId() == cId) {
                cName = curr->data.getCourseName();
                break;
            }
            curr = curr->next;
        }
        
        std::cout << "  " << step++ << ". " << cId << " - " << cName << "\n";
    }
    std::cout << "============================================================\n";
}
