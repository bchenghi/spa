#include "Token.h"

#include <iostream>
#include <string>
#include <utility>

using std::move;
using std::ostream;
using std::string;
using std::to_string;

pql::Token::Token(TokenType type, string token, size_t line_number):
    type_(type), token_(move(token)), line_number_(line_number) { }

pql::TokenType pql::Token::GetTokenType() const
{
    return type_;
}

string pql::Token::GetToken() const
{
    return token_;
}

size_t pql::Token::GetLineNumber() const
{
    return line_number_;
}

bool pql::Token::operator==(const Token& token) const
{
    return type_ == token.type_
        && line_number_ == token.line_number_
        && token_ == token.token_;
}

ostream& operator<<(ostream& os, const pql::Token& token)
{
    static string token_names[] = {
        "kKeyWord",
        "kIdentifier",
        "kSeparator",
        "kConstantInteger",
        "kConstantString",
        "kWildCard",
        "kOpenBracket",
        "kCloseBracket",
        "kStatementEnd"
    };

    os << "{ token: \""
        << token.token_
        << "\", type: "
        << token_names[(int) token.type_]
        << ", line_number: "
        << to_string(token.line_number_)
        << " }";

    return os;
}
