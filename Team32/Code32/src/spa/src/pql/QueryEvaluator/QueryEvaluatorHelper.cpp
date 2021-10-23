#include "QueryEvaluatorHelper.h"

using pql::QueryEvaluatorHelper;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::QueryEvaluatorResult;

// Recursively obtains vector of maps, each map with design entity synonym as key, and matching value as value.
QueryEvaluatorResult QueryEvaluatorHelper::startQuery(
    unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap,
    std::vector<FilterClause*> filterClausesLeftVector,
    PkbAbstractor* pkbAbstractor
) {
    if (filterClausesLeftVector.empty()) {
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> result;
        if (!usedVariablesMap.empty()) {
            result.push_back(usedVariablesMap);
        }
        return QueryEvaluatorResult(result);
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
        // If clause fails to get a match, return failed result
        return QueryEvaluatorResult(false);
    }

    bool atLeastOneValidRecursiveResult = false;
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
            QueryEvaluatorResult result = startQuery(
                newUsedVariablesMap,
                filterClausesLeftVector,
                pkbAbstractor
            );
            finalResult.insert(finalResult.end(), result.entityValuesList.begin(), result.entityValuesList.end());
            if (!atLeastOneValidRecursiveResult && result.isValid) {
                atLeastOneValidRecursiveResult = true;
            }
        }
    } else {
        // If has match but not assigned to any design entities, continue with one less clause.
        QueryEvaluatorResult result = startQuery(
            usedVariablesMap,
            filterClausesLeftVector,
            pkbAbstractor
        );
        finalResult.insert(finalResult.end(), result.entityValuesList.begin(), result.entityValuesList.end());
        if (!atLeastOneValidRecursiveResult && result.isValid) {
            atLeastOneValidRecursiveResult = true;
        }
    }

    // Return valid result with used entity values if at least one recursion was valid. Otherwise, return invalid.
    if (atLeastOneValidRecursiveResult) {
        return QueryEvaluatorResult(finalResult);
    } else {
        return QueryEvaluatorResult(false);
    }
}

unordered_map<QueryDesignEntity, vector<QueryArgValue>> QueryEvaluatorHelper::getAllValuesOfEntities(
        vector<QueryDesignEntity> queryDesignEntities, PkbAbstractor* pkbAbstractor) {
    unordered_map<QueryDesignEntity, vector<QueryArgValue>> result = {};
    for (QueryDesignEntity qde : queryDesignEntities) {
        vector<QueryArgValue> values = getAllValuesOfEntity(qde, pkbAbstractor);
        result.insert(pair(qde, values));
    }
    return result;
}

vector<vector<pair<QueryDesignEntity, QueryArgValue>>> QueryEvaluatorHelper::flattenGetAllValuesOfEntitiesResult(
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> entitiesAndValues) {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> result = {};
    for (pair<QueryDesignEntity, vector<QueryArgValue>> entityAndValues : entitiesAndValues) {
        QueryDesignEntity qde = entityAndValues.first;
        vector<QueryArgValue> values = entityAndValues.second;
        vector<pair<QueryDesignEntity, QueryArgValue>> valuesForGivenEntityVector = {};
        for (QueryArgValue value : values) {
            valuesForGivenEntityVector.push_back(pair(qde, value));
        }
        result.push_back(valuesForGivenEntityVector);
    }
    return result;
}

set<vector<string>> QueryEvaluatorHelper::updateResultWithAttrVals(vector<QueryDesignEntity> designEntitiesVector,
                                                                   set<vector<string>> valueStringsSet, PkbAbstractor *pkbAbstractor) {
    // Get the index of entities with attributes
    set<int> indicesOfEntitiesWithAttr = {};
    for (int i = 0; i < designEntitiesVector.size(); i++) {
        QueryDesignEntity currentEntity = designEntitiesVector[i];
        if ((currentEntity.designEntity == DesignEntity::CALL && currentEntity.attributeType == AttributeType::PROCEDURE_NAME) ||
        (currentEntity.designEntity == DesignEntity::READ && currentEntity.attributeType == AttributeType::VARIABLE_NAME) ||
        (currentEntity.designEntity == DesignEntity::PRINT && currentEntity.attributeType == AttributeType::VARIABLE_NAME)) {
            indicesOfEntitiesWithAttr.insert(i);
        }
    }

    if (!indicesOfEntitiesWithAttr.empty()) {
        set<vector<string>> updatedValueStringSet = {};
        // convert based on indicesOfEntitiesWithAttr
        for (auto it = valueStringsSet.begin(); it != valueStringsSet.end(); it++) {
            vector<string> currentVector = *it;
            for (int i=0; i < currentVector.size(); i++) {
                if (indicesOfEntitiesWithAttr.find(i) != indicesOfEntitiesWithAttr.end()) {
                    QueryDesignEntity currentEntity = designEntitiesVector[i];
                    currentVector[i] = pkbAbstractor -> getAttributeVal(std::stoi(currentVector[i]), currentEntity.designEntity, currentEntity.attributeType);
                }
            }
            updatedValueStringSet.insert(currentVector);
        }
        return updatedValueStringSet;
    } else {
        return valueStringsSet;
    }
}

