#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include <string>
#include "../datastructures/DoublyLinkedList.h"
#include "../datastructures/Graph.h"
#include "Student.h"
#include "Faculty.h"
#include "Course.h"

class StudentManager;
class FeeManager;
class AwardManager;
class BillingManager;

// Purpose: Generates formatted academic and financial reports.
// Responsibilities: Format reports for Student performance, outstanding fees, course sequences.
// Data Structure Used: Graph (for prerequisite sequence), DoublyLinkedList (for summary lookups).
// Time Complexity: O(V + E) for course sequence, O(N log N) for GPA reports | Space Complexity: O(N)
// Dependencies: "DoublyLinkedList.h", "Graph.h", Student.h, Faculty.h, Course.h
class ReportManager {
public:
    // Purpose: Print detailed Student profile, financial status, and academic honors | Parameters: student (const Student*), feeMgr (const FeeManager&), awardMgr (const AwardManager&), billMgr (const BillingManager&) | Return Value: None | Complexity: O(F + A + B)
    static void generateStudentSummary(const Student* student, const FeeManager& feeMgr, const AwardManager& awardMgr, const BillingManager& billMgr);

    // Purpose: Print Faculty profile and assigned schedule | Parameters: faculty (const Faculty*) | Return Value: None | Complexity: O(C)
    static void generateFacultySummary(const Faculty* faculty);

    // Purpose: Print Student leaderboard sorted by CGPA | Parameters: studentMgr (StudentManager&) | Return Value: None | Complexity: O(N log N)
    static void generateStudentGpaReport(StudentManager& studentMgr);

    // Purpose: Print outstanding fees and overdue ledger | Parameters: feeMgr (const FeeManager&) | Return Value: None | Complexity: O(N)
    static void generateOutstandingFeesReport(const FeeManager& feeMgr);

    // Purpose: Generate valid prerequisite course schedule | Parameters: courseList (const DoublyLinkedList<Course>&), prerequisiteGraph (const Graph<std::string>&) | Return Value: None | Complexity: O(V + E)
    static void generateCourseSequenceReport(const DoublyLinkedList<Course>& courseList, const Graph<std::string>& prerequisiteGraph);
};

#endif // REPORT_MANAGER_H
