#ifndef GUARD_PQL_TOKENIZER_H
#define GUARD_PQL_TOKENIZER_H

#include "Token/PqlToken.h"

#include <string>
#include <vector>

namespace pql {
    class PqlTokenizer {
    public:
        static std::vector<PqlToken> tokenize(std::string&);

    private:
        static void next(size_t&, size_t&, std::string&, std::vector<PqlToken>&);
        static void processSymbol(size_t&, size_t&, std::string&, std::vector<PqlToken>&);
        static void processConstString(size_t&, size_t&, std::string&, std::vector<PqlToken>&);
        static void processConstInteger(size_t&, size_t&, std::string&, std::vector<PqlToken>&);
        static void processName(size_t&, size_t&, std::string&, std::vector<PqlToken>&);
    };
}

#endif
