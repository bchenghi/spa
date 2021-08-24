#ifndef GUARD_PQL_TOKEN_H
#define GUARD_PQL_TOKEN_H

#include <string>

enum class TokenType {
    kKeyWord,           // 'Select' | 'Follows' | 'Follows*' | 'Parent' | 'Parent*' | 'Uses' | 'Modifies' | 'pattern' | 'stmt' | 'read' | 'print' | 'call' | 'while' | 'if' | 'assign' | 'variable' | 'constant' | 'procedure'
    kIdentifier,        // variable names
    kSeparator,         // ','
    kConstantInteger,   // statement numbers
    kConstantString,    // '"string literal"'
    kSuchThat,          // 'such that'
    kWildCard,          // '_'
    kOpenBracket,       // '('
    kCloseBracket,      // ')'
    kStatementEnd       // ';'
};

class PqlToken {
public:
    PqlToken(TokenType, std::string, size_t);

    [[nodiscard]] TokenType GetTokenType() const;
    [[nodiscard]] std::string GetToken() const;
    [[nodiscard]] size_t GetLineNumber() const;

private:
    TokenType type_;
    std::string token_;
    size_t line_number_;
};

#endif
