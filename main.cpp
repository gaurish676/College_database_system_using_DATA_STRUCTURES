#include "include/StudentManager.h"
#include "include/FacultyManager.h"
#include "include/FeeManager.h"
#include "include/AwardManager.h"
#include "include/BillingManager.h"
#include "include/SearchManager.h"
#include "include/ReportManager.h"
#include "include/Authentication.h"
#include "include/Utilities.h"
#include "include/Logger.h"
#include "include/Validator.h"
#include "include/Serializer.h"
#include "include/Deserializer.h"
#include "include/FileManager.h"

#include <iostream>
#include <fstream>
#include <string>

// Purpose: Serialize Graph edge dependencies | Parameters: filepath (const std::string&), graph (const Graph<std::string>&) | Return Value: bool | Complexity: O(V + E)
bool savePrerequisites(const std::string& filepath, const Graph<std::string>& graph) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) return false;

    DynamicArray<std::string> vertices = graph.getVertices();
    uint32_t vSize = static_cast<uint32_t>(vertices.getSize());
    ofs.write(reinterpret_cast<const char*>(&vSize), sizeof(vSize));

    for (size_t i = 0; i < vertices.getSize(); ++i) {
        std::string v = vertices[i];
        Serializer::writeString(ofs, v);

        const LinkedList<std::string>* neighbors = graph.getNeighbors(v);
        uint32_t nSize = neighbors ? static_cast<uint32_t>(neighbors->getSize()) : 0;
        ofs.write(reinterpret_cast<const char*>(&nSize), sizeof(nSize));

        if (neighbors) {
            auto curr = neighbors->getHead();
            while (curr != nullptr) {
                Serializer::writeString(ofs, curr->data);
                curr = curr->next;
            }
        }
    }
    return true;
}

// Purpose: Deserialize Graph edge dependencies | Parameters: filepath (const std::string&), graph (Graph<std::string>&) | Return Value: bool | Complexity: O(V + E)
bool loadPrerequisites(const std::string& filepath, Graph<std::string>& graph) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) return false;

    graph.clear();
    uint32_t vSize = 0;
    ifs.read(reinterpret_cast<char*>(&vSize), sizeof(vSize));

    for (uint32_t i = 0; i < vSize; ++i) {
        std::string v = Deserializer::readString(ifs);
        graph.addVertex(v);

        uint32_t nSize = 0;
        ifs.read(reinterpret_cast<char*>(&nSize), sizeof(nSize));
        for (uint32_t j = 0; j < nSize; ++j) {
            std::string neighbor = Deserializer::readString(ifs);
            graph.addEdge(v, neighbor);
        }
    }
    return true;
}

// Helper menus
void showAuthMenu();
void showMainMenu(const std::string& username);
void handleStudentMenu(StudentManager& studentMgr, const FeeManager& feeMgr, const AwardManager& awardMgr, const BillingManager& billMgr);
void handleFacultyMenu(FacultyManager& facultyMgr);
void handleCourseMenu(DoublyLinkedList<Course>& courseList, Graph<std::string>& prerequisiteGraph);
void handleFinanceMenu(StudentManager& studentMgr, FeeManager& feeMgr, BillingManager& billMgr);
void handleAwardMenu(StudentManager& studentMgr, AwardManager& awardMgr);

