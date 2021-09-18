#include "QueryEvaluatorHelper.h"
#include <iostream>

using pql::QueryEvaluatorHelper;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

// Recursively obtains vector of maps, each map with design entity synonym as key, and matching value as value.
vector<unordered_map<QueryDesignEntity, QueryArgValue>> QueryEvaluatorHelper::startQuery(
    unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap,
    std::vector<FilterClause*> filterClausesLeftVector,
    PkbAbstractor* pkbAbstractor
) {
    if (filterClausesLeftVector.empty()) {
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> result;
        if (!usedVariablesMap.empty()) {
            result.push_back(usedVariablesMap);
        }
        return result;
    }

    // Get first clause, check if their arg values are in usedVariablesMap. If yes, update current clause with value.
    // Call executePKBAbsQuery on the clause and get result.
    FilterClause* currentFilterClause = filterClausesLeftVector[0];
    vector<QueryArg*> queryArgsInCurrentClause = currentFilterClause->getQueryArgs();
    for (QueryArg* q : queryArgsInCurrentClause) {
        if (q->queryDesignEntity == nullptr) {
            // If clause argument is a value/wildcard, not design entity, skip to next argument.
            continue;
        }
        unordered_map<QueryDesignEntity, QueryArgValue>::const_iterator foundKeyValue = usedVariablesMap.find(*(q->queryDesignEntity));
        if (foundKeyValue == usedVariablesMap.end()) {
            // If clause was reused in a different path of design entity assignment, and not yet assigned, set value to null (may have been set before)
            if (q->argValue != nullptr) {
                delete q->argValue;
            }
            q->argValue = nullptr;
        } else {
            // Update value in clause
            QueryArgValue* valueOfEntity = new QueryArgValue(foundKeyValue->second);
            if (q->argValue != nullptr) {
                delete q->argValue;
            }
            q->argValue = valueOfEntity;
        }
    }

    vector<unordered_map<QueryDesignEntity, QueryArgValue>> finalResult;
    // Update unordered map with newly assigned values to entities.
    FilterResult filterResult = currentFilterClause->executePKBAbsQuery(pkbAbstractor);

    vector<unordered_map<QueryDesignEntity, QueryArgValue>> c;
    filterClausesLeftVector.erase(filterClausesLeftVector.begin());

    if (!filterResult.getHasMatch()) {
        // If clause fails to get a match, return empty result
        return finalResult;
    }

    if (filterResult.getSize() > 0) {
        for (int i = 0; i < filterResult.getSize(); i++) {
            unordered_map<QueryDesignEntity, QueryArgValue> newUsedVariablesMap = usedVariablesMap;
            vector<pair<QueryDesignEntity, QueryArgValue>> entitiesAndValuesVector = filterResult.getEntitiesAndValuesAtIndex(i);
            for (int j = 0; j < entitiesAndValuesVector.size(); j++) {
                pair<QueryDesignEntity, QueryArgValue> matchedEntityValue = entitiesAndValuesVector[j];
                unordered_map<QueryDesignEntity, QueryArgValue>::const_iterator foundKeyValue = newUsedVariablesMap.find(matchedEntityValue.first);
                if (foundKeyValue == newUsedVariablesMap.end()) {
                    // QueryDesignEntity not in newUsedVariablesMap, add to newUsedVariablesMap
                    std::pair<QueryDesignEntity, QueryArgValue> newKeyValue (matchedEntityValue.first, matchedEntityValue.second);
                    newUsedVariablesMap.insert(newKeyValue);
                } else {
                    QueryArgValue valueOfEntity = foundKeyValue->second;
                    // valueOfEntity and matchedEntityValue.second must be equal.
                }
            }
            vector<unordered_map<QueryDesignEntity, QueryArgValue>> result = startQuery(
                newUsedVariablesMap,
                filterClausesLeftVector,
                pkbAbstractor
            );
            finalResult.insert(finalResult.end(), result.begin(), result.end());
        }
    } else {
        // If has match but not assigned to any design entities, continue with one less clause.
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> result = startQuery(
            usedVariablesMap,
            filterClausesLeftVector,
            pkbAbstractor
        );
        finalResult.insert(finalResult.end(), result.begin(), result.end());
    }
    return finalResult;
}
