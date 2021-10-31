#include <set>
#include "FilterResult.h"
#include "WithClause.h"

using pql::WithClause;
using std::set;
using std::unordered_set;
using pql::FilterResult;
using pql::PkbAbstractor;

WithClause::WithClause(QueryArg firstArg, QueryArg secondArg) : firstArg(firstArg), secondArg(secondArg) {
    // If design entity has no attribute, ensure it is only prog line (may pass var, constant, etc)
    if (firstArg.queryDesignEntity != nullptr) {
        if (firstArg.queryDesignEntity->attributeType == AttributeType::NONE &&
        firstArg.queryDesignEntity->designEntity != DesignEntity::PROGRAM_LINE) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("With clause: Only program line entity allowed for synonyms");
        }
    }

    if (secondArg.queryDesignEntity != nullptr) {
        if (secondArg.queryDesignEntity->attributeType == AttributeType::NONE &&
        secondArg.queryDesignEntity->designEntity != DesignEntity::PROGRAM_LINE) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("With clause: Only program line entity allowed for synonyms");
        }
    }

    // Ensure both are not wildcards
    if (firstArg.isWildCard || secondArg.isWildCard) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("With clause: Wildcards as argument not allowed");
    }

    // Ensure both args are same type (both string or int)
    bool firstArgIsIntNotString = true;
    bool secondArgIsIntNotString = true;

    if (firstArg.queryDesignEntity != nullptr) {
        if (firstArg.queryDesignEntity->attributeType == AttributeType::VARIABLE_NAME ||
        firstArg.queryDesignEntity->attributeType == AttributeType::PROCEDURE_NAME) {
            firstArgIsIntNotString = false;
        }
    }

    if (firstArg.argValue != nullptr) {
        if (firstArg.argValue->designEntity == DesignEntity::PROCEDURE ||
        firstArg.argValue->designEntity == DesignEntity::VARIABLE) {
            firstArgIsIntNotString = false;
        }
    }

    if (secondArg.queryDesignEntity != nullptr) {
        if (secondArg.queryDesignEntity->attributeType == AttributeType::VARIABLE_NAME ||
        secondArg.queryDesignEntity->attributeType == AttributeType::PROCEDURE_NAME) {
            secondArgIsIntNotString = false;
        }
    }

    if (secondArg.argValue != nullptr) {
        if (secondArg.argValue->designEntity == DesignEntity::PROCEDURE ||
        secondArg.argValue->designEntity == DesignEntity::VARIABLE) {
            secondArgIsIntNotString = false;
        }
    }

    if (firstArgIsIntNotString != secondArgIsIntNotString) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("With clause: Argument types are different");
    }

    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}

FilterResult WithClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    string procName;
    DesignEntity designEntity;
    AttributeType attributeType;
    DesignEntity returnDesignEntity;
    bool firstArgMustFilter = false;

    string procName1;
    DesignEntity designEntity1;
    AttributeType attributeType1;
    DesignEntity returnDesignEntity1;
    bool secondArgMustFilter = false;

    if (firstArg.isWildCard) {
        procName = "_";
        designEntity = DesignEntity::NONE;
        attributeType = AttributeType::NONE;
    } else if (firstArg.argValue == nullptr) {
        procName = "";
        designEntity = firstArg.queryDesignEntity->designEntity;
        attributeType = firstArg.queryDesignEntity -> attributeType;
        if (attributeType == AttributeType::NONE ||  attributeType == AttributeType::STMT_NUM ||
        designEntity == DesignEntity::CALL || designEntity == DesignEntity::READ ||
        designEntity == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity = firstArg.queryDesignEntity -> designEntity;
        }
    } else if (firstArg.argValue != nullptr && firstArg.queryDesignEntity != nullptr) {
        // For when value is specified for an entity
        firstArgMustFilter = true;
        designEntity = firstArg.queryDesignEntity->designEntity;
        attributeType = firstArg.queryDesignEntity->attributeType;

        if (attributeType == AttributeType::NONE ||  attributeType == AttributeType::STMT_NUM ||
        designEntity == DesignEntity::CALL || designEntity == DesignEntity::READ ||
        designEntity == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity = firstArg.queryDesignEntity -> designEntity;
        }
    } else if (firstArg.argValue != nullptr) {
        procName = firstArg.argValue->value;
        designEntity = DesignEntity::NONE;
        attributeType = AttributeType::NONE;
    }

    if (secondArg.isWildCard) {
        procName1 = "_";;
        designEntity1 = DesignEntity::NONE;
        attributeType1 = AttributeType::NONE;
    } else if (secondArg.argValue == nullptr) {
        procName1 = "";
        designEntity1 = secondArg.queryDesignEntity->designEntity;
        attributeType1 = secondArg.queryDesignEntity -> attributeType;
        if (attributeType1 == AttributeType::NONE ||  attributeType1 == AttributeType::STMT_NUM ||
        designEntity1 == DesignEntity::CALL || designEntity1 == DesignEntity::READ ||
        designEntity1 == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity1 = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity1 = secondArg.queryDesignEntity -> designEntity;
        }
    } else if (secondArg.argValue != nullptr && secondArg.queryDesignEntity != nullptr) {
        // For when value is specified for an entity
        secondArgMustFilter = true;
        designEntity1 = secondArg.queryDesignEntity->designEntity;
        attributeType1 = secondArg.queryDesignEntity->attributeType;

        if (attributeType1 == AttributeType::NONE || attributeType1 == AttributeType::STMT_NUM ||
        designEntity1 == DesignEntity::CALL || designEntity1 == DesignEntity::READ ||
        designEntity1 == DesignEntity::PRINT) {
            // If entity is prog line or stmt entity
            returnDesignEntity1 = DesignEntity::STMT;
        } else {
            // If entity is constant, procedure, or variable
            returnDesignEntity1 = secondArg.queryDesignEntity -> designEntity;
        }
    } else if (secondArg.argValue != nullptr) {
        procName1 = secondArg.argValue->value;
        designEntity1 = DesignEntity::NONE;
        attributeType1 = AttributeType::NONE;
    }

    list<pair<Value, Value>> pkbResults = pkbAbstractor->getDataFromWith(procName, designEntity, attributeType,
                                                                         procName1, designEntity1, attributeType1);

    if (firstArgMustFilter) {
        list<pair<Value, Value>> newPkbResults = {};
        string firstArgValue = firstArg.argValue->value;
        for (pair<Value, Value> pkbResult : pkbResults) {
            if (pkbResult.first == firstArgValue) {
                newPkbResults.push_back(pkbResult);
            }
        }
        pkbResults = newPkbResults;
    }

    if (secondArgMustFilter) {
        list<pair<Value, Value>> newPkbResults = {};
        string secondArgValue = secondArg.argValue->value;
        for (pair<Value, Value> pkbResult : pkbResults) {
            if (pkbResult.second == secondArgValue) {
                newPkbResults.push_back(pkbResult);
            }
        }
        pkbResults = newPkbResults;
    }

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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.queryDesignEntity, value);
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        // If first and second design entity synonym are different.
        if (*firstArg.queryDesignEntity != *secondArg.queryDesignEntity) {
            vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
            for (pair<Value, Value> pkbResult: pkbResults) {
                QueryArgValue valueFirstArg(returnDesignEntity, pkbResult.first);
                QueryArgValue valueSecondArg(returnDesignEntity1, pkbResult.second);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.queryDesignEntity,
                                                                                      valueFirstArg);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg = pair(*secondArg.queryDesignEntity,
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
                pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.queryDesignEntity,
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