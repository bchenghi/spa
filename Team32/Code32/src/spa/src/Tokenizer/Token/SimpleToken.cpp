#include "SimpleToken.h"

#include <string>
#include <utility>

using std::string;

SimpleToken::SimpleToken(TokenType type, string token, size_t line_number):
    type_(type), token_(std::move(token)), line_number_(line_number) { }

TokenType SimpleToken::GetTokenType() const
{
    return this->type_;
}

string SimpleToken::GetToken() const
{
    return this->token_;
}

size_t SimpleToken::GetLineNumber() const
{
    return this->line_number_;
}
