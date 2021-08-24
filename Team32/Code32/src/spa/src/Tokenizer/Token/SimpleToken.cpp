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

std::ostream& operator<<(std::ostream& os, const SimpleToken& token)
{
    static std::string token_names[] = {
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
