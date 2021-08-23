#include "SimpleToken.h"

#include <string>

using std::string;

SimpleToken::SimpleToken(TokenType type, string token, int line_number):
    type_(type), token_(token), line_number_(line_number) { }

TokenType SimpleToken::GetTokenType() const
{
    return this->type_;
}

string SimpleToken::GetToken() const
{
    return this->token_;
}

int SimpleToken::GetLineNumber() const
{
    return this->line_number_;
}
