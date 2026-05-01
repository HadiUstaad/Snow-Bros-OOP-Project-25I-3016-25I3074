#include "Authenticate.h"
using namespace std;

Authenticate::Authenticate(FileManage* db)
{
    database = db;
    isLoggedIn = false;
    username = "";
}

Authenticate::~Authenticate()
{
    // database is not owned so it will not be deleted
}

bool Authenticate::registerUser(const string& username, const string& password)
{
    if (!isValidUsername(username))
    {
        return false;
    }

    if (!isValidPassword(password))
    {
        return false;
    }

    if (database->userExists(username))
    {
        return false;
    }

    // if user is really a new user and passes all checks then the password is hased and a new user is added
    string hash = Password::hashPassword(password);
    return database->addUser(username, hash);
}

bool Authenticate::loginUser(const string& username, const string& password)
{
    // we store the incoming password and convert it into hash.
    // then compare the hash with the og  password
    string hash = Password::hashPassword(password);

    if (!database->verifyPassword(username, hash))
    {
        return false;
    }

    this->username = username;
    isLoggedIn = true;
    return true;
}

void Authenticate::logout()
{
    isLoggedIn = false;
    username = "";
}

string Authenticate::getUsername() const
{
    return username;
}

bool Authenticate::isloggedin() const
{
    return isLoggedIn;
}

bool Authenticate::isValidUsername(const string& username) const
{
    int len = username.size();
    if (len < 3 || len > 20) // length check
    {
        return false;
    }

    for (int i = 0; i < len; i++) // valid charachter check
    {
        char c = username[i];
        
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || (c == '_')))
        {
            return false;
        }

    }
    return true;
}

bool Authenticate::isValidPassword(const string& password) const
{
    if (password.size() >= 6 && password.size() <= 8)
    {
        return 1;
    }
    return 0;
}