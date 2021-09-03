#ifndef GUARD_SIMPLE_TOKENIZER_H
#define GUARD_SIMPLE_TOKENIZER_H

#include "Token.h"

#include <string>
#include <vector>

namespace simple {
    class Tokenizer {
    public:
        static std::vector<Token> tokenize(std::string&);

    private:
        static void next(size_t&, size_t&, std::string&, std::vector<Token>&);
        static void processSymbol(size_t&, size_t&, std::string&, std::vector<Token>&);
        static void processConst(size_t&, size_t&, std::string&, std::vector<Token>&);
        static void processName(size_t&, size_t&, std::string&, std::vector<Token>&);
    };
}

#endif
