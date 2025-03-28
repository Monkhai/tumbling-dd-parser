#include "parser.hpp"
#include <iostream>
#include "token/token_type.hpp"

Parser::Parser(const string &input) : lexer(input)
{
    this->errors = vector<string>();
    this->tokens = this->lexer.getTokens();
}

string Parser::parse()
{
    string pass = "";
    for (Token token : this->tokens)
    {
        if (TokenType::isTransitionSkill(token.token))
        {
            pass += this->processTransitionSkill(token);
            continue;
        }
        else
        {
            pass += this->processSkill(token);
        }
    }
    return pass;
}

string Parser::processTransitionSkill(const Token &token)
{
    auto skill = TokenType::SKILL_STRINGS.find(token.token);
    if (skill != TokenType::SKILL_STRINGS.end())
    {
        return skill->second;
    }
    else
    {
        this->addError("Invalid transition skill: " + token.token);
        return "";
    }
}

string Parser::processSkill(const Token &token)
{
    // here we need to parse the skill char by char.
    int i = 0;
    bool readyForShape = false;
    string skillString = "";
    while (i < token.token.length())
    {
        char ch = token.token[i];
        if (TokenType::isShape(ch))
        {
            if (readyForShape)
            {
                readyForShape = false;
                auto skill = TokenType::SKILL_STRINGS.find(string(1, ch));
                if (skill != TokenType::SKILL_STRINGS.end())
                {
                    skillString += skill->second;
                }
            }
            else
            {
                this->addError("Invalid shape: " + string(1, ch));
                return "";
            }
        }
        else
        {
        }

        i++;
    }
}

void Parser::addError(const string &error)
{
    this->errors.push_back(error);
}