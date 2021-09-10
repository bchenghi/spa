#include "Token.h"

#include <string>
#include <utility>

using std::move;
using std::ostream;
using std::string;

simple::Token::Token() {  }

simple::Token::Token(TokenType type, string token, size_t line_number):
    type_(type), token_(move(token)), line_number_(line_number) { }

simple::TokenType simple::Token::GetTokenType() const
{
    return type_;
}

string simple::Token::GetToken() const
{
    return token_;
}

size_t simple::Token::GetLineNumber() const
{
    return line_number_;
}

bool simple::Token::operator==(const Token& token) const
{
    return type_ == token.type_
           && line_number_ == token.line_number_
           && token_ == token.token_;
}

simple::Token& simple::Token::operator=(const Token& rhs)
{
    if (&rhs != this) {
        this->type_ = rhs.type_;
        this->token_ = rhs.token_;
        this->line_number_ = rhs.line_number_;
    }

    return *this;
}

ostream& operator<<(ostream& os, const simple::Token& token)
{
    static string token_names[] = {
        "kKeyWord",
        "kIdentifier",
        "kConstant",
        "kAssignment",
        "kOpenBracket",
        "kCloseBracket",
        "kOpenBrace",
        "kCloseBrace",
        "kNegate",
        "kConditionOperator",
        "kOperator",
        "kRelationalOperator",
        "kStatementEnd"
    };

    os << "{ token: \""
        << token.token_
        << "\", type: "
        << token_names[(int) token.type_]
        << ", line_number: "
        << std::to_string(token.line_number_)
        << " }";

    return os;
}
