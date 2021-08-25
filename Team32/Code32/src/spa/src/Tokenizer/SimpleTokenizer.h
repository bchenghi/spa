#ifndef GUARD_SIMPLE_TOKENIZER_H
#define GUARD_SIMPLE_TOKENIZER_H

#include "Token/SimpleToken.h"

#include <string>
#include <vector>

namespace simple {
    class SimpleTokenizer {
    public:
        static std::vector<SimpleToken> tokenize(std::string&);

    private:
        static void next(size_t&, size_t&, std::string&, std::vector<SimpleToken>&);
        static void processSymbol(size_t&, size_t&, std::string&, std::vector<SimpleToken>&);
        static void processConst(size_t&, size_t&, std::string&, std::vector<SimpleToken>&);
        static void processName(size_t&, size_t&, std::string&, std::vector<SimpleToken>&);
    };
}

#endif
