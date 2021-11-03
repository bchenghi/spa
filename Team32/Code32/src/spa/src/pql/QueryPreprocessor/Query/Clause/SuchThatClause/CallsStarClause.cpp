#include "CallsStarClause.h"
#include <set>
#include <utility>

using std::set;
using std::unordered_set;
using pql::CallsStarClause;
using pql::FilterResult;
using pql::PkbAbstractor;
CallsStarClause::CallsStarClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if (!SyntaxCheck::isEntRef(firstArg) || !SyntaxCheck::isEntRef(secondArg)) {
        throw "Calls* Clause: arguments do not match the grammar.";
    }

    if (firstArg.getQueryArgValue() != nullptr &&
    firstArg.getQueryArgValue()->getDesignEntity() == DesignEntity::VARIABLE) {
        firstArg.getQueryArgValue()->setDesignEntity(DesignEntity::PROCEDURE);
    }

    if (secondArg.getQueryArgValue() != nullptr &&
    secondArg.getQueryArgValue()->getDesignEntity() == DesignEntity::VARIABLE) {
        secondArg.getQueryArgValue()->setDesignEntity(DesignEntity::PROCEDURE);
    }

    if (!argIsValid(firstArg) || !argIsValid(secondArg)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Calls Star Clause: Argument must be procedure");
    }
}


FilterResult CallsStarClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    string procName;
    string procName1;

    if (firstArg.isWildCardArg()) {
        procName = "_";
    } else if (firstArg.getQueryArgValue() == nullptr) {
        procName = "";
    } else if (firstArg.getQueryArgValue() != nullptr) {
        procName = firstArg.getQueryArgValue()->getValue();
    }

    if (secondArg.isWildCardArg()) {
        procName1 = "_";
    } else if (secondArg.getQueryArgValue() == nullptr) {
        procName1 = "";
    } else if (secondArg.getQueryArgValue() != nullptr) {
        procName1 = secondArg.getQueryArgValue()->getValue();
    }

    list<pair<Value, Value>> pkbResults = pkbAbstractor->getDataFromCallsStar(procName, procName1);

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
            QueryArgValue value(DesignEntity::PROCEDURE, *procNameIter);
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
            QueryArgValue value(DesignEntity::PROCEDURE, *procNameIter);
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
                QueryArgValue valueFirstArg(DesignEntity::PROCEDURE, pkbResult.first);
                QueryArgValue valueSecondArg(DesignEntity::PROCEDURE, pkbResult.second);
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
                QueryArgValue valueFirstArg(DesignEntity::PROCEDURE, pkbResult.first);
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

bool CallsStarClause::argIsValid(QueryArg arg) {
    QueryDesignEntity* queryDesignEntity = arg.getQueryDesignEntity();
    QueryArgValue* argValue = arg.getQueryArgValue();
    if ((queryDesignEntity != nullptr &&
    queryDesignEntity->getDesignEntity() != DesignEntity::PROCEDURE) ||
    (argValue != nullptr &&
    argValue->getDesignEntity() != DesignEntity::PROCEDURE)) {
        return false;
    }
    return true;
}
