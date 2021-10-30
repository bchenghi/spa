#include <string>
#include <set>

#include "Optimisation/Optimiser.h"
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
using pql::QueryResult;
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

QueryResult QueryEvaluator::executeQuery(Query queryObject, bool isOptimisationOn) {
    SelectClause* selectClausePtr = queryObject.select;
    vector<QueryDesignEntity> designEntitiesVector = queryObject.designEntitiesVector;
    unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
    vector<FilterClause*> filterClauses = queryObject.filterClauseVector;
    if (isOptimisationOn) {
        filterClauses = Optimiser::optimise(selectClausePtr->queryDesignEntities, queryObject.filterClauseVector);
    }
    QueryEvaluatorResult result = QueryEvaluatorHelper::startQuery(usedVariablesMap,
                                                                                   filterClauses,
                                                                                   this->pkbAbstractor);
    // Clear cache
    this->pkbAbstractor->clear();

    // Check if select clause is boolean
    if (selectClausePtr->queryDesignEntities.empty()) {
        return QueryResult(result.isValid);
    }

    if (!result.isValid) {
        set<vector<string>> emptyValueStringSet = {};
        return QueryResult(emptyValueStringSet);
    }

    vector<unordered_map<QueryDesignEntity, QueryArgValue>> resultMap = result.entityValuesList;


    // Obtain selected synonyms that are not in the resultMap (not assigned)
    vector<QueryDesignEntity> designEntitiesNotAssigned = {};
    unordered_map<QueryDesignEntity, QueryArgValue> assignedValues = {};
    if (resultMap.size() > 0) {
        assignedValues = resultMap[0];
    }
    for (int k = 0; k < selectClausePtr->queryDesignEntities.size(); k++) {
        unordered_map<QueryDesignEntity, QueryArgValue>::const_iterator foundKeyValue
        = assignedValues.find(selectClausePtr->queryDesignEntities[k]);

        if (foundKeyValue == assignedValues.end()) {
            designEntitiesNotAssigned.push_back(selectClausePtr->queryDesignEntities[k]);
        }
    }


    // Get all values for each unassigned entity
    unordered_map<QueryDesignEntity, vector<QueryArgValue>> unassignedEntityValues =
            QueryEvaluatorHelper::getAllValuesOfEntities(designEntitiesNotAssigned, pkbAbstractor);

    // Flatten {{entity1, [value1, value2]}, {entity2, [value3, ...]}} to
    // {{{entity1, value1}, {entity1, value2}}, {{entity2, value3},...}} to use in cartesian product
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> flattenedEntityResults =
            QueryEvaluatorHelper::flattenGetAllValuesOfEntitiesResult(unassignedEntityValues);

    // Cartesian product of the entity values, each result vector contains combination of the values of unassigned entities.
    // {{{entity1, value1}, {entity2, value3}}, {...}, ...}
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> cartesianProductOfUnassignedEntityValues =
            QueryEvaluatorHelper::cartesianProduct(flattenedEntityResults);


    // For each combination in cartesian product, insert into each unordered map.
    vector<unordered_map<QueryDesignEntity, QueryArgValue>> assignedMapsVector = {};
    if (!cartesianProductOfUnassignedEntityValues.empty()) {
        for (vector<pair<QueryDesignEntity, QueryArgValue>> combination : cartesianProductOfUnassignedEntityValues) {
            if (resultMap.size() > 0) {
                for (unordered_map<QueryDesignEntity, QueryArgValue> resultValues : resultMap) {
                    unordered_map<QueryDesignEntity, QueryArgValue> newMap = resultValues;
                    for (pair<QueryDesignEntity, QueryArgValue> unassignedEntityValuePair : combination) {
                        newMap.insert(unassignedEntityValuePair);
                    }
                    assignedMapsVector.push_back(newMap);
                }
            } else {
                unordered_map<QueryDesignEntity, QueryArgValue> newMap = {};
                for (pair<QueryDesignEntity, QueryArgValue> unassignedEntityValuePair : combination) {
                    newMap.insert(unassignedEntityValuePair);
                }
                assignedMapsVector.push_back(newMap);
            }
        }
    } else {
        for (unordered_map<QueryDesignEntity, QueryArgValue> resultValues : resultMap) {
            assignedMapsVector.push_back(resultValues);
        }
    }

    set<vector<string>> valueStringsSet; // Final result to send to projector

    // Each map contains the values matched to design entities.
    // Obtain only for those in select clause, and add its value to valueStringsSet.
    for (unordered_map<QueryDesignEntity, QueryArgValue> assignedValues : assignedMapsVector) {
        vector<string> resultVector = {};
        for (int k = 0; k < selectClausePtr->queryDesignEntities.size(); k++) {
            unordered_map<QueryDesignEntity, QueryArgValue>::const_iterator foundKeyValue
            = assignedValues.find(selectClausePtr->queryDesignEntities[k]);

            if (foundKeyValue == assignedValues.end()) {
                continue;
            } else {
                // Update final result with value in clause
                QueryArgValue valueOfEntity = foundKeyValue->second;
                resultVector.push_back(valueOfEntity.value);
            }
        }
        valueStringsSet.insert(resultVector);
    }

    // Know which elements are refs.
    // For each vector in set, for ref, update the valueStringSet with ref value.
    // return the valueStringSet

    valueStringsSet = QueryEvaluatorHelper::updateResultWithAttrVals(designEntitiesVector, valueStringsSet, pkbAbstractor);

    // vector<string> valueStringsVector(valueStringsSet.begin(), valueStringsSet.end());
    // queryResultProjector->outputResult(valueStringsVector);
    delete queryObject.select;
    for (FilterClause* filterClause : filterClauses) {
        filterClause->free();
        delete filterClause;
    }

    // Return set of values if select clause is not boolean.
    return QueryResult(valueStringsSet);
}


