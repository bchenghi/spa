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
    SelectClause* selectClausePtr = queryObject.getSelectClause();
    vector<QueryDesignEntity> designEntitiesVector = queryObject.getQueryDesignEntities();
    unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
    vector<FilterClause*> filterClauses = queryObject.getFilterClauses();
    vector<QueryDesignEntity> selectedEntities = selectClausePtr->getSelectedEntities();
    if (isOptimisationOn) {
        filterClauses = Optimiser::optimise(selectedEntities, queryObject.getFilterClauses());
    }
    QueryEvaluatorResult result = QueryEvaluatorHelper::startQuery(usedVariablesMap,
                                                                                   filterClauses,
                                                                                   this->pkbAbstractor);
    // Clear cache
    this->pkbAbstractor->clear();

    // Check if select clause is boolean
    if (selectedEntities.empty()) {
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
    for (int k = 0; k < selectedEntities.size(); k++) {
        unordered_map<QueryDesignEntity, QueryArgValue>::const_iterator foundKeyValue
        = assignedValues.find(selectedEntities[k]);

        if (foundKeyValue == assignedValues.end()) {
            designEntitiesNotAssigned.push_back(selectedEntities[k]);
        }
    }

    // Cartesian product of the entity values, each result vector contains combination of the values of unassigned entities.
    vector<vector<pair<QueryDesignEntity, QueryArgValue>>> cartesianProductOfUnassignedEntityValues =
            QueryEvaluatorHelper::getValuesOfEntities(designEntitiesNotAssigned, pkbAbstractor);


    // For each combination in cartesian product, insert into each unordered map.
    vector<unordered_map<QueryDesignEntity, QueryArgValue>> assignedMapsVector = QueryEvaluatorHelper::mergeEntityValues(
            resultMap, cartesianProductOfUnassignedEntityValues);

    set<vector<string>> valueStringsSet;

    // Each map contains the values matched to design entities.
    // Obtain only for those in select clause, and add its value to valueStringsSet.
    for (unordered_map<QueryDesignEntity, QueryArgValue> assignedValues : assignedMapsVector) {
        vector<string> resultVector = {};
        for (int k = 0; k < selectedEntities.size(); k++) {
            unordered_map<QueryDesignEntity, QueryArgValue>::const_iterator foundKeyValue
            = assignedValues.find(selectedEntities[k]);

            if (foundKeyValue == assignedValues.end()) {
                continue;
            } else {
                // Update final result with value in clause
                QueryArgValue valueOfEntity = foundKeyValue->second;
                resultVector.push_back(valueOfEntity.getValue());
            }
        }
        valueStringsSet.insert(resultVector);
    }

    // update the obtained synonym values with attribute value if it has attribute type.
    valueStringsSet = QueryEvaluatorHelper::updateResultWithAttrVals(selectedEntities,
                                                                     valueStringsSet, pkbAbstractor);

    delete selectClausePtr;
    for (FilterClause* filterClause : filterClauses) {
        filterClause->free();
        delete filterClause;
    }

    // Return set of values if select clause is not boolean.
    return QueryResult(valueStringsSet);
}


