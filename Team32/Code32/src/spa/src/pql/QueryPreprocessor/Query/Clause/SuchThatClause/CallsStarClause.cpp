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

    if (firstArg.argValue != nullptr &&
    firstArg.argValue->designEntity == DesignEntity::VARIABLE) {
        firstArg.argValue->designEntity = DesignEntity::PROCEDURE;
    }

    if (secondArg.argValue != nullptr &&
    secondArg.argValue->designEntity == DesignEntity::VARIABLE) {
        secondArg.argValue->designEntity = DesignEntity::PROCEDURE;
    }

    if ((firstArg.queryDesignEntity != nullptr &&
    firstArg.queryDesignEntity->designEntity != DesignEntity::PROCEDURE) ||
    (firstArg.argValue != nullptr &&
    firstArg.argValue->designEntity != DesignEntity::PROCEDURE)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Calls Star Clause: First argument must be procedure");
    }

    if ((secondArg.queryDesignEntity != nullptr &&
    secondArg.queryDesignEntity->designEntity != DesignEntity::PROCEDURE) ||
    (secondArg.argValue != nullptr &&
    secondArg.argValue->designEntity != DesignEntity::PROCEDURE)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Calls Star Clause: Second argument must be procedure");
    }

    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}


FilterResult CallsStarClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    string procName;
    string procName1;

    if (firstArg.isWildCard) {
        procName = "_";
    } else if (firstArg.argValue == nullptr) {
        procName = "";
    } else if (firstArg.argValue != nullptr) {
        procName = firstArg.argValue->value;
    }

    if (secondArg.isWildCard) {
        procName1 = "_";
    } else if (secondArg.argValue == nullptr) {
        procName1 = "";
    } else if (secondArg.argValue != nullptr) {
        procName1 = secondArg.argValue->value;
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
            QueryArgValue value(DesignEntity::PROCEDURE, *procNameIter);
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
                QueryArgValue valueFirstArg(DesignEntity::PROCEDURE, pkbResult.first);
                QueryArgValue valueSecondArg(DesignEntity::PROCEDURE, pkbResult.second);
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
                QueryArgValue valueFirstArg(DesignEntity::PROCEDURE, pkbResult.first);
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
