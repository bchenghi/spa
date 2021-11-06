#include "AffectsClause.h"
#include <set>

using pql::AffectsClause;
using pql::FilterResult;
using pql::PkbAbstractor;

AffectsClause::AffectsClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if (!SyntaxCheck::isStmtRef(firstArg) || !SyntaxCheck::isStmtRef(secondArg)) {
        throw "Affects Clause: arguments do not match the grammar.";
    }

    if (!argIsValid(firstArg) || !argIsValid(secondArg)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Affects Clause: Argument must be assignment, stmt or program line");
    }
}

FilterResult AffectsClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    int stmtNum1;

    if (firstArg.isWildCardArg()) {
        stmtNum = 0;
    } else if (firstArg.getQueryArgValue() == nullptr) {
        stmtNum = 0;
    } else if (firstArg.getQueryArgValue() != nullptr) {
        stmtNum = std::stoi(firstArg.getQueryArgValue()->getValue());
    }

    if (secondArg.isWildCardArg()) {
        stmtNum1 = 0;
    } else if (secondArg.getQueryArgValue() == nullptr) {
        stmtNum1 = 0;
    } else if (secondArg.getQueryArgValue() != nullptr) {
        stmtNum1 = std::stoi(secondArg.getQueryArgValue()->getValue());
    }

    list<pair<StmtNum, StmtNum>> pkbResults = pkbAbstractor->getAffects(stmtNum, stmtNum1);

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

bool AffectsClause::argIsValid(QueryArg arg) {
    QueryDesignEntity* queryDesignEntity = arg.getQueryDesignEntity();
    if (queryDesignEntity != nullptr) {
        DesignEntity designEntity = queryDesignEntity->getDesignEntity();
        if (designEntity != DesignEntity::ASSIGN && designEntity != DesignEntity::STMT &&
        designEntity != DesignEntity::PROGRAM_LINE) {
            return false;
        }
    }
    QueryArgValue* argValue = arg.getQueryArgValue();
    if (argValue != nullptr &&
    argValue->getDesignEntity() != DesignEntity::STMT) {
        return false;
    }
    return true;
}
