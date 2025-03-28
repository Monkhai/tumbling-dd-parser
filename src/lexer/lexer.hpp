#pragma once

#include <string>
#include <vector>
#include "../token/token.hpp"

using namespace std;

class Lexer
{
public:
    // Constructor
    Lexer(const string &input);
    Token nextToken();

private:
    // members
    string input;           // The input source code
    char ch;                // Current byte in source
    size_t currentPosition; // Current position in source
    size_t nextPosition;    // Next position in source

    // methods
    void read();
    void skipWhitespace();
    Token lexSkill();
};
