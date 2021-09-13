#ifndef GUARD_PARSER_UTILS_H
#define GUARD_PARSER_UTILS_H

#include "../Tokenizer/Token.h"

#include <string>
#include <vector>

namespace pql {
    void throwWithoutToken(std::string expectedToken, size_t lineNumber);
    void throwWithToken(std::string expectedToken, std::string actualToken, size_t lineNumber);
    std::string tokenToPostfixExpression(
        const std::vector<pql::Token>& tokens,
        size_t startIndex,
        size_t endIndex
    );
    void throwWithMessage(std::string message);
}

#endif
