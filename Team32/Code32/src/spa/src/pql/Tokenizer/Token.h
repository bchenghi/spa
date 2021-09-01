#ifndef GUARD_PQL_TOKEN_H
#define GUARD_PQL_TOKEN_H

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace pql { class Token; }

std::ostream& operator<<(std::ostream&, const pql::Token&);

namespace pql {
    enum class TokenType {
        kKeyWord,           // 'Select' | 'Follows' | 'Follows*' | 'Parent' | 'Parent*' | 'Uses' | 'Modifies' | 'pattern' | 'stmt' | 'read' | 'print' | 'call' | 'while' | 'if' | 'assign' | 'variable' | 'constant' | 'procedure' | 'such that'
        kIdentifier,        // variable names
        kSeparator,         // ','
        kConstantInteger,   // statement numbers
        kConstantString,    // '"string literal"'
        kWildCard,          // '_'
        kOpenBracket,       // '('
        kCloseBracket,      // ')'
        kStatementEnd       // ';'
    };

    class Token {
    public:
        static inline const std::unordered_map<char, TokenType> token_map = {
                { ',', TokenType::kSeparator },
                { '_', TokenType::kWildCard },
                { '(', TokenType::kOpenBracket },
                { ')', TokenType::kCloseBracket },
                { ';', TokenType::kStatementEnd }
        };
        static inline const std::unordered_set<std::string> keyword_set = {
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

        [[nodiscard]] TokenType GetTokenType() const;
        [[nodiscard]] std::string GetToken() const;
        [[nodiscard]] size_t GetLineNumber() const;

        bool operator==(const Token&) const;

    private:
        TokenType type_;
        std::string token_;
        size_t line_number_;
    };
}

#endif
