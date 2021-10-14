#ifndef GUARD_QUERY_EVALUATOR_H
#define GUARD_QUERY_EVALUATOR_H

#include "pql/PkbAbstractor/PkbAbstractor.h"
#include "pql/QueryPreprocessor/Query/Query.h"
#include "pql/QueryPreprocessor/Query/QueryArgValue.h"
#include "pql/QueryPreprocessor/Query/QueryDesignEntity.h"
#include "pql/QueryResultProjector/QueryResultProjector.h"
#include "pql/QueryResult.h"

#include <set>
#include <unordered_map>
#include <vector>

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
        QueryResult executeQuery(Query queryObject, bool isOptimisationOn = true);
    };
}

#endif // GUARD_QUERY_EVALUATOR_H
