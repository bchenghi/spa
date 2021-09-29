#ifndef GUARD_PARSER_UTILS_H
#define GUARD_PARSER_UTILS_H

#include "simple/Tokenizer/Token.h"

#include <string>
#include <vector>

void throwWithoutToken(const std::string& expectedToken, size_t lineNumber);
void throwWithToken(const std::string& expectedToken, const std::string& actualToken, size_t lineNumber);
std::vector<std::string> tokenToPostfixExpression(
    const std::vector<simple::Token>& tokens,
    size_t startIndex,
    size_t endIndex
);
void throwWithMessage(const std::string& message);
void trim(std::string& source);

#endif
