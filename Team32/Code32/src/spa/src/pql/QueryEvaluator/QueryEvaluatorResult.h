#ifndef GUARD_QUERY_EVALUATOR_RESULT_H
#define GUARD_QUERY_EVALUATOR_RESULT_H

#include <unordered_map>
#include <vector>
#include "pql/QueryPreprocessor/Query/QueryDesignEntity.h"
#include "pql/QueryPreprocessor/Query/QueryArgValue.h"

using std::unordered_map;
using std::vector;

namespace pql {
    class QueryEvaluatorResult {
    public:
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> entityValuesList;
        bool isValid;
        QueryEvaluatorResult(vector<unordered_map<QueryDesignEntity, QueryArgValue>> entityValuesList);
        QueryEvaluatorResult(bool isValid);
        bool operator==(const QueryEvaluatorResult& other) const {
            return entityValuesList == other.entityValuesList && isValid == other.isValid;
        }
    };
}


#endif //GUARD_QUERY_EVALUATOR_RESULT_H
