#ifndef GUARD_PQL_TOKENIZER_H
#define GUARD_PQL_TOKENIZER_H

#include "Token/PqlToken.h"

#include <string>
#include <vector>

class PqlTokenizer {
public:
    static std::vector<PqlToken> tokenize(std::string&);

private:
    static void next(size_t&, size_t&, std::string&, std::vector<PqlToken>&);
};

#endif
