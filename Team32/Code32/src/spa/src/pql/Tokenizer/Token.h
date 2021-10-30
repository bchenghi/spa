#ifndef GUARD_PQL_TOKEN_H
#define GUARD_PQL_TOKEN_H

#include <string>

namespace pql { class Token; }

std::ostream& operator<<(std::ostream&, const pql::Token&);

namespace pql {
    enum class TokenType {
        /*
         * 'Select'      | 'Follows'     | 'Follows*'    | 'Parent'
         * 'Parent*'     | 'Uses'        | 'Modifies'    | 'Calls'
         * 'Calls*'      | 'Next'        | 'Next*'       | 'NextBip'
         * 'NextBip*'    | 'Affects'     | 'Affects*'    | 'AffectsBip'
         * 'AffectsBip*' | 'pattern'     | 'stmt'        | 'read'
         * 'print'       | 'call'        | 'while'       | 'if'
         * 'assign'      | 'variable'    | 'constant'    | 'procedure'
         * 'such that'   | 'with'        | 'prog_line'   | 'and'
         */
        KEY_WORD,
        BOOLEAN,            // 'BOOLEAN'
        ATTRIBUTE_NAME,     // 'procName' | 'varName' | 'value' | 'stmt#'
        IDENTIFIER,         // variable names
        SEPARATOR,          // ','
        CONSTANT_INTEGER,   // statement numbers
        CONSTANT_STRING,    // '"string literal"'
        WILD_CARD,          // '_'
        OPEN_BRACKET,       // '('
        CLOSE_BRACKET,      // ')'
        STATEMENT_END,      // ';'
        OPEN_TUPLE,         // '<'
        CLOSE_TUPLE,        // '>'
        EQUAL_OPERATOR,     // '='
        MEMBER_OPERATOR     // '.'
    };

    class Token {
    public:
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
