#include "Authenticate.h"
using namespace std;

AuthManager::AuthManager(FileManage* db)
{
    database = db;
    isLoggedIn = false;
    currentUser = "";
}

AuthManager::~AuthManager()
{
    // database is not owned — do not delete
}

bool AuthManager::registerUser(const string& username, const string& password)
{
    if (!isValidUsername(username))
        return false;

    if (!isValidPassword(password))
        return false;

    if (database->userExists(username))
        return false;

    string hashedPassword = Password::hashPassword(password);
    return database->addUser(username, hashedPassword);
}

bool AuthManager::loginUser(const string& username, const string& password)
{
    string hashedPassword = Password::hashPassword(password);

    if (!database->verifyPassword(username, hashedPassword))
        return false;

    currentUser = username;
    isLoggedIn = true;
    return true;
}

void AuthManager::logout()
{
    isLoggedIn = false;
    currentUser = "";
}

string AuthManager::getCurrentUser() const
{
    return currentUser;
}

bool AuthManager::isUserLoggedIn() const
{
    return isLoggedIn;
}

bool AuthManager::isValidUsername(const string& username) const
{
    int len = (int)username.size();
    if (len < 3 || len > 20)
        return false;

    for (int i = 0; i < len; i++)
    {
        char c = username[i];
        bool valid = (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            (c == '_');
        if (!valid)
            return false;
    }

    return true;
}

bool AuthManager::isValidPassword(const string& password) const
{
    return (int)password.size() >= 6;
}