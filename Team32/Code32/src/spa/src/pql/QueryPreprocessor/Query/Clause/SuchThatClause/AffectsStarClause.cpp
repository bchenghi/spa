#include "AffectsStarClause.h"
#include <set>

using pql::AffectsStarClause;
using pql::FilterResult;
using pql::PkbAbstractor;

AffectsStarClause::AffectsStarClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if ((firstArg.queryDesignEntity != nullptr &&
    firstArg.queryDesignEntity->designEntity != DesignEntity::ASSIGN &&
    firstArg.queryDesignEntity->designEntity != DesignEntity::STMT &&
    firstArg.queryDesignEntity->designEntity != DesignEntity::PROGRAM_LINE) ||
    (firstArg.argValue != nullptr &&
    firstArg.argValue->designEntity != DesignEntity::STMT)) {
        throw SemanticError("Affects Clause: First argument must be assignment, stmt or program line");
    }

    if ((secondArg.queryDesignEntity != nullptr &&
    secondArg.queryDesignEntity->designEntity != DesignEntity::ASSIGN &&
    secondArg.queryDesignEntity->designEntity != DesignEntity::STMT &&
    secondArg.queryDesignEntity->designEntity != DesignEntity::PROGRAM_LINE) ||
    (secondArg.argValue != nullptr &&
    secondArg.argValue->designEntity != DesignEntity::STMT)) {
        throw SemanticError("Affects Clause: Second argument must be assignment, stmt or program line");
    }

    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}

FilterResult AffectsStarClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    int stmtNum1;

    if (firstArg.isWildCard) {
        stmtNum = 0;
    } else if (firstArg.argValue == nullptr) {
        stmtNum = 0;
    } else if (firstArg.argValue != nullptr) {
        stmtNum = std::stoi(firstArg.argValue->value);
    }

    if (secondArg.isWildCard) {
        stmtNum1 = 0;
    } else if (secondArg.argValue == nullptr) {
        stmtNum1 = 0;
    } else if (secondArg.argValue != nullptr) {
        stmtNum1 = std::stoi(secondArg.argValue->value);
    }

    list<pair<StmtNum, StmtNum>> pkbResults = pkbAbstractor->getDataFromAffectsStar(stmtNum, stmtNum1);

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
