#ifndef GUARD_SIMPLE_TOKEN_H
#define GUARD_SIMPLE_TOKEN_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace simple { class SimpleToken; }

std::ostream& operator<<(std::ostream&, const simple::SimpleToken&);

namespace simple {
    enum class TokenType {
        kKeyWord,               // 'procedure' | 'read' | 'print' | 'call' | 'while' | 'if' | 'then' | 'else'
        kIdentifier,            // procedure | variable names
        kConstant,              // constants (we only have integer constants in SIMPLE)
        kAssignment,            // '='
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
        static inline const std::unordered_map<char, TokenType> token_map = {
                { '!', TokenType::kNegate },
                { '{', TokenType::kOpenBrace },
                { '}', TokenType::kCloseBrace },
                { '(', TokenType::kOpenBracket },
                { ')', TokenType::kCloseBracket },
                { '+', TokenType::kOperator },
                { '-', TokenType::kOperator },
                { '/', TokenType::kOperator },
                { '*', TokenType::kOperator },
                { '%', TokenType::kOperator },
                { ';', TokenType::kStatementEnd },
                { '=', TokenType::kAssignment },
                { '<', TokenType::kRelationalOperator },
                { '>', TokenType::kRelationalOperator }
        };
        static inline const std::unordered_set<std::string> keyword_set = {
                "procedure",
                "read",
                "print",
                "call",
                "while",
                "if",
                "then",
                "else"
        };

        friend std::ostream& ::operator<<(std::ostream&, const SimpleToken&);

        SimpleToken(TokenType, std::string, size_t);

        [[nodiscard]] TokenType GetTokenType() const;
        [[nodiscard]] std::string GetToken() const;
        [[nodiscard]] size_t GetLineNumber() const;

        bool operator==(const SimpleToken&) const;

    private:
        TokenType type_;
        std::string token_;
        size_t line_number_;
    };
}

#endif
