#include "Token.h"

#include <string>
#include <utility>

using std::move;
using std::ostream;
using std::string;

simple::Token::Token() { }

simple::Token::Token(TokenType type, string token, size_t line_number):
        type(type), token(move(token)), lineNumber(line_number) { }

simple::TokenType simple::Token::getTokenType() const
{
    return type;
}

string simple::Token::getToken() const
{
    return token;
}

size_t simple::Token::getLineNumber() const
{
    return lineNumber;
}

bool simple::Token::operator==(const Token& other) const
{
    return type == other.type
           && lineNumber == other.lineNumber
           && token == other.token;
}

simple::Token& simple::Token::operator=(const Token& rhs)
{
    if (&rhs != this) {
        this->type = rhs.type;
        this->token = rhs.token;
        this->lineNumber = rhs.lineNumber;
    }

    return *this;
}

void simple::Token::setTokenType(TokenType newType)
{
    this->type = newType;
}

ostream& operator<<(ostream& os, const simple::Token& token)
{
    static const string token_names[] = {
            /*
             * procedure | variable names | 'procedure' | 'read' | 'print' | 'call' | 'while' | 'if' | 'then' | 'else'
             */
            "NAME",
            "CONSTANT",             // constants (we only have integer constants in SIMPLE)
            "ASSIGNMENT",           // '='
            "OPEN_BRACKET",         // '('
            "CLOSE_BRACKET",        // ')'
            "OPEN_BRACE",           // '{'
            "CLOSE_BRACE",          // '}'
            "NEGATE",               // '!'
            "CONDITION_OPERATOR",   // '&&' | '||'
            "OPERATOR",             // '+' | '-' | '/' | '*' | '%'
            "RELATIONAL_OPERATOR",  // '>' | '>=' | '<' | '<=' | '==' | '!='
            "STATEMENT_END"         // ';'
    };

    os << "{ token: \""
        << token.token
        << "\", type: "
        << token_names[(int) token.type]
        << ", line_number: "
        << std::to_string(token.lineNumber)
        << " }";

    return os;
}
