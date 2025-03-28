#include "lexer.hpp"
#include <iostream>
#include <token/token_type.hpp>

Lexer::Lexer(const string &input)
{
    this->input = input;
    this->currentPosition = 0;
    this->nextPosition = 0;
    this->read();
}

void Lexer::read()
{
    if (this->nextPosition >= this->input.length())
    {
        this->ch = '\0';
    }
    else
    {
        this->ch = this->input[this->nextPosition];
    }
    this->currentPosition = this->nextPosition;
    this->nextPosition++;
}

Token Lexer::nextToken()
{
    this->skipWhitespace();
    Token token;

    switch (this->ch)
    {
    case '(':
        // todo: check if it is RO or just skill surrounding
        token = Token(TokenType::RO);
        break;
    //----------------------------------------
    case 'f':
        token = Token(TokenType::FLIC);
        break;
    //----------------------------------------
    case '^':
        token = Token(TokenType::WHIP);
        break;
    //----------------------------------------
    case '.':
        token = Token(TokenType::ILLEGAL);
        break;
    //----------------------------------------
    case '0':
        token = Token(TokenType::END_OF_FILE);
        break;
    //----------------------------------------
    default:
        token = this->lexSkill();
    }

    this->read();
    return token;
}

Token Lexer::lexSkill()
{
    string skill;
    skill += this->ch;
    bool sawShape = false;
    bool sawDirection = false;
    char prev = this->ch;
    while (true)
    {
        if (this->ch == '\0')
        {
            break;
        }

        if (TokenType::isIllegal(this->ch))
        {
            skill = TokenType::ILLEGAL;
            break;
        }

        if (TokenType::isTransitionSkill(this->ch))
        {
            break;
        }

        this->read();
        if (TokenType::isShape(this->ch))
        {
            if (sawShape)
            {
                skill = TokenType::ILLEGAL;
                break;
            }
            sawShape = true;
            skill += this->ch;
            if (prev == *TokenType::DIRECTION_INDICATOR)
            {
                break;
            }
            prev = this->ch;
        }
        else if (this->ch == *TokenType::DIRECTION_INDICATOR)
        {
            if (sawDirection)
            {
                skill = TokenType::ILLEGAL;
                break;
            }
            sawDirection = true;
            skill += this->ch;
            if (TokenType::isShape(prev))
            {
                break;
            }
            prev = this->ch;
        }
        else
        {
            skill += this->ch;
        }
    }
    return Token(skill);
}

void Lexer::skipWhitespace()
{
    while (this->ch == ' ' || this->ch == '\t' || this->ch == '\n')
    {
        this->read();
    }
}

vector<Token> Lexer::getTokens()
{
    vector<Token> tokens;
    while (this->ch != '\0')
    {
        tokens.push_back(this->nextToken());
    }

    return tokens;
}