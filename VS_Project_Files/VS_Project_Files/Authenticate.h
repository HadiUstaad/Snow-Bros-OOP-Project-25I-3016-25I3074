#pragma once
#include <string>
#include "DatabaseManagement.h"
#include "Password.h"
using namespace std;

// Manages all of the user authentication which means it includes login and registration
class Authenticate
{
private:
    FileManage* database;       // pointer to file but the file isnt owned aggregation
    string username;         // username of the currently logged-in user
    bool isLoggedIn;            // is someone logged in right now

public:

    Authenticate(FileManage* db);
    ~Authenticate();

    // Register a new user if done then output 1 else 0
    bool registerUser(const string& username, const string& password);

    // true on success
    bool loginUser(const string& username, const string& password);

    void logout();

    string getUsername() const;

    bool isloggedin() const;

    // 3- 20 charachter are valid
    bool isValidUsername(const string& username) const;

    //6-8 chars
    bool isValidPassword(const string& password) const;
};