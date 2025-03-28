#pragma once

#include "lexer/lexer.hpp"

using namespace std;

class Parser
{
public:
    Parser(const string &input);
    string parse();

private:
    Lexer lexer;
    vector<Token> tokens;
    vector<string> errors;

    void addError(const string &error);
    string processTransitionSkill(const Token &token);
    string processSkill(const Token &token);
};
