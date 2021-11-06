#include <set>
#include "FilterResult.h"
#include "WithClause.h"

using pql::WithClause;
using std::set;
using std::unordered_set;
using pql::FilterResult;
using pql::PkbAbstractor;

WithClause::WithClause(QueryArg firstArg, QueryArg secondArg) : firstArg(firstArg), secondArg(secondArg) {
    if (!argIsValid(firstArg) || !argIsValid(secondArg)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("With clause: Invalid arguments");
    }

    if (argIsIntNotString(firstArg) != argIsIntNotString(secondArg)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("With clause: Argument types are different");
    }

    if (firstArg.getQueryDesignEntity() != nullptr) {
        shldReturnFirst = true;
    }
    if (secondArg.getQueryDesignEntity() != nullptr) {
        shldReturnSecond = true;
    }
}

FilterResult WithClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    string procName;
    DesignEntity designEntity;
    AttributeType attributeType;
    DesignEntity returnDesignEntity;
    bool firstArgMustFilter = false;
    bool firstArgIsEntity = false;

    string procName1;
    DesignEntity designEntity1;
    AttributeType attributeType1;
    DesignEntity returnDesignEntity1;
    bool secondArgMustFilter = false;
    bool secondArgIsEntity = false;

    if (firstArg.getQueryArgValue() == nullptr) {
        procName = "";
        designEntity = firstArg.getQueryDesignEntity()->getDesignEntity();
        attributeType = firstArg.getQueryDesignEntity() -> getAttributeType();
        if (attributeType == AttributeType::NONE ||  attributeType == AttributeType::STMT_NUM ||
        designEntity == DesignEntity::CALL || designEntity == DesignEntity::READ ||
        designEntity == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity = firstArg.getQueryDesignEntity()-> getDesignEntity();
        }
        firstArgIsEntity = true;
    } else if (firstArg.getQueryArgValue() != nullptr && firstArg.getQueryDesignEntity() != nullptr) {
        // For when value is specified for an entity
        firstArgMustFilter = true;
        designEntity = firstArg.getQueryDesignEntity()->getDesignEntity();
        attributeType = firstArg.getQueryDesignEntity()->getAttributeType();

        if (attributeType == AttributeType::NONE ||  attributeType == AttributeType::STMT_NUM ||
        designEntity == DesignEntity::CALL || designEntity == DesignEntity::READ ||
        designEntity == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity = firstArg.getQueryDesignEntity()-> getDesignEntity();
        }
        firstArgIsEntity = true;
    } else if (firstArg.getQueryArgValue() != nullptr) {
        procName = firstArg.getQueryArgValue()->getValue();
        designEntity = DesignEntity::NONE;
        attributeType = AttributeType::NONE;
    }

    if (secondArg.getQueryArgValue() == nullptr) {
        procName1 = "";
        designEntity1 = secondArg.getQueryDesignEntity()->getDesignEntity();
        attributeType1 = secondArg.getQueryDesignEntity() -> getAttributeType();
        if (attributeType1 == AttributeType::NONE ||  attributeType1 == AttributeType::STMT_NUM ||
        designEntity1 == DesignEntity::CALL || designEntity1 == DesignEntity::READ ||
        designEntity1 == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity1 = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity1 = secondArg.getQueryDesignEntity()-> getDesignEntity();
        }
        secondArgIsEntity = true;
    } else if (secondArg.getQueryArgValue() != nullptr && secondArg.getQueryDesignEntity() != nullptr) {
        // For when value is specified for an entity
        secondArgMustFilter = true;
        designEntity1 = secondArg.getQueryDesignEntity()->getDesignEntity();
        attributeType1 = secondArg.getQueryDesignEntity()->getAttributeType();

        if (attributeType1 == AttributeType::NONE || attributeType1 == AttributeType::STMT_NUM ||
        designEntity1 == DesignEntity::CALL || designEntity1 == DesignEntity::READ ||
        designEntity1 == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity1 = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity1 = secondArg.getQueryDesignEntity()-> getDesignEntity();
        }
        secondArgIsEntity = true;
    } else if (secondArg.getQueryArgValue() != nullptr) {
        procName1 = secondArg.getQueryArgValue()->getValue();
        designEntity1 = DesignEntity::NONE;
        attributeType1 = AttributeType::NONE;
    }

    list<pair<Value, Value>> pkbResults = {};
    if (firstArgIsEntity && secondArgIsEntity) {
        pkbResults = pkbAbstractor->getWith(designEntity, attributeType, designEntity1, attributeType1);
    } else if (firstArgIsEntity && !secondArgIsEntity) {
        pkbResults = pkbAbstractor->getWith(designEntity, attributeType, procName1);
    } else if (!firstArgIsEntity && secondArgIsEntity) {
        pkbResults = pkbAbstractor->getWith(procName, designEntity1, attributeType1);
    } else if (!firstArgIsEntity && !secondArgIsEntity) {
        pkbResults = pkbAbstractor->getWith(procName, procName1);
    }

    pkbResults = filterPkbResults(pkbResults, firstArgMustFilter, secondArgMustFilter);

    if (pkbResults.empty()) {
        return FilterResult({}, false);
    }

    if (!shldReturnFirst && !shldReturnSecond) {
        return FilterResult({}, true);
    } else if (!shldReturnSecond) {
        set<Value> matchedProcNames = {};
        for (pair<Value, Value> pkbResult: pkbResults) {
            matchedProcNames.insert(pkbResult.first);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto procNameIter = matchedProcNames.begin(); procNameIter != matchedProcNames.end(); ++procNameIter) {
            QueryArgValue value(returnDesignEntity, *procNameIter);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.getQueryDesignEntity(), value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else if (!shldReturnFirst) {
        set<Value> matchedProcNames = {};
        for (pair<Value, Value> pkbResult: pkbResults) {
            matchedProcNames.insert(pkbResult.second);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto procNameIter = matchedProcNames.begin(); procNameIter != matchedProcNames.end(); ++procNameIter) {
            QueryArgValue value(returnDesignEntity1, *procNameIter);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.getQueryDesignEntity(), value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        // If first and second design entity synonym are different.
        if (*firstArg.getQueryDesignEntity() != *secondArg.getQueryDesignEntity()) {
            vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
            for (pair<Value, Value> pkbResult: pkbResults) {
                QueryArgValue valueFirstArg(returnDesignEntity, pkbResult.first);
                QueryArgValue valueSecondArg(returnDesignEntity1, pkbResult.second);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.getQueryDesignEntity(),
                                                                                      valueFirstArg);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg = pair(*secondArg.getQueryDesignEntity(),
                                                                                       valueSecondArg);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg,
                                                                                       entityValuePairSecondArg};
                results.push_back(vectorOfEntityValues);
            }
            return FilterResult(results, true);
        } else {
            // If first and second design entity synonym are the same, only return value for one of the args.
            vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
            for (pair<Value, Value> pkbResult: pkbResults) {
                if (pkbResult.first != pkbResult.second) {
                    continue;
                }
                QueryArgValue valueFirstArg(returnDesignEntity, pkbResult.first);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.getQueryDesignEntity(),
                                                                                      valueFirstArg);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg};
                results.push_back(vectorOfEntityValues);
            }
            if (results.empty()) {
                return FilterResult(results, false);
            }
            return FilterResult(results, true);
        }
    }
}