vector<vector<pair<QueryDesignEntity, QueryArgValue>>> QueryEvaluatorHelper::cartesianProduct(
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> v) {
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> result = {{}};
    for (auto& vec : v) {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> newResult;
        for (auto& vectorInResult : result) {
            for (auto designEntityValuePair : vec) {
                newResult.push_back(vectorInResult);
                newResult.back().push_back(designEntityValuePair);
            }
        }
        result.swap(newResult);
    }
    return result;
}

vector<QueryArgValue> QueryEvaluatorHelper::getAllValuesOfEntity(QueryDesignEntity queryDesignEntity,
                                                              PkbAbstractor* pkbAbstractor) {
    ListOfStmtNos listOfStmtNo = {};
    switch(queryDesignEntity.designEntity) {
        case DesignEntity::ASSIGN: {
            listOfStmtNo = pkbAbstractor->getAllAssignStmts();
            break;
        }
        case DesignEntity::CALL: {
            listOfStmtNo = pkbAbstractor->getAllCallStmts();
            break;
        }
        case DesignEntity::CONSTANT: {
            vector<std::string> constants = pkbAbstractor->getAllConstants();
            return getQueryArgValueVectorFromValues(DesignEntity::CONSTANT, constants);
        }
        case DesignEntity::IF: {
            listOfStmtNo = pkbAbstractor->getAllIfStmts();
            break;
        }
        case DesignEntity::PRINT: {
            listOfStmtNo = pkbAbstractor->getAllPrintStmts();
            break;
        }
        case DesignEntity::PROCEDURE: {
            ListOfProcNames procNamesSet = pkbAbstractor->getAllProcNames();
            vector<std::string> procNames = vector(procNamesSet.begin(), procNamesSet.end());
            return getQueryArgValueVectorFromValues(DesignEntity::PROCEDURE, procNames);
        }
        case DesignEntity::READ: {
            listOfStmtNo = pkbAbstractor->getAllReadStmts();
            break;
        }
        case DesignEntity::STMT:
        case DesignEntity::PROGRAM_LINE: {
            int largestStmtNum = pkbAbstractor->getLargestStmtNum();
            return getQueryArgValueVectorFromLargestInt(largestStmtNum);
        }
        case DesignEntity::VARIABLE: {
            ListOfVarNames varNamesSet = pkbAbstractor->getAllVarNames();
            vector<std::string> varNames = vector(varNamesSet.begin(), varNamesSet.end());
            return getQueryArgValueVectorFromValues(DesignEntity::VARIABLE, varNames);
        }
        case DesignEntity::WHILE: {
            listOfStmtNo = pkbAbstractor->getAllWhileStmts();
            break;
        }
    }

    return getQueryArgValueVectorFromStmtLst(listOfStmtNo);
}

vector<QueryArgValue> QueryEvaluatorHelper::getQueryArgValueVectorFromValues(DesignEntity designEntity, vector<string> values) {
    vector<QueryArgValue> result = {};
    for (string value : values) {
        result.push_back(QueryArgValue(designEntity, value));
    }
    return result;
}

vector<QueryArgValue> QueryEvaluatorHelper::getQueryArgValueVectorFromStmtLst(unordered_set<StmtNo> stmtNos) {
    vector<QueryArgValue> result = {};
    for (StmtNo num : stmtNos) {
        result.push_back(QueryArgValue(DesignEntity::STMT, std::to_string(num)));
    }
    return result;
}

vector<QueryArgValue> QueryEvaluatorHelper::getQueryArgValueVectorFromLargestInt(int largestStmtNum) {
    vector<QueryArgValue> result = {};
    for (int i = 1; i <= largestStmtNum; i++) {
        result.push_back(QueryArgValue(DesignEntity::STMT, std::to_string(i)));
    }
    return result;
}