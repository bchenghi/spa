#ifndef GUARD_PROCESSOR_H
#define GUARD_PROCESSOR_H

#include "Query/Query.h"

class Preprocessor {
public:
    virtual pql::Query preprocess(std::string query_text);
};

#endif //GUARD_PROCESSOR_H