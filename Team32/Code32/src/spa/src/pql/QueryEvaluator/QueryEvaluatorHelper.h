#ifndef GUARD_QUERY_EVALUATOR_HELPER_H
#define GUARD_QUERY_EVALUATOR_HELPER_H

#include "../QueryPreprocessor/Query/Clause/FilterClause.h"
#include "../QueryPreprocessor/Query/QueryDesignEntity.h"
#include "../QueryPreprocessor/Query/QueryArgValue.h"
#include "../PkbAbstractor/PkbAbstractor.h"

#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;

namespace pql {
    class QueryEvaluatorHelper {
    public:
        static vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQuery(
            unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap,
            std::vector<FilterClause*> filterClausesLeftVector,
            PkbAbstractor* pkbAbstractor
        );
    };
}


#endif //GUARD_QUERY_EVALUATOR_HELPER_H
