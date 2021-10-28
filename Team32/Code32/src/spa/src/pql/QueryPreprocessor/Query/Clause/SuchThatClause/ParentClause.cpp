#include "ParentClause.h"
#include <set>

using std::set;
using std::unordered_set;
using pql::FilterResult;
using pql::ParentClause;
using pql::PkbAbstractor;

ParentClause::ParentClause(QueryArg queryArg, QueryArg queryArg1) : SuchThatClause(queryArg, queryArg1) {
    if ((firstArg.queryDesignEntity != nullptr &&
         (firstArg.queryDesignEntity->designEntity == DesignEntity::VARIABLE ||
          firstArg.queryDesignEntity->designEntity == DesignEntity::CONSTANT ||
          firstArg.queryDesignEntity->designEntity == DesignEntity::PROCEDURE)) ||
        (firstArg.argValue != nullptr &&
         (firstArg.argValue->designEntity == DesignEntity::VARIABLE ||
          firstArg.argValue->designEntity == DesignEntity::CONSTANT ||
          firstArg.argValue->designEntity == DesignEntity::PROCEDURE))) {
        throw SemanticError("Parent Clause: First argument cannot be a variable, constant or procedure");
    }

    if ((secondArg.queryDesignEntity != nullptr &&
         (secondArg.queryDesignEntity->designEntity == DesignEntity::VARIABLE ||
          secondArg.queryDesignEntity->designEntity == DesignEntity::CONSTANT ||
          secondArg.queryDesignEntity->designEntity == DesignEntity::PROCEDURE)) ||
        (secondArg.argValue != nullptr &&
         (secondArg.argValue->designEntity == DesignEntity::VARIABLE ||
          secondArg.argValue->designEntity == DesignEntity::CONSTANT ||
          secondArg.argValue->designEntity == DesignEntity::PROCEDURE))) {
        throw SemanticError("Parent Clause: Second argument cannot be a variable, constant or procedure");
    }
    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}

FilterResult ParentClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    DesignEntity designEntity;
    int stmtNum1;
    DesignEntity designEntity1;

    list<pair<StmtNum, StmtNum>> pkbResults;

    if (firstArg.argValue != nullptr && secondArg.argValue != nullptr) {
        // NumNum
        stmtNum = std::stoi(firstArg.argValue->value);
        stmtNum1 = std::stoi(secondArg.argValue->value);
        pkbResults = pkbAbstractor->getParents(stmtNum, stmtNum1);
    } else if (firstArg.argValue != nullptr && secondArg.isWildCard) {
        // NumWildcard
        stmtNum = std::stoi(firstArg.argValue->value);
        designEntity1 = DesignEntity::NONE;
        pkbResults = pkbAbstractor->getParents(stmtNum, designEntity1);
    } else if (firstArg.argValue != nullptr && secondArg.argValue == nullptr && !secondArg.isWildCard) {
        // NumEntity
        stmtNum = std::stoi(firstArg.argValue->value);
        designEntity1 = secondArg.queryDesignEntity->designEntity;
        pkbResults = pkbAbstractor->getParents(stmtNum, designEntity1);
    } else if (firstArg.isWildCard && secondArg.argValue != nullptr) {
        // WildcardNum
        designEntity = DesignEntity::NONE;
        stmtNum1 = std::stoi(secondArg.argValue->value);
        pkbResults = pkbAbstractor->getParents(designEntity, stmtNum1);
    } else if (firstArg.isWildCard && secondArg.isWildCard) {
        // WildcardWildcard
        designEntity = DesignEntity::NONE;
        designEntity1 = DesignEntity::NONE;
        pkbResults = pkbAbstractor->getParents(designEntity, designEntity1);
    } else if (firstArg.isWildCard && secondArg.argValue == nullptr && !secondArg.isWildCard) {
        // WildcardEntity
        designEntity = DesignEntity::NONE;
        designEntity1 = secondArg.queryDesignEntity->designEntity;
        pkbResults = pkbAbstractor->getParents(designEntity, designEntity1);
    } else if (firstArg.argValue == nullptr && !firstArg.isWildCard && secondArg.argValue != nullptr) {
        // EntityNum
        designEntity = firstArg.queryDesignEntity->designEntity;
        stmtNum1 = std::stoi(secondArg.argValue->value);
        pkbResults = pkbAbstractor->getParents(designEntity, stmtNum1);
    } else if (firstArg.argValue == nullptr && !firstArg.isWildCard && secondArg.isWildCard) {
        // EntityWildcard
        designEntity = firstArg.queryDesignEntity->designEntity;
        designEntity1 = DesignEntity::NONE;
        pkbResults = pkbAbstractor->getParents(designEntity, designEntity1);
    } else if (firstArg.argValue == nullptr && !firstArg.isWildCard && secondArg.argValue == nullptr && !secondArg.isWildCard) {
        // EntityEntity
        designEntity = firstArg.queryDesignEntity->designEntity;
        designEntity1 = secondArg.queryDesignEntity->designEntity;
        pkbResults = pkbAbstractor->getParents(designEntity, designEntity1);
    }

    if (pkbResults.empty()) {
        return FilterResult({}, false);
    }

    if (!shldReturnFirst && !shldReturnSecond) {
        return FilterResult({}, true);
    } else if (!shldReturnSecond) {
        set<StmtNum> matchedStmtNums = {};
        for (pair<StmtNum, StmtNum> pkbResult: pkbResults) {
            matchedStmtNums.insert(pkbResult.first);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto stmtNumIter = matchedStmtNums.begin(); stmtNumIter != matchedStmtNums.end(); ++stmtNumIter) {
            QueryArgValue value(DesignEntity::STMT, std::to_string(*stmtNumIter));
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else if (!shldReturnFirst) {
        set<StmtNum> matchedStmtNums = {};
        for (pair<StmtNum, StmtNum> pkbResult: pkbResults) {
            matchedStmtNums.insert(pkbResult.second);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto stmtNumIter = matchedStmtNums.begin(); stmtNumIter != matchedStmtNums.end(); ++stmtNumIter) {
            QueryArgValue value(DesignEntity::STMT, std::to_string(*stmtNumIter));
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        // If first and second design entity synonym are different.
        if (*firstArg.queryDesignEntity != *secondArg.queryDesignEntity) {
            vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
            for (pair<StmtNum, StmtNum> pkbResult: pkbResults) {
                QueryArgValue valueFirstArg(DesignEntity::STMT, std::to_string(pkbResult.first));
                QueryArgValue valueSecondArg(DesignEntity::STMT, std::to_string(pkbResult.second));
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
            for (pair<StmtNum, StmtNum> pkbResult: pkbResults) {
                if (pkbResult.first != pkbResult.second) {
                    continue;
                }
                QueryArgValue valueFirstArg(DesignEntity::STMT, std::to_string(pkbResult.first));
                pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg
                        = pair(*firstArg.queryDesignEntity, valueFirstArg);
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