#ifndef GUARD_QUERY_EVALUATOR_HELPER_H
#define GUARD_QUERY_EVALUATOR_HELPER_H

#include "QueryEvaluatorResult.h"
#include "../QueryPreprocessor/Query/Clause/FilterClause.h"
#include "../QueryPreprocessor/Query/QueryDesignEntity.h"
#include "../QueryPreprocessor/Query/QueryArgValue.h"
#include "../PkbAbstractor/PkbAbstractor.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>

using std::unordered_set;
using std::unordered_map;
using std::vector;

namespace pql {
    class QueryEvaluatorHelper {
    public:
        static QueryEvaluatorResult startQuery(
            unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap,
            std::vector<FilterClause*> filterClausesLeftVector,
            PkbAbstractor* pkbAbstractor
        );
        static vector<vector<pair<QueryDesignEntity, QueryArgValue>>> cartesianProduct(
                vector<vector<pair<QueryDesignEntity, QueryArgValue>>> v);

        static unordered_map<QueryDesignEntity, vector<QueryArgValue>> getAllValuesOfEntities(vector<QueryDesignEntity>,
                PkbAbstractor* pkbAbstractor);

        static vector<vector<pair<QueryDesignEntity, QueryArgValue>>> flattenGetAllValuesOfEntitiesResult(
                unordered_map<QueryDesignEntity, vector<QueryArgValue>>);

    private:
        static vector<QueryArgValue> getAllValuesOfEntity(QueryDesignEntity, PkbAbstractor* pkbAbstractor);
        // For procedure names, constants or variables
        static vector<QueryArgValue> getQueryArgValueVectorFromValues(DesignEntity, vector<string>);
        static vector<QueryArgValue> getQueryArgValueVectorFromStmtLst(unordered_set<StmtNo>);
        static vector<QueryArgValue> getQueryArgValueVectorFromLargestInt(int);

    };
}


#endif //GUARD_QUERY_EVALUATOR_HELPER_H
