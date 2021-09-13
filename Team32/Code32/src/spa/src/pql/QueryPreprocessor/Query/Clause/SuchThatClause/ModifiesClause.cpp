#include "ModifiesClause.h"
#include <set>

using std::unordered_set;
using std::set;
using std::string;
using pql::FilterResult;
using pql::ModifiesClause;
using pql::PkbAbstractor;
ModifiesClause::ModifiesClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg){
    if (firstArg.isWildCard) {
        throw "Modifies Clause: First argument cannot be a wildcard";
    }

    if ((firstArg.queryDesignEntity != nullptr &&
    (firstArg.queryDesignEntity->designEntity == DesignEntity::Variable ||
    firstArg.queryDesignEntity->designEntity == DesignEntity::Constant)) ||
    (firstArg.argValue != nullptr &&
    (firstArg.argValue->designEntity == DesignEntity::Variable ||
    firstArg.argValue->designEntity == DesignEntity::Constant))) {
        throw "Modifies Clause: First argument cannot be a variable or constant";
    }

    if ((secondArg.queryDesignEntity != nullptr && secondArg.queryDesignEntity->designEntity != DesignEntity::Variable) ||
    (secondArg.argValue != nullptr && secondArg.argValue->designEntity != DesignEntity::Variable)) {
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
        designEntity = DesignEntity::None;
    } else if (firstArg.argValue == nullptr) {
        value = "";
        designEntity = firstArg.queryDesignEntity->designEntity;
    } else if (firstArg.argValue != nullptr) {
        value = firstArg.argValue->value;
        designEntity = firstArg.argValue->designEntity;
    }

    if (secondArg.isWildCard) {
        variable = "";
    } else if (secondArg.argValue == nullptr) {
        variable = "";
    } else if (secondArg.argValue != nullptr) {
        variable = secondArg.argValue->value;
    }

    list<pair<Value , std::unordered_set<VAR_NAME>>> pkbResults = pkbAbstractor->getDataFromModifies(value, designEntity, variable);
    if (!shldReturnFirst && !shldReturnSecond) {
        if (pkbResults.size() > 0) {
            return FilterResult({}, true);
        } else {
            return FilterResult({}, false);
        }
    } else if (!shldReturnFirst) {
        unordered_set<string> matchedVariables = {};
        for (pair<Value , std::unordered_set<VAR_NAME>> pkbResult : pkbResults) {
            matchedVariables.insert(pkbResult.second.begin(), pkbResult.second.end());
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto stmtNum = matchedVariables.begin(); stmtNum != matchedVariables.end(); ++stmtNum) {
            QueryArgValue value(DesignEntity::Variable, *stmtNum);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else if (!shldReturnSecond) {
        unordered_set<string> matchedStmtNumsOrProcedures = {};
        for (pair<Value , std::unordered_set<VAR_NAME>> pkbResult : pkbResults) {
            matchedStmtNumsOrProcedures.insert(pkbResult.first);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto matchedValue = matchedStmtNumsOrProcedures.begin(); matchedValue != matchedStmtNumsOrProcedures.end(); ++matchedValue) {
            QueryArgValue value(DesignEntity::Stmt, *matchedValue);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (pair<Value , std::unordered_set<VAR_NAME>> pkbResult : pkbResults) {
            DesignEntity firstArgValueDesignEntity;
            if (firstArg.queryDesignEntity->designEntity == DesignEntity::Procedure) {
                firstArgValueDesignEntity = DesignEntity::Procedure;
            } else {
                firstArgValueDesignEntity = DesignEntity::Stmt;
            }
            QueryArgValue valueFirstArg(firstArgValueDesignEntity, pkbResult.first);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.queryDesignEntity, valueFirstArg);
            for (auto matchedSecondArgValue = pkbResult.second.begin(); matchedSecondArgValue != pkbResult.second.end(); ++matchedSecondArgValue) {
                QueryArgValue value(DesignEntity::Variable, *matchedSecondArgValue);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg = pair(*secondArg.queryDesignEntity, value);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg, entityValuePairSecondArg};
                results.push_back(vectorOfEntityValues);
            }
        }
        return FilterResult(results, true);
    }
}
