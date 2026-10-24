#include "../include/Authentication.h"
#include "../include/Serializer.h"
#include "../include/Deserializer.h"
#include <fstream>
#include <sstream>

// Purpose: Simple hash function for passwords | Parameters: pass (const std::string&) | Return Value: std::string | Complexity: O(P)
std::string Authentication::simpleHash(const std::string& pass) const {
    size_t h = 5381;
    for (char c : pass) {
        h = ((h << 5) + h) + c;
    }
    // Convert to hex string for output uniformity
    std::stringstream ss;
    ss << std::hex << h;
    return ss.str();
}

// Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
Authentication::Authentication() : credentials(16), loggedInUser(""), sessionActive(false) {
    // If credentials file doesn't exist or is empty, register a default admin user
    loadCredentials();
    std::string adminPass;
    if (!credentials.search("admin", adminPass)) {
        registerUser("admin", "admin123");
    }
}

// Purpose: Register a new user | Parameters: username (const std::string&), password (const std::string&) | Return Value: bool | Complexity: O(1) average
bool Authentication::registerUser(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) return false;
    std::string existingPass;
    if (credentials.search(username, existingPass)) {
        return false; // Already exists
    }
    credentials.insert(username, simpleHash(password));
    saveCredentials();
    return true;
}

// Purpose: Log in a user | Parameters: username (const std::string&), password (const std::string&) | Return Value: bool | Complexity: O(1) average
bool Authentication::login(const std::string& username, const std::string& password) {
    std::string hashedPass;
    if (credentials.search(username, hashedPass)) {
        if (hashedPass == simpleHash(password)) {
            loggedInUser = username;
            sessionActive = true;
            return true;
        }
    }
    return false;
}

// Purpose: Log out current user | Parameters: None | Return Value: None | Complexity: O(1)
void Authentication::logout() {
    loggedInUser = "";
    sessionActive = false;
}

// Purpose: Check if session is active | Parameters: None | Return Value: bool | Complexity: O(1)
bool Authentication::isSessionActive() const {
    return sessionActive;
}

// Purpose: Get current username | Parameters: None | Return Value: std::string | Complexity: O(1)
std::string Authentication::getLoggedInUser() const {
    return loggedInUser;
}

// Purpose: Save credentials to disk | Parameters: None | Return Value: bool | Complexity: O(U)
bool Authentication::saveCredentials() {
    std::ofstream ofs("data/users.dat", std::ios::binary);
    if (!ofs) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(credentials.getSize());
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    const auto* table = credentials.getTable();
    size_t capacity = credentials.getCapacity();
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].state == EntryState::ACTIVE) {
            Serializer::writeString(ofs, table[i].key);
            Serializer::writeString(ofs, table[i].value);
        }
    }
    return true;
}

// Purpose: Load credentials from disk | Parameters: None | Return Value: bool | Complexity: O(U)
bool Authentication::loadCredentials() {
    std::ifstream ifs("data/users.dat", std::ios::binary);
    if (!ifs) {
        return false;
    }
    credentials.clear();
    uint32_t size = 0;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (uint32_t i = 0; i < size; ++i) {
        std::string username = Deserializer::readString(ifs);
        std::string hashedPass = Deserializer::readString(ifs);
        credentials.insert(username, hashedPass);
    }
    return true;
}
