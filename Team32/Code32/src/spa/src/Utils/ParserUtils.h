#ifndef GUARD_PARSER_UTILS_H
#define GUARD_PARSER_UTILS_H

#include <string>

void throwWithoutToken(std::string expectedToken, size_t lineNumber);
void throwWithToken(std::string expectedToken, std::string actualToken, size_t lineNumber);

#endif
