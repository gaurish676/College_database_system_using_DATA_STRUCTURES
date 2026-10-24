#include "../include/FileManager.h"
#include "../include/Serializer.h"
#include "../include/Deserializer.h"
#include <fstream>

// Purpose: Save Student records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Student>&) | Return Value: bool | Complexity: O(N)
bool FileManager::saveStudents(const std::string& filepath, DoublyLinkedList<Student>& list) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(list.getSize());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    auto current = list.getHead();
    while (current != nullptr) {
        Serializer::serializeStudent(ofs, current->data);
        current = current->next;
    }
    return true;
}

// Purpose: Load Student records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Student>&) | Return Value: bool | Complexity: O(N)
bool FileManager::loadStudents(const std::string& filepath, DoublyLinkedList<Student>& list) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) {
        return false;
    }
    list.clear();
    uint32_t size = 0;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (uint32_t i = 0; i < size; ++i) {
        list.push_back(Deserializer::deserializeStudent(ifs));
    }
    return true;
}

// Purpose: Save Faculty records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Faculty>&) | Return Value: bool | Complexity: O(N)
bool FileManager::saveFaculty(const std::string& filepath, DoublyLinkedList<Faculty>& list) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(list.getSize());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    auto current = list.getHead();
    while (current != nullptr) {
        Serializer::serializeFaculty(ofs, current->data);
        current = current->next;
    }
    return true;
}

// Purpose: Load Faculty records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Faculty>&) | Return Value: bool | Complexity: O(N)
bool FileManager::loadFaculty(const std::string& filepath, DoublyLinkedList<Faculty>& list) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) {
        return false;
    }
    list.clear();
    uint32_t size = 0;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (uint32_t i = 0; i < size; ++i) {
        list.push_back(Deserializer::deserializeFaculty(ifs));
    }
    return true;
}

// Purpose: Save Course records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Course>&) | Return Value: bool | Complexity: O(N)
bool FileManager::saveCourses(const std::string& filepath, DoublyLinkedList<Course>& list) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(list.getSize());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    auto current = list.getHead();
    while (current != nullptr) {
        Serializer::serializeCourse(ofs, current->data);
        current = current->next;
    }
    return true;
}

// Purpose: Load Course records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Course>&) | Return Value: bool | Complexity: O(N)
bool FileManager::loadCourses(const std::string& filepath, DoublyLinkedList<Course>& list) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) {
        return false;
    }
    list.clear();
    uint32_t size = 0;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (uint32_t i = 0; i < size; ++i) {
        list.push_back(Deserializer::deserializeCourse(ifs));
    }
    return true;
}

// Purpose: Save Fee records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Fee>&) | Return Value: bool | Complexity: O(N)
bool FileManager::saveFees(const std::string& filepath, DoublyLinkedList<Fee>& list) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(list.getSize());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    auto current = list.getHead();
    while (current != nullptr) {
        Serializer::serializeFee(ofs, current->data);
        current = current->next;
    }
    return true;
}

// Purpose: Load Fee records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Fee>&) | Return Value: bool | Complexity: O(N)
bool FileManager::loadFees(const std::string& filepath, DoublyLinkedList<Fee>& list) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) {
        return false;
    }
    list.clear();
    uint32_t size = 0;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (uint32_t i = 0; i < size; ++i) {
        list.push_back(Deserializer::deserializeFee(ifs));
    }
    return true;
}

// Purpose: Save Award records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Award>&) | Return Value: bool | Complexity: O(N)
bool FileManager::saveAwards(const std::string& filepath, DoublyLinkedList<Award>& list) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(list.getSize());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    auto current = list.getHead();
    while (current != nullptr) {
        Serializer::serializeAward(ofs, current->data);
        current = current->next;
    }
    return true;
}

// Purpose: Load Award records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Award>&) | Return Value: bool | Complexity: O(N)
bool FileManager::loadAwards(const std::string& filepath, DoublyLinkedList<Award>& list) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) {
        return false;
    }
    list.clear();
    uint32_t size = 0;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (uint32_t i = 0; i < size; ++i) {
        list.push_back(Deserializer::deserializeAward(ifs));
    }
    return true;
}

// Purpose: Save Bill records to binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Bill>&) | Return Value: bool | Complexity: O(N)
bool FileManager::saveBills(const std::string& filepath, DoublyLinkedList<Bill>& list) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(list.getSize());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    auto current = list.getHead();
    while (current != nullptr) {
        Serializer::serializeBill(ofs, current->data);
        current = current->next;
    }
    return true;
}

// Purpose: Load Bill records from binary file | Parameters: filepath (const std::string&), list (DoublyLinkedList<Bill>&) | Return Value: bool | Complexity: O(N)
bool FileManager::loadBills(const std::string& filepath, DoublyLinkedList<Bill>& list) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) {
        return false;
    }
    list.clear();
    uint32_t size = 0;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (uint32_t i = 0; i < size; ++i) {
        list.push_back(Deserializer::deserializeBill(ifs));
    }
    return true;
}
