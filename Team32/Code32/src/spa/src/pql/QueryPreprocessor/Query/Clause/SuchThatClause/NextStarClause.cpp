#include "NextStarClause.h"

#include <set>

using std::set;
using pql::FilterResult;
using pql::NextStarClause;

NextStarClause::NextStarClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if (!SyntaxCheck::isStmtRef(firstArg) || !SyntaxCheck::isStmtRef(secondArg)) {
        throw "Next* Clause: arguments do not match the grammar.";
    }

    if (!argIsValid(firstArg) || !argIsValid(secondArg)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Next Star Clause: Argument cannot be a variable, constant or procedure");
    }
}

FilterResult NextStarClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    DesignEntity designEntity;
    int stmtNum1;
    DesignEntity designEntity1;

    list<pair<StmtNum, StmtNum>> pkbResults;

    if (firstArg.getQueryArgValue() != nullptr && secondArg.getQueryArgValue() != nullptr) {
        // NumNum
        stmtNum = std::stoi(firstArg.getQueryArgValue()->getValue());
        stmtNum1 = std::stoi(secondArg.getQueryArgValue()->getValue());
        pkbResults = pkbAbstractor->getNextStar(stmtNum, stmtNum1);
    } else if (firstArg.getQueryArgValue() != nullptr && secondArg.isWildCardArg()) {
        // NumWildcard
        stmtNum = std::stoi(firstArg.getQueryArgValue()->getValue());
        designEntity1 = DesignEntity::NONE;
        pkbResults = pkbAbstractor->getNextStar(stmtNum, designEntity1);
    } else if (firstArg.getQueryArgValue() != nullptr && secondArg.getQueryArgValue() == nullptr && !secondArg.isWildCardArg()) {
        // NumEntity
        stmtNum = std::stoi(firstArg.getQueryArgValue()->getValue());
        designEntity1 = secondArg.getQueryDesignEntity()->getDesignEntity();
        pkbResults = pkbAbstractor->getNextStar(stmtNum, designEntity1);
    } else if (firstArg.isWildCardArg() && secondArg.getQueryArgValue() != nullptr) {
        // WildcardNum
        designEntity = DesignEntity::NONE;
        stmtNum1 = std::stoi(secondArg.getQueryArgValue()->getValue());
        pkbResults = pkbAbstractor->getNextStar(designEntity, stmtNum1);
    } else if (firstArg.isWildCardArg() && secondArg.isWildCardArg()) {
        // WildcardWildcard
        designEntity = DesignEntity::NONE;
        designEntity1 = DesignEntity::NONE;
        pkbResults = pkbAbstractor->getNextStar(designEntity, designEntity1);
    } else if (firstArg.isWildCardArg() && secondArg.getQueryArgValue() == nullptr && !secondArg.isWildCardArg()) {
        // WildcardEntity
        designEntity = DesignEntity::NONE;
        designEntity1 = secondArg.getQueryDesignEntity()->getDesignEntity();
        pkbResults = pkbAbstractor->getNextStar(designEntity, designEntity1);
    } else if (firstArg.getQueryArgValue() == nullptr && !firstArg.isWildCardArg() && secondArg.getQueryArgValue() != nullptr) {
        // EntityNum
        designEntity = firstArg.getQueryDesignEntity()->getDesignEntity();
        stmtNum1 = std::stoi(secondArg.getQueryArgValue()->getValue());
        pkbResults = pkbAbstractor->getNextStar(designEntity, stmtNum1);
    } else if (firstArg.getQueryArgValue() == nullptr && !firstArg.isWildCardArg() && secondArg.isWildCardArg()) {
        // EntityWildcard
        designEntity = firstArg.getQueryDesignEntity()->getDesignEntity();
        designEntity1 = DesignEntity::NONE;
        pkbResults = pkbAbstractor->getNextStar(designEntity, designEntity1);
    } else if (firstArg.getQueryArgValue() == nullptr && !firstArg.isWildCardArg() && secondArg.getQueryArgValue() == nullptr && !secondArg.isWildCardArg()) {
        // EntityEntity
        designEntity = firstArg.getQueryDesignEntity()->getDesignEntity();
        designEntity1 = secondArg.getQueryDesignEntity()->getDesignEntity();
        pkbResults = pkbAbstractor->getNextStar(designEntity, designEntity1);
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.getQueryDesignEntity(), value);
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.getQueryDesignEntity(), value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        // If first and second design entity synonym are different.
        if (*firstArg.getQueryDesignEntity() != *secondArg.getQueryDesignEntity()) {
            vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
            for (pair<StmtNum, StmtNum> pkbResult: pkbResults) {
                QueryArgValue valueFirstArg(DesignEntity::STMT, std::to_string(pkbResult.first));
                QueryArgValue valueSecondArg(DesignEntity::STMT, std::to_string(pkbResult.second));
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
            for (pair<StmtNum, StmtNum> pkbResult: pkbResults) {
                if (pkbResult.first != pkbResult.second) {
                    continue;
                }
                QueryArgValue valueFirstArg(DesignEntity::STMT, std::to_string(pkbResult.first));
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

bool NextStarClause::argIsValid(QueryArg arg) {
    QueryDesignEntity* queryDesignEntity = arg.getQueryDesignEntity();
    if (queryDesignEntity != nullptr) {
        DesignEntity designEntity = queryDesignEntity->getDesignEntity();
        if (designEntity == DesignEntity::VARIABLE ||
        designEntity == DesignEntity::CONSTANT ||
        designEntity == DesignEntity::PROCEDURE) {
            return false;
        }
    }

    QueryArgValue* argValue = arg.getQueryArgValue();
    if (argValue != nullptr) {
        DesignEntity designEntity = argValue->getDesignEntity();
        if (designEntity == DesignEntity::VARIABLE ||
        designEntity == DesignEntity::CONSTANT ||
        designEntity == DesignEntity::PROCEDURE) {
            return false;
        }
    }
    return true;
}
