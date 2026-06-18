#pragma once
#include <string>

using namespace std;

// makes password unreadavle normally
class Password
{
public:
    // hashes password string and returns hash as string
    static string hashPassword(const string& password);

    // Verifies password 
    static bool verifyPassword(const string& password, const string& stored);

    // string to unsigned int
    static unsigned int simpleHash(const string& input);

  
};