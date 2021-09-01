#ifndef GUARD_STATEMENT_PARSER_H
#define GUARD_STATEMENT_PARSER_H

#include "simple/Tokenizer/Token.h"

#include <vector>

namespace simple {
    struct {
        const std::vector<Token>& statement_tokens;
        const size_t statement_number;
    } typedef Statement;

    class StatementParser {
    public:
        StatementParser(/* pkb here */);

        void parse(const Statement& statement);

    private:
        /* pkb here */
    };
}

#endif
