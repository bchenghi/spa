#include "PqlToken.h"

#include <string>
#include <utility>

using std::string;

PqlToken::PqlToken(TokenType type, string token, size_t line_number):
    type_(type), token_(std::move(token)), line_number_(line_number) { }

TokenType PqlToken::GetTokenType() const
{
    return this->type_;
}

std::string PqlToken::GetToken() const
{
    return this->token_;
}

size_t PqlToken::GetLineNumber() const
{
    return this->line_number_;
}
