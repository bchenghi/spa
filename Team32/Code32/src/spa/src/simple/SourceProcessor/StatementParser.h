#ifndef GUARD_STATEMENT_PARSER_H
#define GUARD_STATEMENT_PARSER_H

#include "simple/Tokenizer/Token.h"

#include <string>
#include <vector>

namespace simple {
    enum class ExpressionType { IF, WHILE, OTHER };

    struct {
        const std::vector<Token>& statementTokens;
        const size_t statementNumber;
        const std::string procedureName;
    } typedef Statement;

    bool validateExpression(std::vector<Token>&);

    class StatementParser {
    public:
        StatementParser(/* pkb here */);

        void parse(const Statement&);

    private:
        /* pkb here */

        void parseAssignmentStatement(const Statement&);
        void parseKeywordStatement(const Token&, const Statement&);
        void parseReadStatement(size_t, const Statement&);
        void parsePrintStatement(size_t, const Statement&);
        void parseCallStatement(size_t, const Statement&);
        void parseWhileStatement(size_t, const Statement&);
        void parseIfStatement(size_t, const Statement&);

        size_t parseConditionExpression(size_t, const Statement&, ExpressionType);
        size_t parseRelationalExpression(size_t, const Statement&, ExpressionType);
        size_t parseExpression(size_t, const Statement&, ExpressionType);
    };
}

#endif
