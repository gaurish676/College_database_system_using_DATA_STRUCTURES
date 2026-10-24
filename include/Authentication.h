#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include "../datastructures/HashTable.h"

// Purpose: Manages user authentication, registration, and session state.
// Responsibilities: Handle user login, password hashing/storage, and sessions.
// Data Structure Used: HashTable<std::string, std::string> for credentials store.
// Time Complexity: O(1) average lookup | Space Complexity: O(U) where U is user count
// Dependencies: <string>, "HashTable.h"
class Authentication {
private:
    HashTable<std::string, std::string> credentials;
    std::string loggedInUser;
    bool sessionActive;

    // Purpose: Simple hash function for passwords | Parameters: pass (const std::string&) | Return Value: std::string | Complexity: O(P) password length
    std::string simpleHash(const std::string& pass) const;

public:
    // Purpose: Constructor | Parameters: None | Return Value: None | Complexity: O(1)
    Authentication();

    // Purpose: Register a new user | Parameters: username (const std::string&), password (const std::string&) | Return Value: bool | Complexity: O(1) average
    bool registerUser(const std::string& username, const std::string& password);

    // Purpose: Log in a user | Parameters: username (const std::string&), password (const std::string&) | Return Value: bool | Complexity: O(1) average
    bool login(const std::string& username, const std::string& password);

    // Purpose: Log out current user | Parameters: None | Return Value: None | Complexity: O(1)
    void logout();

    // Purpose: Check if session is active | Parameters: None | Return Value: bool | Complexity: O(1)
    bool isSessionActive() const;

    // Purpose: Get current username | Parameters: None | Return Value: std::string | Complexity: O(1)
    std::string getLoggedInUser() const;

    // Purpose: Save credentials to disk | Parameters: None | Return Value: bool | Complexity: O(U)
    bool saveCredentials();

    // Purpose: Load credentials from disk | Parameters: None | Return Value: bool | Complexity: O(U)
    bool loadCredentials();
};

#endif // AUTHENTICATION_H
