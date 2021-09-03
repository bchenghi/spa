#ifndef GUARD_QUERY_EVALUATOR_H
#define GUARD_QUERY_EVALUATOR_H

#include <vector>
#include <unordered_map>
#include <set>
#include "QueryProcessor/PkbAbstraction/PkbAbstractor.h"
#include "QueryProcessor/QueryPreprocessor/Query/Query.h"
#include "QueryProcessor/QueryPreprocessor/Query/QueryArgValue.h"
#include "QueryProcessor/QueryPreprocessor/Query/QueryDesignEntity.h"
#include "QueryProcessor/QueryResultProjector/QueryResultProjector.h"

using std::vector;
using std::string;
using std::set;
using std::unordered_map;

namespace pql {
    class QueryEvaluator {
    public:
        PkbAbstractor* pkbAbstractor;
        QueryResultProjector* queryResultProjector;
        QueryEvaluator(PkbAbstractor* pkbAbstractor, QueryResultProjector* queryResultProjector1);
        set<string> executeQuery(Query queryObject);

    private:
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQuery(unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap,
                                                                           vector<FilterClause*> filterClausesLeftVector,
                                                                           PkbAbstractor* pkbAbstractor);
    };
}

#endif // GUARD_QUERY_EVALUATOR_H
