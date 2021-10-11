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
    static const string token_names[] = {
            /*
             * 'Select'    | 'Follows'   | 'Follows*'  | 'Parent'
             * 'Parent*'   | 'Uses'      | 'Modifies'  | 'Calls'
             * 'Calls*'    | 'Next'      | 'Next*'     | 'Affects'
             * 'Affects*'  | 'pattern'   | 'stmt'      | 'read'
             * 'print'     | 'call'      | 'while'     | 'if'
             * 'assign'    | 'variable'  | 'constant'  | 'procedure'
             * 'such that' | 'with'      | 'prog_line' | 'and'
             */
            "KEY_WORD",
            "ATTRIBUTE_NAME",   // 'procName' | 'varName' | 'value' | 'stmt#'
            "IDENTIFIER",       // variable names
            "SEPARATOR",        // ','
            "CONSTANT_INTEGER", // statement numbers
            "CONSTANT_STRING",  // '"string literal"'
            "WILD_CARD",        // '_'
            "OPEN_BRACKET",     // '('
            "CLOSE_BRACKET",    // ')'
            "STATEMENT_END",    // ';'
            "OPEN_TUPLE",       // '<'
            "CLOSE_TUPLE",      // '>'
            "MEMBER_OPERATOR"   // '.'
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
