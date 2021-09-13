#ifndef GUARD_QUERY_EVALUATOR_H
#define GUARD_QUERY_EVALUATOR_H

#include <vector>
#include <unordered_map>
#include <set>
#include "pql/PkbAbstractor/PkbAbstractor.h"
#include "pql/QueryPreprocessor/Query/Query.h"
#include "pql/QueryPreprocessor/Query/QueryArgValue.h"
#include "pql/QueryPreprocessor/Query/QueryDesignEntity.h"
#include "pql/QueryResultProjector/QueryResultProjector.h"

using std::vector;
using std::string;
using std::set;
using std::unordered_map;

namespace pql {
    class QueryEvaluator {
    public:
        PkbAbstractor* pkbAbstractor;
        QueryResultProjector* queryResultProjector;
        QueryEvaluator();
        QueryEvaluator(PkbAbstractor* pkbAbstractor, QueryResultProjector* queryResultProjector1);
        set<string> executeQuery(Query queryObject);

    private:
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQuery(unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap,
                                                                           vector<FilterClause*> filterClausesLeftVector,
                                                                           PkbAbstractor* pkbAbstractor);
    };
}

#endif // GUARD_QUERY_EVALUATOR_H
