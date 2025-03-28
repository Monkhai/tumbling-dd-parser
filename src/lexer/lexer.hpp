#pragma once

#include <string>
#include <vector>
#include "../token/token.hpp"

using namespace std;

class Lexer
{
public:
    Lexer(const string &input);
    Token nextToken();
    vector<Token> getTokens();

private:
    string input;           // The input source code
    char ch;                // Current byte in source
    size_t currentPosition; // Current position in source
    size_t nextPosition;    // Next position in source

    void read();
    void skipWhitespace();
    Token lexSkill();
};
