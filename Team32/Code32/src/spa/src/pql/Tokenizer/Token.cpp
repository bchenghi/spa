#include "Token.h"

#include <iostream>
#include <string>
#include <utility>

using std::move;
using std::ostream;
using std::string;
using std::to_string;

pql::Token::Token(TokenType type, string token, size_t line_number)
        : type(type), token(move(token)), lineNumber(line_number) { }

pql::TokenType pql::Token::getTokenType() const
{
    return type;
}

string pql::Token::getToken() const
{
    return token;
}

size_t pql::Token::getLineNumber() const
{
    return lineNumber;
}

bool pql::Token::operator==(const Token& other) const
{
    return type == other.type
           && lineNumber == other.lineNumber
           && token == other.token;
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
        << token.token
        << "\", type: "
        << token_names[(int) token.type]
        << ", line_number: "
        << to_string(token.lineNumber)
        << " }";

    return os;
}
