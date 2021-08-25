#include "SimpleToken.h"

#include <string>
#include <utility>

using std::move;
using std::ostream;
using std::string;

simple::SimpleToken::SimpleToken(TokenType type, string token, size_t line_number):
    type_(type), token_(move(token)), line_number_(line_number) { }

simple::TokenType simple::SimpleToken::GetTokenType() const
{
    return type_;
}

string simple::SimpleToken::GetToken() const
{
    return token_;
}

size_t simple::SimpleToken::GetLineNumber() const
{
    return line_number_;
}

bool simple::SimpleToken::operator==(const SimpleToken& token) const
{
    return type_ == token.type_
           && line_number_ == token.line_number_
           && token_ == token.token_;
}

ostream& operator<<(ostream& os, const simple::SimpleToken& token)
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
