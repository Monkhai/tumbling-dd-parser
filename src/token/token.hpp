#pragma once

#include <string>

using namespace std;

class Token
{
public:
    // constructors
    Token() : token("") {} // Default constructor
    Token(string token);   // Existing constructor

    string token;
};