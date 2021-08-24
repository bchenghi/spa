#include "PqlToken.h"

#include <iostream>
#include <string>
#include <utility>

using std::move;
using std::ostream;
using std::string;
using std::to_string;

pql::PqlToken::PqlToken(TokenType type, string token, size_t line_number):
    type_(type), token_(move(token)), line_number_(line_number) { }

pql::TokenType pql::PqlToken::GetTokenType() const
{
    return type_;
}

string pql::PqlToken::GetToken() const
{
    return token_;
}

size_t pql::PqlToken::GetLineNumber() const
{
    return line_number_;
}

ostream& operator<<(ostream& os, const pql::PqlToken& token) {
    static string token_names[] = {
        "kKeyWord",
        "kIdentifier",
        "kSeparator",
        "kConstantInteger",
        "kConstantString",
        "kSuchThat",
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

