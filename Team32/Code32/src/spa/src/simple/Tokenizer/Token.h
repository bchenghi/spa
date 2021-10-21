#ifndef GUARD_SIMPLE_TOKEN_H
#define GUARD_SIMPLE_TOKEN_H

#include <iostream>
#include <string>

namespace simple { class Token; }

std::ostream& operator<<(std::ostream&, const simple::Token&);

namespace simple {
    enum class TokenType {
        KEY_WORD,               // 'procedure' | 'read' | 'print' | 'call' | 'while' | 'if' | 'then' | 'else'
        IDENTIFIER,             // procedure | variable names
        CONSTANT,               // constants (we only have integer constants in SIMPLE)
        ASSIGNMENT,             // '='
        OPEN_BRACKET,           // '('
        CLOSE_BRACKET,          // ')'
        OPEN_BRACE,             // '{'
        CLOSE_BRACE,            // '}'
        NEGATE,                 // '!'
        CONDITION_OPERATOR,     // '&&' | '||'
        OPERATOR,               // '+' | '-' | '/' | '*' | '%'
        RELATIONAL_OPERATOR,    // '>' | '>=' | '<' | '<=' | '==' | '!='
        STATEMENT_END           // ';'
    };

    class Token {
    public:
        friend std::ostream& ::operator<<(std::ostream&, const Token&);

        Token();
        Token(TokenType, std::string, size_t);

        [[nodiscard]] TokenType getTokenType() const;
        [[nodiscard]] std::string getToken() const;
        [[nodiscard]] size_t getLineNumber() const;
        void setTokenType(TokenType);

        bool operator==(const Token&) const;
        Token& operator=(const Token&);

    private:
        TokenType type;
        std::string token;
        size_t lineNumber;
    };
}

#endif