int main() {
    // Ensure data directory exists (is kept by gitkeep)
    Authentication auth;
    StudentManager studentMgr;
    FacultyManager facultyMgr;
    FeeManager feeMgr;
    AwardManager awardMgr;
    BillingManager billMgr;

    DoublyLinkedList<Course> courseList;
    Graph<std::string> prerequisiteGraph;
    
    // Load courses
    FileManager::loadCourses("data/courses.dat", courseList);
    loadPrerequisites("data/prerequisites.dat", prerequisiteGraph);

    bool running = true;
    while (running) {
        Utilities::clearConsole();
        if (!auth.isSessionActive()) {
            std::cout << "\033[36m==================================================\n";
            std::cout << "         COLLEGE ERP SECURITY GATEWAY             \n";
            std::cout << "==================================================\033[0m\n";
            std::cout << "  1. Login Session\n";
            std::cout << "  2. Register Administrator Account\n";
            std::cout << "  3. Terminate Application\n";
            std::cout << "--------------------------------------------------\n";
            int choice = Utilities::getIntegerInput("Choose gateway action (1-3): ", 1, 3);
            
            if (choice == 1) {
                Utilities::clearConsole();
                std::cout << "\033[36m--- SECURE LOGIN ---\033[0m\n";
                std::string user = Utilities::getStringInput("Enter Username: ");
                std::string pass = Utilities::getStringInput("Enter Password: ");
                if (auth.login(user, pass)) {
                    Logger::success("Access Granted! Opening system dashboard...");
                    Utilities::pressEnterToContinue();
                } else {
                    Logger::error("Authentication failed! Invalid credentials.");
                    Utilities::pressEnterToContinue();
                }
            } else if (choice == 2) {
                Utilities::clearConsole();
                std::cout << "\033[36m--- ADMINISTRATOR REGISTRATION ---\033[0m\n";
                std::string user = Utilities::getStringInput("Register Username: ");
                std::string pass = Utilities::getStringInput("Register Password: ");
                if (auth.registerUser(user, pass)) {
                    Logger::success("Administrator registered successfully!");
                } else {
                    Logger::error("Registration failed! Username might already exist.");
                }
                Utilities::pressEnterToContinue();
            } else {
                running = false;
            }
        } else {
            // Dashboard Menu
            std::cout << "\033[32m============================================================\n";
            std::cout << "        COLLEGE ERP & DATABASE SYSTEM DASHBOARD            \n";
            std::cout << "============================================================\033[0m\n";
            std::cout << "  Logged in as: \033[33m" << auth.getLoggedInUser() << "\033[0m\n";
            std::cout << "------------------------------------------------------------\n";
            std::cout << "  1. Student Academic Management\n";
            std::cout << "  2. Faculty & Staff Records\n";
            std::cout << "  3. Course Database & Prerequisites\n";
            std::cout << "  4. Finance & Outstanding Student Invoices\n";
            std::cout << "  5. Academic Honors & Scholarship Awards\n";
            std::cout << "  6. Log Out Session\n";
            std::cout << "  7. Save Databases & Terminate\n";
            std::cout << "------------------------------------------------------------\n";
            int choice = Utilities::getIntegerInput("Enter Dashboard Action (1-7): ", 1, 7);

            if (choice == 1) {
                handleStudentMenu(studentMgr, feeMgr, awardMgr, billMgr);
            } else if (choice == 2) {
                handleFacultyMenu(facultyMgr);
            } else if (choice == 3) {
                handleCourseMenu(courseList, prerequisiteGraph);
            } else if (choice == 4) {
                handleFinanceMenu(studentMgr, feeMgr, billMgr);
            } else if (choice == 5) {
                handleAwardMenu(studentMgr, awardMgr);
            } else if (choice == 6) {
                auth.logout();
                Logger::info("Logged out successfully.");
                Utilities::pressEnterToContinue();
            } else {
                // Save databases and exit
                studentMgr.saveToFile();
                facultyMgr.saveToFile();
                feeMgr.saveToFile();
                awardMgr.saveToFile();
                billMgr.saveToFile();
                FileManager::saveCourses("data/courses.dat", courseList);
                savePrerequisites("data/prerequisites.dat", prerequisiteGraph);
                Logger::success("Databases saved successfully to disk. Goodbye!");
                running = false;
            }
        }
    }
    return 0;
}

