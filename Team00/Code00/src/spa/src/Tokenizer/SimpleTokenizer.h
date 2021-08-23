#ifndef GUARD_SIMPLE_TOKENIZER_H
#define GUARD_SIMPLE_TOKENIZER_H

#include "Tokenizer/Token/SimpleToken.h"

#include <string>
#include <vector>

class SimpleTokenizer {
public:
    static std::vector<SimpleToken> tokenize(std::string&);

private:
    static void next(size_t&, size_t&, std::string&, std::vector<SimpleToken>&);
};

#endif
