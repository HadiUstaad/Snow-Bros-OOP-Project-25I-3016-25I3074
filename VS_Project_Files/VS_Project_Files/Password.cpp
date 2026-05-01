#include "Password.h"
using namespace std;

// converts to oct to be unrecignozed
string Password::hashPassword(const string& password)
{
    unsigned int hash = simpleHash(password);
    string result = "";
    for (int i = 0; i < 12 ; i++)
    {
        int remainder = hash % 8;

        char c = remainder + '0';
        result = c + result;    // the new number is added at the left side of string

        hash = hash / 8;
    }

    return result;
   
}


bool Password::verifyPassword(const string& password, const string& stored)
{
    return hashPassword(password) == stored;
}

// prime number weights applied so that each password has unique answer making it hashed
//unsigned so no negative num
unsigned int Password::simpleHash( const string& input)
{
    unsigned int hash = 0;
    unsigned int prime = 19;    // prime number has no divisible factors

    for (int i = 0; i < input.size(); i++)
    {
        // each new hash has a larger weight making the number un predictable
        hash = hash * prime + (unsigned int)input[i];
    }

    return hash;
}


