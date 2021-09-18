#include "ModifiesClause.h"
#include <set>

using std::unordered_set;
using std::set;
using std::string;
using pql::FilterResult;
using pql::ModifiesClause;
using pql::PkbAbstractor;

ModifiesClause::ModifiesClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if (firstArg.isWildCard) {
        throw "Modifies Clause: First argument cannot be a wildcard";
    }

    if ((firstArg.queryDesignEntity != nullptr &&
         (firstArg.queryDesignEntity->designEntity == DesignEntity::VARIABLE ||
          firstArg.queryDesignEntity->designEntity == DesignEntity::CONSTANT)) ||
        (firstArg.argValue != nullptr &&
         (firstArg.argValue->designEntity == DesignEntity::VARIABLE ||
          firstArg.argValue->designEntity == DesignEntity::CONSTANT))) {
        throw "Modifies Clause: First argument cannot be a variable or constant";
    }

    if ((secondArg.queryDesignEntity != nullptr &&
         secondArg.queryDesignEntity->designEntity != DesignEntity::VARIABLE) ||
        (secondArg.argValue != nullptr && secondArg.argValue->designEntity != DesignEntity::VARIABLE)) {
        throw "Modifies Clause: Second argument must be a variable";
    }
}

FilterResult ModifiesClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    string value;
    DesignEntity designEntity;
    bool shldReturnFirst = false;

    string variable;
    bool shldReturnSecond = false;

    if (firstArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }

    if (secondArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }

    if (firstArg.isWildCard) {
        value = "";
        designEntity = DesignEntity::NONE;
    } else if (firstArg.argValue == nullptr) {
        value = "";
        designEntity = firstArg.queryDesignEntity->designEntity;
    } else if (firstArg.argValue != nullptr) {
        value = firstArg.argValue->value;
        designEntity = DesignEntity::NONE;
    }

    if (secondArg.isWildCard) {
        variable = "";
    } else if (secondArg.argValue == nullptr) {
        variable = "";
    } else if (secondArg.argValue != nullptr) {
        variable = secondArg.argValue->value;
    }

    list<pair<Value, std::unordered_set<VarName>>> pkbResults = pkbAbstractor->getDataFromModifies(value, designEntity,
                                                                                                   variable);

    if (pkbResults.empty()) {
        return FilterResult({}, false);
    }

    if (!shldReturnFirst && !shldReturnSecond) {
        return FilterResult({}, true);
    } else if (!shldReturnFirst) {
        unordered_set<string> matchedVariables = {};
        for (pair<Value, std::unordered_set<VarName>> pkbResult: pkbResults) {
            matchedVariables.insert(pkbResult.second.begin(), pkbResult.second.end());
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto stmtNum = matchedVariables.begin(); stmtNum != matchedVariables.end(); ++stmtNum) {
            QueryArgValue value(DesignEntity::VARIABLE, *stmtNum);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else if (!shldReturnSecond) {
        unordered_set<string> matchedStmtNumsOrProcedures = {};
        for (pair<Value, std::unordered_set<VarName>> pkbResult: pkbResults) {
            matchedStmtNumsOrProcedures.insert(pkbResult.first);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto matchedValue = matchedStmtNumsOrProcedures.begin();
             matchedValue != matchedStmtNumsOrProcedures.end(); ++matchedValue) {
            QueryArgValue value(DesignEntity::STMT, *matchedValue);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (pair<Value, std::unordered_set<VarName>> pkbResult: pkbResults) {
            DesignEntity firstArgValueDesignEntity;
            if (firstArg.queryDesignEntity->designEntity == DesignEntity::PROCEDURE) {
                firstArgValueDesignEntity = DesignEntity::PROCEDURE;
            } else {
                firstArgValueDesignEntity = DesignEntity::STMT;
            }
            QueryArgValue valueFirstArg(firstArgValueDesignEntity, pkbResult.first);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.queryDesignEntity,
                                                                                  valueFirstArg);
            for (
                auto matchedSecondArgValue = pkbResult.second.begin();
                matchedSecondArgValue != pkbResult.second.end();
                ++matchedSecondArgValue
            ) {
                QueryArgValue argValue(DesignEntity::VARIABLE, *matchedSecondArgValue);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg
                        = pair(*secondArg.queryDesignEntity, argValue);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues
                        = { entityValuePairFirstArg, entityValuePairSecondArg };
                results.push_back(vectorOfEntityValues);
            }
        }
        return FilterResult(results, true);
    }
}
