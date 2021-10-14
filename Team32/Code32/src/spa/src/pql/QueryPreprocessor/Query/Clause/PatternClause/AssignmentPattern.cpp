#include "AssignmentPattern.h"
#include <set>
#include <utility>

using std::set;
using std::unordered_set;
using pql::AssignmentPattern;
using pql::FilterResult;
using pql::PkbAbstractor;

AssignmentPattern::AssignmentPattern(QueryArg queryDesignEntity, QueryArg variable, std::vector<std::string> postFixStr, bool hasUnderscores)
: PatternClause(queryDesignEntity, variable),  postFixStr(std::move(postFixStr)), hasUnderscores(hasUnderscores)
{
    if (queryDesignEntity.queryDesignEntity != nullptr &&
    queryDesignEntity.queryDesignEntity->designEntity != DesignEntity::ASSIGN) {
        throw SemanticError("Assignment Pattern Clause: First argument must be assignment");
    }

    if ((variable.queryDesignEntity != nullptr && variable.queryDesignEntity->designEntity != DesignEntity::VARIABLE) ||
        (variable.argValue != nullptr && variable.argValue->designEntity != DesignEntity::VARIABLE)) {
        throw SemanticError("Assignment Pattern Clause: Second argument must be variable");
    }
    if (designEntityArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (variableArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}

FilterResult AssignmentPattern::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    bool shldReturnAssign = shldReturnFirst;

    string variable;
    bool shldReturnVariable = shldReturnSecond;

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

    list<pair<StmtNum, VarName>> pkbResults = pkbAbstractor->getAssignPattern(stmtNum, variable, postFixStr,
                                                                              hasUnderscores);

    if (pkbResults.empty()) {
        return FilterResult({}, false);
    }

    if (!shldReturnAssign && !shldReturnVariable) {
        return FilterResult({}, true);
    } else if (!shldReturnVariable) {
        set<StmtNum> matchedStmtNums = {};
        for (const pair<StmtNum, VarName>& pkbResult : pkbResults) {
            matchedStmtNums.insert(pkbResult.first);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (unsigned long matchedStmtNum : matchedStmtNums) {
            QueryArgValue value(DesignEntity::STMT, std::to_string(matchedStmtNum));
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*designEntityArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else if (!shldReturnAssign) {
        set<VarName> matchedVariables = {};
        for (const pair<StmtNum, VarName>& pkbResult : pkbResults) {
            matchedVariables.insert(pkbResult.second);
        }

        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (const auto& matchedVariable : matchedVariables) {
            QueryArgValue value(DesignEntity::VARIABLE, matchedVariable);
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*variableArg.queryDesignEntity, value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (const pair<StmtNum, VarName>& pkbResult : pkbResults) {
            QueryArgValue valueFirstArg(DesignEntity::STMT, std::to_string(pkbResult.first));
            QueryArgValue valueSecondArg(DesignEntity::VARIABLE, pkbResult.second);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*designEntityArg.queryDesignEntity, valueFirstArg);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg = pair(*variableArg.queryDesignEntity, valueSecondArg);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg, entityValuePairSecondArg};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    }
}