bool WithClause::argIsValid(QueryArg arg) {
    // If design entity has no attribute, ensure it is only prog line (may pass var, constant, etc)
    QueryDesignEntity* queryDesignEntity = arg.getQueryDesignEntity();
    if (queryDesignEntity != nullptr) {
        if (queryDesignEntity->getAttributeType() == AttributeType::NONE &&
        queryDesignEntity->getDesignEntity() != DesignEntity::PROGRAM_LINE) {
            return false;
        }
    }

    if (arg.isWildCardArg()) {
        return false;
    }
    return true;
}

bool WithClause::argIsIntNotString(QueryArg arg) {
    // Ensure both args are same type (both string or int)
    bool argIsIntNotString = true;
    QueryDesignEntity* queryDesignEntity = arg.getQueryDesignEntity();
    if (queryDesignEntity != nullptr) {
        AttributeType attributeType = queryDesignEntity->getAttributeType();
        if (attributeType == AttributeType::VARIABLE_NAME ||
        attributeType == AttributeType::PROCEDURE_NAME) {
            argIsIntNotString = false;
        }
    }

    QueryArgValue* argValue = arg.getQueryArgValue();
    if (argValue != nullptr) {
        DesignEntity designEntity = argValue->getDesignEntity();
        if (designEntity == DesignEntity::PROCEDURE ||
        designEntity == DesignEntity::VARIABLE) {
            argIsIntNotString = false;
        }
    }
    return argIsIntNotString;
}

list<pair<Value, Value>> WithClause::filterPkbResults(list<pair<Value, Value>> pkbResults, bool firstArgMustFilter,
                                                      bool secondArgMustFilter) {
    if (firstArgMustFilter) {
        list<pair<Value, Value>> newPkbResults = {};
        string firstArgValue = firstArg.getQueryArgValue()->getValue();
        for (pair<Value, Value> pkbResult : pkbResults) {
            if (pkbResult.first == firstArgValue) {
                newPkbResults.push_back(pkbResult);
            }
        }
        pkbResults = newPkbResults;
    }

    if (secondArgMustFilter) {
        list<pair<Value, Value>> newPkbResults = {};
        string secondArgValue = secondArg.getQueryArgValue()->getValue();
        for (pair<Value, Value> pkbResult : pkbResults) {
            if (pkbResult.second == secondArgValue) {
                newPkbResults.push_back(pkbResult);
            }
        }
        pkbResults = newPkbResults;
    }
    return pkbResults;
}