void handleStudentMenu(StudentManager& studentMgr, const FeeManager& feeMgr, const AwardManager& awardMgr, const BillingManager& billMgr) {
    bool inMenu = true;
    while (inMenu) {
        Utilities::clearConsole();
        std::cout << "\033[32m--- STUDENT ACADEMIC MANAGEMENT ---\033[0m\n";
        std::cout << "  1. Add Student Profile\n";
        std::cout << "  2. Remove Student Record (O(1) index removal)\n";
        std::cout << "  3. Search Student by Roll Number (O(1) Hash Table Index)\n";
        std::cout << "  4. Search Student by Name (O(log N) AVL Tree Index)\n";
        std::cout << "  5. Wildcard Name Prefix Lookup (Ternary Search Tree Index)\n";
        std::cout << "  6. View Class Leaderboard (Heap Index)\n";
        std::cout << "  7. Enroll Student in Course\n";
        std::cout << "  8. Unenroll Student from Course\n";
        std::cout << "  9. Back to Dashboard\n";
        std::cout << "-----------------------------------\n";
        int choice = Utilities::getIntegerInput("Choose student module action (1-9): ", 1, 9);

        if (choice == 1) {
            Utilities::clearConsole();
            std::cout << "--- Create Student Profile ---\n";
            std::string roll = Utilities::getStringInput("Roll Number: ");
            std::string name = Utilities::getStringInput("Full Name: ");
            std::string email;
            while (true) {
                email = Utilities::getStringInput("Email Address: ");
                if (Validator::isValidEmail(email)) break;
                Logger::error("Invalid email syntax! Try again.");
            }
            std::cout << "Departments:\n 1. Computer Science\n 2. Electrical\n 3. Mechanical\n 4. Civil\n 5. Physics\n 6. Chemistry\n 7. Mathematics\n";
            Department dept = static_cast<Department>(Utilities::getIntegerInput("Choose Department (1-7): ", 1, 7));
            Semester sem = static_cast<Semester>(Utilities::getIntegerInput("Choose Semester (1-8): ", 1, 8));
            double cgpa = Utilities::getDoubleInput("Enter CGPA (0.0 - 10.0): ", 0.0, 10.0);

            Student s(roll, name, email, dept, sem, cgpa);
            if (studentMgr.addStudent(s)) {
                Logger::success("Student added successfully to database and indexes!");
            } else {
                Logger::error("Duplicate roll number detected. Student not added.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 2) {
            Utilities::clearConsole();
            std::cout << "--- Delete Student Record ---\n";
            std::string roll = Utilities::getStringInput("Enter Student Roll Number to delete: ");
            if (studentMgr.removeStudent(roll)) {
                Logger::success("Student deleted from master list and all secondary indexes!");
            } else {
                Logger::error("Student not found.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 3) {
            Utilities::clearConsole();
            std::cout << "--- Exact Roll Number Search ---\n";
            std::string roll = Utilities::getStringInput("Enter Roll Number: ");
            Student* s = SearchManager::searchStudentByRoll(roll, studentMgr);
            if (s != nullptr) {
                ReportManager::generateStudentSummary(s, feeMgr, awardMgr, billMgr);
            } else {
                Logger::error("Student not found.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 4) {
            Utilities::clearConsole();
            std::cout << "--- Exact Name Search ---\n";
            std::string name = Utilities::getStringInput("Enter Student Full Name: ");
            Student* s = SearchManager::searchStudentByNameExact(name, studentMgr);
            if (s != nullptr) {
                ReportManager::generateStudentSummary(s, feeMgr, awardMgr, billMgr);
            } else {
                Logger::error("Student not found.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 5) {
            Utilities::clearConsole();
            std::cout << "--- Wildcard Prefix Search ---\n";
            std::string prefix = Utilities::getStringInput("Enter Name Prefix: ");
            DynamicArray<Student*> results;
            SearchManager::autoCompleteStudentName(prefix, studentMgr, results);
            std::cout << "\nResults found: " << results.getSize() << "\n";
            for (size_t i = 0; i < results.getSize(); ++i) {
                std::cout << " - Roll: " << results[i]->getRollNumber() << " | Name: " << results[i]->getName() << " | GPA: " << results[i]->getCgpa() << "\n";
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 6) {
            Utilities::clearConsole();
            ReportManager::generateStudentGpaReport(studentMgr);
            Utilities::pressEnterToContinue();
        } else if (choice == 7) {
            Utilities::clearConsole();
            std::cout << "--- Enroll in Course ---\n";
            std::string roll = Utilities::getStringInput("Student Roll Number: ");
            Student* s = studentMgr.getStudentByRoll(roll);
            if (s != nullptr) {
                std::string cId = Utilities::getStringInput("Enter Course ID to enroll: ");
                s->enrollCourse(cId);
                studentMgr.saveToFile();
                Logger::success("Student enrolled in course successfully!");
            } else {
                Logger::error("Student not found.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 8) {
            Utilities::clearConsole();
            std::cout << "--- Unenroll from Course ---\n";
            std::string roll = Utilities::getStringInput("Student Roll Number: ");
            Student* s = studentMgr.getStudentByRoll(roll);
            if (s != nullptr) {
                std::string cId = Utilities::getStringInput("Enter Course ID to unenroll: ");
                if (s->unenrollCourse(cId)) {
                    studentMgr.saveToFile();
                    Logger::success("Course unenrolled successfully.");
                } else {
                    Logger::error("Course enrollment record not found.");
                }
            } else {
                Logger::error("Student not found.");
            }
            Utilities::pressEnterToContinue();
        } else {
            inMenu = false;
        }
    }
}

void handleFacultyMenu(FacultyManager& facultyMgr) {
    bool inMenu = true;
    while (inMenu) {
        Utilities::clearConsole();
        std::cout << "\033[32m--- FACULTY & STAFF RECORDS ---\033[0m\n";
        std::cout << "  1. Add Faculty Record\n";
        std::cout << "  2. Remove Faculty Record\n";
        std::cout << "  3. Search Faculty by ID\n";
        std::cout << "  4. Assign Course to Teach\n";
        std::cout << "  5. Back to Dashboard\n";
        std::cout << "-------------------------------\n";
        int choice = Utilities::getIntegerInput("Choose faculty module action (1-5): ", 1, 5);

        if (choice == 1) {
            Utilities::clearConsole();
            std::cout << "--- Create Faculty Record ---\n";
            std::string id = Utilities::getStringInput("Faculty ID: ");
            std::string name = Utilities::getStringInput("Full Name: ");
            std::string email;
            while (true) {
                email = Utilities::getStringInput("Email Address: ");
                if (Validator::isValidEmail(email)) break;
                Logger::error("Invalid email syntax! Try again.");
            }
            std::cout << "Departments:\n 1. Computer Science\n 2. Electrical\n 3. Mechanical\n 4. Civil\n 5. Physics\n 6. Chemistry\n 7. Mathematics\n";
            Department dept = static_cast<Department>(Utilities::getIntegerInput("Choose Department (1-7): ", 1, 7));
            std::string des = Utilities::getStringInput("Designation: ");
            int salary = Utilities::getIntegerInput("Salary amount ($): ", 0, 1000000);

            Faculty f(id, name, email, dept, des, salary);
            if (facultyMgr.addFaculty(f)) {
                Logger::success("Faculty member registered successfully!");
            } else {
                Logger::error("Duplicate faculty ID. Faculty not added.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 2) {
            Utilities::clearConsole();
            std::cout << "--- Delete Faculty Record ---\n";
            std::string id = Utilities::getStringInput("Enter Faculty ID to delete: ");
            if (facultyMgr.removeFaculty(id)) {
                Logger::success("Faculty record deleted.");
            } else {
                Logger::error("Faculty record not found.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 3) {
            Utilities::clearConsole();
            std::cout << "--- Search Faculty ---\n";
            std::string id = Utilities::getStringInput("Enter Faculty ID: ");
            Faculty* f = SearchManager::searchFacultyById(id, facultyMgr);
            if (f != nullptr) {
                ReportManager::generateFacultySummary(f);
            } else {
                Logger::error("Faculty record not found.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 4) {
            Utilities::clearConsole();
            std::cout << "--- Assign Teaching Course ---\n";
            std::string id = Utilities::getStringInput("Faculty ID: ");
            Faculty* f = facultyMgr.getFacultyById(id);
            if (f != nullptr) {
                std::string cId = Utilities::getStringInput("Enter Course ID to assign: ");
                f->assignCourse(cId);
                facultyMgr.saveToFile();
                Logger::success("Course teaching assignment updated successfully!");
            } else {
                Logger::error("Faculty member not found.");
            }
            Utilities::pressEnterToContinue();
        } else {
            inMenu = false;
        }
    }
}

void handleCourseMenu(DoublyLinkedList<Course>& courseList, Graph<std::string>& prerequisiteGraph) {
    bool inMenu = true;
    while (inMenu) {
        Utilities::clearConsole();
        std::cout << "\033[32m--- COURSE DATABASE & PREREQUISITES ---\033[0m\n";
        std::cout << "  1. Add Course to Curriculum\n";
        std::cout << "  2. Add Prerequisite Edge (Graph dependency)\n";
        std::cout << "  3. View Valid Course Take Sequence (Topological Sort)\n";
        std::cout << "  4. Clear Course database\n";
        std::cout << "  5. Back to Dashboard\n";
        std::cout << "---------------------------------------\n";
        int choice = Utilities::getIntegerInput("Choose course module action (1-5): ", 1, 5);

        if (choice == 1) {
            Utilities::clearConsole();
            std::cout << "--- Add Course ---\n";
            std::string id = Utilities::getStringInput("Course ID (e.g. CS101): ");
            
            // Check duplicate
            bool dup = false;
            auto curr = courseList.getHead();
            while (curr != nullptr) {
                if (curr->data.getCourseId() == id) {
                    dup = true;
                    break;
                }
                curr = curr->next;
            }
            if (dup) {
                Logger::error("Course ID already exists!");
                Utilities::pressEnterToContinue();
                continue;
            }

            std::string name = Utilities::getStringInput("Course Name: ");
            int credits = Utilities::getIntegerInput("Credits (1-5): ", 1, 5);
            std::cout << "Departments:\n 1. Computer Science\n 2. Electrical\n 3. Mechanical\n 4. Civil\n 5. Physics\n 6. Chemistry\n 7. Mathematics\n";
            Department dept = static_cast<Department>(Utilities::getIntegerInput("Choose Department (1-7): ", 1, 7));
            Semester sem = static_cast<Semester>(Utilities::getIntegerInput("Semester Recommended (1-8): ", 1, 8));

            Course c(id, name, credits, dept, sem);
            courseList.push_back(c);
            prerequisiteGraph.addVertex(id);
            FileManager::saveCourses("data/courses.dat", courseList);
            savePrerequisites("data/prerequisites.dat", prerequisiteGraph);
            Logger::success("Course added to database curriculum!");
            Utilities::pressEnterToContinue();
        } else if (choice == 2) {
            Utilities::clearConsole();
            std::cout << "--- Link Prerequisite Edge ---\n";
            std::string course = Utilities::getStringInput("Target Course ID (e.g. CS201): ");
            std::string prereq = Utilities::getStringInput("Prerequisite Course ID (e.g. CS101): ");

            if (!prerequisiteGraph.hasVertex(course) || !prerequisiteGraph.hasVertex(prereq)) {
                Logger::error("Both courses must exist in database first!");
                Utilities::pressEnterToContinue();
                continue;
            }

            // Add directed dependency: prereq -> course (prereq must be taken first)
            prerequisiteGraph.addEdge(prereq, course);
            
            // Check for cycles instantly to enforce curriculum integrity
            if (prerequisiteGraph.isCyclic()) {
                Logger::error("Circular dependency detected! Removing edge to preserve DAG integrity.");
                prerequisiteGraph.removeEdge(prereq, course);
            } else {
                savePrerequisites("data/prerequisites.dat", prerequisiteGraph);
                Logger::success("Prerequisite edge linked successfully!");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 3) {
            Utilities::clearConsole();
            ReportManager::generateCourseSequenceReport(courseList, prerequisiteGraph);
            Utilities::pressEnterToContinue();
        } else if (choice == 4) {
            Utilities::clearConsole();
            std::string confirm = Utilities::getStringInput("Are you sure you want to clear courses? (yes/no): ");
            if (Utilities::toUpper(confirm) == "YES") {
                courseList.clear();
                prerequisiteGraph.clear();
                FileManager::saveCourses("data/courses.dat", courseList);
                savePrerequisites("data/prerequisites.dat", prerequisiteGraph);
                Logger::success("Curriculum database cleared.");
            }
            Utilities::pressEnterToContinue();
        } else {
            inMenu = false;
        }
    }
}

void handleFinanceMenu(StudentManager& studentMgr, FeeManager& feeMgr, BillingManager& billMgr) {
    bool inMenu = true;
    while (inMenu) {
        Utilities::clearConsole();
        std::cout << "\033[32m--- FINANCE & STUDENT INVOICES ---\033[0m\n";
        std::cout << "  1. Issue Student Tuition Fee Record\n";
        std::cout << "  2. Issue Custom Student Bill Invoice\n";
        std::cout << "  3. Process Fee/Bill Payment\n";
        std::cout << "  4. View Deficit Report (Outstanding Student Fees)\n";
        std::cout << "  5. Back to Dashboard\n";
        std::cout << "----------------------------------\n";
        int choice = Utilities::getIntegerInput("Choose financial action (1-5): ", 1, 5);

        if (choice == 1) {
            Utilities::clearConsole();
            std::cout << "--- Issue Fee Record ---\n";
            std::string id = Utilities::getStringInput("Fee Record ID (e.g. FEE001): ");
            std::string roll = Utilities::getStringInput("Student Roll Number: ");
            int total = Utilities::getIntegerInput("Tuition amount ($): ", 0, 100000);
            std::string due = Utilities::getStringInput("Due date (DD/MM/YYYY): ");

            Fee f(id, roll, total, 0, FeeStatus::UNPAID, due);
            if (feeMgr.addFeeRecord(f, studentMgr)) {
                Logger::success("Tuition fee issued and linked to student account!");
            } else {
                Logger::error("Issue failed. Ensure Student exists and Fee ID is unique.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 2) {
            Utilities::clearConsole();
            std::cout << "--- Issue Custom Bill ---\n";
            std::string id = Utilities::getStringInput("Bill ID (e.g. BIL001): ");
            std::string roll = Utilities::getStringInput("Student Roll Number: ");
            int amt = Utilities::getIntegerInput("Bill amount ($): ", 0, 10000);
            std::cout << "Bill Categories:\n 0. Tuition\n 1. Hostel\n 2. Library\n 3. Mess\n 4. Other\n";
            BillCategory cat = static_cast<BillCategory>(Utilities::getIntegerInput("Choose Category (0-4): ", 0, 4));
            std::string date = Utilities::getStringInput("Issue date (DD/MM/YYYY): ");

            Bill b(id, roll, amt, cat, BillStatus::PENDING, date);
            if (billMgr.addBillRecord(b, studentMgr)) {
                Logger::success("Custom bill issued and linked to student account!");
            } else {
                Logger::error("Issue failed. Ensure Student exists and Bill ID is unique.");
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 3) {
            Utilities::clearConsole();
            std::cout << "--- Process Payment ---\n";
            std::cout << "Payment Type:\n 1. Fee Payment\n 2. Bill Payment\n";
            int type = Utilities::getIntegerInput("Choose Payment type (1-2): ", 1, 2);
            std::string recordId = Utilities::getStringInput("Enter Record ID (Fee ID or Bill ID): ");
            int pay = Utilities::getIntegerInput("Enter payment amount ($): ", 1, 100000);

            if (type == 1) {
                if (feeMgr.recordPayment(recordId, pay, studentMgr)) {
                    Logger::success("Fee payment processed successfully!");
                } else {
                    Logger::error("Payment failed. Check ID validity or overpayment.");
                }
            } else {
                Bill* b = billMgr.getBillById(recordId);
                if (b != nullptr) {
                    if (b->getStatus() == BillStatus::PAID) {
                        Logger::warn("Bill is already fully paid!");
                    } else if (static_cast<uint32_t>(pay) == b->getAmount()) {
                        billMgr.updateBillStatus(recordId, BillStatus::PAID);
                        Logger::success("Bill paid in full successfully!");
                    } else {
                        Logger::error("Exact amount is required for bill payments.");
                    }
                } else {
                    Logger::error("Bill ID not found.");
                }
            }
            Utilities::pressEnterToContinue();
        } else if (choice == 4) {
            Utilities::clearConsole();
            ReportManager::generateOutstandingFeesReport(feeMgr);
            Utilities::pressEnterToContinue();
        } else {
            inMenu = false;
        }
    }
}

void handleAwardMenu(StudentManager& studentMgr, AwardManager& awardMgr) {
    bool inMenu = true;
    while (inMenu) {
        Utilities::clearConsole();
        std::cout << "\033[32m--- ACADEMIC HONORS & SCHOLARSHIPS ---\033[0m\n";
        std::cout << "  1. Add Scholarship / Honors Award to Student\n";
        std::cout << "  2. Back to Dashboard\n";
        std::cout << "--------------------------------------\n";
        int choice = Utilities::getIntegerInput("Choose Action (1-2): ", 1, 2);

        if (choice == 1) {
            Utilities::clearConsole();
            std::cout << "--- Issue Award record ---\n";
            std::string id = Utilities::getStringInput("Award ID (e.g. AWD001): ");
            std::string roll = Utilities::getStringInput("Student Roll Number: ");
            std::string name = Utilities::getStringInput("Award/Scholarship Name: ");
            std::string sponsor = Utilities::getStringInput("Sponsoring Body: ");
            int prize = Utilities::getIntegerInput("Cash Prize amount ($): ", 0, 100000);
            std::string date = Utilities::getStringInput("Date Awarded (DD/MM/YYYY): ");

            Award a(id, roll, name, sponsor, prize, date);
            if (awardMgr.addAwardRecord(a, studentMgr)) {
                Logger::success("Academic Award issued and linked to student profile!");
            } else {
                Logger::error("Issue failed. Ensure Student exists and Award ID is unique.");
            }
            Utilities::pressEnterToContinue();
        } else {
            inMenu = false;
        }
    }
}
