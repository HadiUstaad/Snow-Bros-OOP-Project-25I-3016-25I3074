#pragma once
#include <string>
#include "DatabaseManagement.h"
#include "Password.h"
using namespace std;

// Manages user authentication: login and registration
class AuthManager
{
private:
    FileManage* database;       // pointer to file database (not owned)
    string currentUser;         // username of the currently logged-in user
    bool isLoggedIn;            // is someone logged in right now

public:
    // Constructor takes database reference
    AuthManager(FileManage* db);

    // Destructor (does not delete database)
    ~AuthManager();

    // Register a new user — returns true on success
    bool registerUser(const string& username, const string& password);

    // Login an existing user — returns true on success
    bool loginUser(const string& username, const string& password);

    // Logout current user
    void logout();

    // Get the username of the logged-in user
    string getCurrentUser() const;

    // Returns true if someone is currently logged in
    bool isUserLoggedIn() const;

private:
    // Validates username: 3-20 alphanumeric/_  characters
    bool isValidUsername(const string& username) const;

    // Validates password: minimum 6 characters
    bool isValidPassword(const string& password) const;
};