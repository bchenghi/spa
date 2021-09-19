#include <string>
#include <set>
#include <iostream>

#include "QueryEvaluator.h"
#include "QueryEvaluatorHelper.h"

using std::vector;
using std::set;
using std::pair;
using std::string;
using pql::FilterClause;
using pql::FilterResult;
using pql::PkbAbstractor;
using pql::Query;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::QueryEvaluator;
using pql::QueryResultProjector;
using pql::QueryEvaluatorHelper;

QueryEvaluator::QueryEvaluator() {
    PkbAbstractor* pkbAbstractorPtr = new PkbAbstractor;
    this->pkbAbstractor = pkbAbstractorPtr;
    QueryResultProjector* queryResultProjectorPtr = new QueryResultProjector;
    this->queryResultProjector = queryResultProjectorPtr;
}

QueryEvaluator::QueryEvaluator(PkbAbstractor* pkbAbstractor, QueryResultProjector* queryResultProjector) :
pkbAbstractor(pkbAbstractor), queryResultProjector(queryResultProjector) {
}

set<string> QueryEvaluator::executeQuery(Query queryObject) {
    set<string> valueStringsSet; // Final result to send to projector

    vector<QueryDesignEntity> designEntitiesVector = queryObject.designEntitiesVector;
    unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;

    vector<FilterClause*> filterClauses = queryObject.filterClauseVector;

    // Get all combinations of values from the select clause design entities.
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> allDesignEntityValueCombinations = queryObject.select->getAllEntityCombinations(pkbAbstractor);

    for (int i = 0; i < allDesignEntityValueCombinations.size(); i++) {
        vector<pair<QueryDesignEntity, QueryArgValue>> designEntityValueCombination = allDesignEntityValueCombinations[i];

        // Add values to the map containing values to use for all clauses.
        for (int j = 0; j < designEntityValueCombination.size(); j++) {
            usedVariablesMap.insert(designEntityValueCombination[j]);
        }

        vector<unordered_map<QueryDesignEntity, QueryArgValue>> resultMap = QueryEvaluatorHelper::startQuery(usedVariablesMap,
                                                                                       filterClauses,
                                                                                       this->pkbAbstractor);

        // Each map contains the values matched to design entities.
        // Obtain only for those in select clause, and add its value to valueStringsSet.
        for (unordered_map<QueryDesignEntity, QueryArgValue> assignedValues : resultMap) {
            unordered_map<QueryDesignEntity, QueryArgValue>::const_iterator foundKeyValue
                    = assignedValues.find(queryObject.select->queryDesignEntity);

            if (foundKeyValue == assignedValues.end()) {
                continue;
            } else {
                // Update final result with value in clause
                QueryArgValue valueOfEntity = foundKeyValue->second;
                valueStringsSet.insert(valueOfEntity.value);
            }
        }
        usedVariablesMap = {};
    }

    vector<string> valueStringsVector(valueStringsSet.begin(), valueStringsSet.end());
    queryResultProjector->outputResult(valueStringsVector);
    delete queryObject.select;
    for (FilterClause* filterClause : filterClauses) {
        filterClause->free();
        delete filterClause;
    }
    return valueStringsSet;
}


