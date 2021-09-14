#include "AssignmentPattern.h"
#include <set>

using std::set;
using std::unordered_set;
using pql::AssignmentPattern;
using pql::FilterResult;
using pql::PkbAbstractor;

AssignmentPattern::AssignmentPattern(QueryArg queryDesignEntity, QueryArg variable, std::string postFixStr) :
PatternClause(queryDesignEntity, variable, postFixStr) {
    if (queryDesignEntity.queryDesignEntity != nullptr &&
    queryDesignEntity.queryDesignEntity->designEntity != DesignEntity::Assign) {
        throw "Assignment Pattern Clause: First argument must be assignment";
    }

    if ((variable.queryDesignEntity != nullptr && variable.queryDesignEntity->designEntity != DesignEntity::Variable) ||
    (variable.argValue != nullptr && variable.argValue->designEntity != DesignEntity::Variable)) {
        throw "Assignment Pattern Clause: Second argument must be variable";
    }
}

FilterResult AssignmentPattern::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    bool shldReturnAssign = false;

    string variable;
    bool shldReturnVariable = false;

    if (designEntityArg.queryDesignEntity != nullptr) {
        shldReturnAssign = true;
    }

    if (variableArg.queryDesignEntity != nullptr) {
        shldReturnVariable = true;
    }

    if (designEntityArg.isWildCard) {
        stmtNum = -1;
    } else if (designEntityArg.argValue == nullptr) {
        stmtNum = -1;
    } else if (designEntityArg.argValue != nullptr) {
        stmtNum = std::stoi(designEntityArg.argValue->value);
    }

    if (variableArg.isWildCard) {
        variable = "";
    } else if (variableArg.argValue == nullptr) {
        variable = "";
    } else if (variableArg.argValue != nullptr) {
        variable = variableArg.argValue->value;
    }

    list<pair<StmtNum, VarName>> pkbResults = pkbAbstractor->getPattern(stmtNum, variable, postFixStr);

    if (pkbResults.size() == 0) {
        return FilterResult({}, false);
    }

    if (!shldReturnAssign && !shldReturnVariable) {
        return FilterResult({}, true);
    } else if (!shldReturnVariable) {
        set<StmtNum> matchedStmtNums = {};
        for (pair<StmtNum, VarName> pkbResult : pkbResults) {
            matchedStmtNums.insert(pkbResult.first);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto stmtNum = matchedStmtNums.begin(); stmtNum != matchedStmtNums.end(); ++stmtNum) {
            QueryArgValue value(DesignEntity::Stmt, std::to_string(*stmtNum));
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*designEntityArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else if (!shldReturnAssign) {
        set<VarName> matchedVariables = {};
        for (pair<StmtNum, VarName> pkbResult : pkbResults) {
            matchedVariables.insert(pkbResult.second);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (auto varName = matchedVariables.begin(); varName != matchedVariables.end(); ++varName) {
            QueryArgValue value(DesignEntity::Variable, *varName);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*variableArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (pair<StmtNum, VarName> pkbResult : pkbResults) {
            QueryArgValue valueFirstArg(DesignEntity::Stmt, std::to_string(pkbResult.first));
            QueryArgValue valueSecondArg(DesignEntity::Variable, pkbResult.second);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*designEntityArg.queryDesignEntity, valueFirstArg);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg = pair(*variableArg.queryDesignEntity, valueSecondArg);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg, entityValuePairSecondArg};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    }
}
