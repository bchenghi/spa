#ifndef GUARD_SIMPLE_TOKEN_H
#define GUARD_SIMPLE_TOKEN_H

#include <string>

enum class TokenType {
    kKeyWord,               // 'procedure' | 'read' | 'print' | 'call' | 'while' | 'if' | 'then' | 'else'
    kIdentifier,            // procedure | variable names
    kConstant,              // constants (we only have integer constants in SIMPLE)
    kOpenBracket,           // '('
    kCloseBracket,          // ')'
    kOpenBrace,             // '{'
    kCloseBrace,            // '}'
    kNegate,                // '!'
    kConditionOperator,     // '&&' | '||'
    kOperator,              // '+' | '-' | '/' | '*' | '%'
    kRelationalOperator,    // '>' | '>=' | '<' | '<=' | '==' | '!='
    kStatementEnd           // ';'
};

class SimpleToken {
public:
    SimpleToken(TokenType, std::string, size_t);

    [[nodiscard]] TokenType GetTokenType() const;
    [[nodiscard]] std::string GetToken() const;
    [[nodiscard]] size_t GetLineNumber() const;

private:
    TokenType type_;
    std::string token_;
    size_t line_number_;
};

#endif
