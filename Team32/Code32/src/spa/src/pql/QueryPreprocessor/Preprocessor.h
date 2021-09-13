#include "Query/Query.h"

class Preprocessor {
public:
    virtual pql::Query preprocess(std::string query_text);
};