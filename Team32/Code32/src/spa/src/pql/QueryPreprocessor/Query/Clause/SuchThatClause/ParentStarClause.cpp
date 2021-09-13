#include "ParentStarClause.h"
#include <set>

using std::unordered_set;
using std::set;
using pql::FilterResult;
using pql::ParentStarClause;
using pql::PkbAbstractor;

ParentStarClause::ParentStarClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if ((firstArg.queryDesignEntity != nullptr &&
    (firstArg.queryDesignEntity->designEntity == DesignEntity::Variable ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::Constant ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::Procedure)) ||
    (firstArg.argValue != nullptr &&
    (firstArg.argValue->designEntity == DesignEntity::Variable ||
    firstArg.argValue->designEntity == DesignEntity::Constant||
    firstArg.argValue->designEntity == DesignEntity::Procedure))) {
        throw "Parent Star Clause: First argument cannot be a variable, constant or procedure";
    }
    if ((secondArg.queryDesignEntity != nullptr &&
    (secondArg.queryDesignEntity->designEntity == DesignEntity::Variable ||
    secondArg.queryDesignEntity->designEntity == DesignEntity::Constant ||
    secondArg.queryDesignEntity->designEntity == DesignEntity::Procedure)) ||
    (secondArg.argValue != nullptr &&
    (secondArg.argValue->designEntity == DesignEntity::Variable ||
    secondArg.argValue->designEntity == DesignEntity::Constant||
    secondArg.argValue->designEntity == DesignEntity::Procedure))) {
        throw "Parent Star Clause: Second argument cannot be a variable, constant or procedure";
    }
}

FilterResult ParentStarClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    DesignEntity designEntity;
    bool shldReturnFirst = false;
    int stmtNum1;
    DesignEntity designEntity1;
    bool shldReturnSecond = false;

    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }

    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }

    if (firstArg.isWildCard) {
        stmtNum = -1;
        designEntity = DesignEntity::None;
    } else if (firstArg.argValue == nullptr) {
        stmtNum = -1;
        designEntity = firstArg.queryDesignEntity->designEntity;
    } else if (firstArg.argValue != nullptr) {
        stmtNum = std::stoi(firstArg.argValue->value);
        designEntity = firstArg.argValue->designEntity;
    }

    if (secondArg.isWildCard) {
        stmtNum1 = -1;
        designEntity1 = DesignEntity::None;
    } else if (secondArg.argValue == nullptr) {
        stmtNum1 = -1;
        designEntity1 = secondArg.queryDesignEntity->designEntity;
    } else if (secondArg.argValue != nullptr) {
        stmtNum1 = std::stoi(secondArg.argValue->value);
        designEntity1 = secondArg.argValue->designEntity;
    }

    list<pair<StmtNum, StmtNum>> pkbResults = pkbAbstractor->getDataFromParentsStar(stmtNum, designEntity, stmtNum1, designEntity1);
    if (!shldReturnFirst && !shldReturnSecond) {
        if (pkbResults.size() > 0) {
            return FilterResult({}, true);
        } else {
            return FilterResult({}, false);
        }
    } else if (!shldReturnSecond) {
        set<StmtNum> matchedStmtNums = {};
        for (pair<StmtNum, StmtNum> pkbResult : pkbResults) {
            matchedStmtNums.insert(pkbResult.first);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto stmtNum = matchedStmtNums.begin(); stmtNum != matchedStmtNums.end(); ++stmtNum) {
            QueryArgValue value(DesignEntity::Stmt, std::to_string(*stmtNum));
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else if (!shldReturnFirst) {
        set<StmtNum> matchedStmtNums = {};
        for (pair<StmtNum, StmtNum> pkbResult : pkbResults) {
            matchedStmtNums.insert(pkbResult.second);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto stmtNum = matchedStmtNums.begin(); stmtNum != matchedStmtNums.end(); ++stmtNum) {
            QueryArgValue value(DesignEntity::Stmt, std::to_string(*stmtNum));
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        // If first and second design entity synonym are different.
        if (firstArg.queryDesignEntity != secondArg.queryDesignEntity) {
            vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
            for (pair<StmtNum, StmtNum> pkbResult : pkbResults) {
                QueryArgValue valueFirstArg(DesignEntity::Stmt, std::to_string(pkbResult.first));
                QueryArgValue valueSecondArg(DesignEntity::Stmt, std::to_string(pkbResult.second));
                pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.queryDesignEntity, valueFirstArg);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg = pair(*secondArg.queryDesignEntity, valueSecondArg);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg, entityValuePairSecondArg};
                results.push_back(vectorOfEntityValues);
            }
            return FilterResult(results, true);
        } else {
            // If first and second design entity synonym are the same, only return value for one of the args.
            vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
            for (pair<StmtNum, StmtNum> pkbResult : pkbResults) {
                if (pkbResult.first != pkbResult.second) {
                    continue;
                }
                QueryArgValue valueFirstArg(DesignEntity::Stmt, std::to_string(pkbResult.first));
                pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.queryDesignEntity, valueFirstArg);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg};
                results.push_back(vectorOfEntityValues);
            }
            return FilterResult(results, true);
        }
    }
}