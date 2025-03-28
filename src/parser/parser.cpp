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
        return skill->second + " ";
    }
    else
    {
        this->addError("Invalid transition skill: " + token.token);
        return "";
    }
}

string Parser::processSkill(const Token &token)
{
    string skillString = "";

    // 0 means back, 1 means front
    int direction = 0;

    // iterate and find the direction indicator. if before shape or direction indicator, it's front. if after, it's back.
    for (int i = 0; i < token.token.length(); i++)
    {
        if (token.token[i] == *TokenType::DIRECTION_INDICATOR)
        {
            if (TokenType::isShape(token.token[i - 1]))
            {
                direction = 0;
            }
            else if (TokenType::isShape(token.token[i + 1]))
            {
                direction = 1;
            }
            else
            {
                this->addError("invalid direction indicator: " + token.token);
                return "";
            }
        }
    }
    // count chars before shape or direction indicator
    int flipCount = 0;
    while (token.token[flipCount] != *TokenType::DIRECTION_INDICATOR && token.token[flipCount] != *TokenType::ILLEGAL && !TokenType::isShape(token.token[flipCount]))
    {
        flipCount++;
    }

    if (flipCount == 0)
    {
        this->addError("no flips found in skill: " + token.token);
        return "";
    }

    string flip = token.token.substr(0, flipCount);
    int i = 0;

    bool anyTwists = false;
    while (i < flip.length())
    {
        char ch = flip[i];
        if (isdigit(ch))
        {
            anyTwists = true;
        }
        i++;
    }

    if (!anyTwists)
    {
        auto flipsString = TokenType::FLIP_STRINGS.find(to_string(flipCount));
        if (flipsString == TokenType::FLIP_STRINGS.end())
        {
            this->addError("invalid flip number: " + flip);
            return "";
        }

        skillString += flipsString->second;
    }
    else
    {
        bool allTwists = true;
        for (int i = 0; i < flip.length(); i++)
        {
            char ch = flip[i];
            if (!isdigit(ch))
            {
                allTwists = false;
            }
        }

        if (allTwists)
        {
            for (int i = 0; i < flip.length(); i++)
            {
                char ch = flip[i];
                auto twistsString = TokenType::TWIST_STRINGS.find(string(1, ch));
                if (twistsString == TokenType::TWIST_STRINGS.end())
                {
                    this->addError("invalid twist number: " + flip);
                    return "";
                }
                if (i != 0)
                {
                    skillString += "-";
                }
                skillString += twistsString->second;
            }
        }
        else
        {
            for (int i = 0; i < flip.length(); i++)
            {
                char ch = flip[i];
                if (ch == '-')
                {
                    bool hasMoreTwists = false;
                    for (int j = i + 1; j < flip.length(); j++)
                    {
                        if (isdigit(flip[j]))
                        {
                            hasMoreTwists = true;
                        }
                    }

                    if (!hasMoreTwists && flipCount > 2)
                    {
                        {
                            auto flipString = TokenType::FLIP_STRINGS.find(to_string(flipCount));
                            if (flipString == TokenType::FLIP_STRINGS.end())
                            {
                                this->addError("invalid flip number: " + flip);
                                return "";
                            }

                            if (i != 0)
                            {
                                skillString += " ";
                            }

                            skillString += flipString->second;
                        }
                        break;
                    }
                    else if (i == flip.length() - 1)
                    {
                        continue;
                    }

                    auto directionString = TokenType::DIRECTION_STRINGS.find(direction);
                    if (directionString == TokenType::DIRECTION_STRINGS.end())
                    {
                        this->addError("invalid direction: " + directionString->second);
                        return "";
                    }

                    if (i != 0)
                    {
                        skillString += " ";
                    }

                    skillString += directionString->second;

                    if (i == 0)
                    {
                        skillString += "-in";
                    }
                    else if (i == flip.length() - 1)
                    {
                        skillString += "-out";
                    }
                    continue;
                }
                else
                {
                    auto twistString = TokenType::TWIST_STRINGS.find(string(1, ch));
                    if (twistString == TokenType::TWIST_STRINGS.end())
                    {
                        this->addError("invalid twist: " + twistString->second);
                        return "";
                    }

                    if (i != 0)
                    {
                        skillString += " ";
                    }

                    skillString += twistString->second;

                    if (i == flip.length() - 1)
                    {
                        skillString += "-out";
                    }
                    else if (i == 0)
                    {
                        skillString += "-in";
                    }
                }
            }
        }
    }

    // add shape
    auto shapeString = TokenType::SHAPE_STRINGS.find(string(1, token.token[flip.length()]));
    if (shapeString == TokenType::SHAPE_STRINGS.end())
    {
        this->addError("invalid shape: " + shapeString->second);
        return "";
    }
    skillString += " " + shapeString->second;

    return skillString;
}

void Parser::addError(const string &error)
{
    this->errors.push_back(error);
}

vector<string> Parser::getErrors()
{
    return this->errors;
}