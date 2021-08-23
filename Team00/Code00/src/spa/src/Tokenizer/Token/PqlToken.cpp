#include "PqlToken.h"

#include <string>

using std::string;

PqlToken::PqlToken(TokenType type, string token, int line_number):
    type_(type), token_(token), line_number_(line_number) { }

TokenType PqlToken::GetTokenType() const {
    return this->type_;
}

std::string PqlToken::GetToken() const {
    return this->token_;
}

int PqlToken::GetLineNumber() const {
    return this->line_number_;
}
