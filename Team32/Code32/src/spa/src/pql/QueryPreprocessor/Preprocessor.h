#ifndef GUARD_PREPROCESSOR_H
#define GUARD_PREPROCESSOR_H
#include "Query/Query.h"

namespace pql {
    class Preprocessor {
    public:
        virtual pql::Query preprocess(std::string query_text);
    };
}
#endif
