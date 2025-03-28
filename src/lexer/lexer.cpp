#include "lexer.hpp"

Lexer::Lexer(const string &input)
{
    this->input = input;
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

    string t = "";
    Token token = Token(t);
    return token;
}

void Lexer::skipWhitespace()
{
    while (this->ch == ' ' || this->ch == '\t' || this->ch == '\n')
    {
        this->read();
    }
}
