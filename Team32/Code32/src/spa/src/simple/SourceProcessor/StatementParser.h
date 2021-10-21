#ifndef GUARD_STATEMENT_PARSER_H
#define GUARD_STATEMENT_PARSER_H

#include "simple/Tokenizer/Token.h"

#include <string>
#include <vector>

namespace simple {
    enum class ExpressionType { IF, WHILE, OTHER };

    struct {
        std::vector<Token>& statementTokens;
        const size_t statementNumber;
        const std::string procedureName;
    } typedef Statement;

    bool validateExpression(std::vector<Token>&);

    class StatementParser {
    public:
        StatementParser(/* pkb here */);

        void parse(Statement&);

    private:
        /* pkb here */

        void parseAssignmentStatement(Statement&);
        void parseKeywordStatement(const Token&, Statement&);
        void parseReadStatement(size_t, const Statement&);
        void parsePrintStatement(size_t, const Statement&);
        void parseCallStatement(size_t, const Statement&);
        void parseWhileStatement(size_t, Statement&);
        void parseIfStatement(size_t, Statement&);

        size_t parseConditionExpression(size_t, Statement&, ExpressionType);
        size_t parseRelationalExpression(size_t, Statement&, ExpressionType);
        size_t parseExpression(size_t, Statement&, ExpressionType);
    };
}

#endif
