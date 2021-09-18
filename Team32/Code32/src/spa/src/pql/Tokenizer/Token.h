#ifndef GUARD_PQL_TOKEN_H
#define GUARD_PQL_TOKEN_H

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace pql { class Token; }

std::ostream& operator<<(std::ostream&, const pql::Token&);

namespace pql {
    enum class TokenType {
        KEY_WORD,           // 'Select' | 'Follows' | 'Follows*' | 'Parent' | 'Parent*' | 'Uses' | 'Modifies' | 'pattern' | 'stmt' | 'read' | 'print' | 'call' | 'while' | 'if' | 'assign' | 'variable' | 'constant' | 'procedure' | 'such that'
        IDENTIFIER,         // variable names
        SEPARATOR,          // ','
        CONSTANT_INTEGER,   // statement numbers
        CONSTANT_STRING,    // '"string literal"'
        WILD_CARD,          // '_'
        OPEN_BRACKET,       // '('
        CLOSE_BRACKET,      // ')'
        STATEMENT_END       // ';'
    };

    class Token {
    public:
        static inline const std::unordered_map<char, TokenType> tokenMap = {
                { ',', TokenType::SEPARATOR },
                { '_', TokenType::WILD_CARD },
                { '(', TokenType::OPEN_BRACKET },
                { ')', TokenType::CLOSE_BRACKET },
                { ';', TokenType::STATEMENT_END }
        };
        static inline const std::unordered_set<std::string> keywordSet = {
                "Select",
                "Follows",
                "Parent",
                "Uses",
                "Modifies",
                "pattern",
                "stmt",
                "read",
                "print",
                "call",
                "while",
                "if",
                "assign",
                "variable",
                "constant",
                "procedure"
        };

        friend std::ostream& ::operator<<(std::ostream&, const Token&);

        Token(TokenType, std::string, size_t);

        [[nodiscard]] TokenType getTokenType() const;
        [[nodiscard]] std::string getToken() const;
        [[nodiscard]] size_t getLineNumber() const;

        bool operator==(const Token&) const;

    private:
        TokenType type;
        std::string token;
        size_t lineNumber;
    };
}

#endif
