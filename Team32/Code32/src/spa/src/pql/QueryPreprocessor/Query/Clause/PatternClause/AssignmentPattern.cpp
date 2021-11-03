#include "AssignmentPattern.h"
#include <set>
#include <utility>

using std::set;
using std::unordered_set;
using pql::AssignmentPattern;
using pql::FilterResult;
using pql::PkbAbstractor;

AssignmentPattern::AssignmentPattern(QueryArg assignmentArg, QueryArg variable, std::vector<std::string> postFixStr, bool hasUnderscores)
: PatternClause(assignmentArg, variable),  postFixStr(std::move(postFixStr)), hasUnderscores(hasUnderscores)
{
    if (!SyntaxCheck::isEntRef(variable)) {
        throw "Assignment Pattern Clause: arguments do not match the grammar.";
    }

    QueryDesignEntity* assignQueryDesignEntity = assignmentArg.getQueryDesignEntity();
    if (assignQueryDesignEntity != nullptr &&
    assignQueryDesignEntity->getDesignEntity() != DesignEntity::ASSIGN) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Assignment Pattern Clause: First argument must be assignment");
    }

    QueryDesignEntity* varQueryDesignEntity = variable.getQueryDesignEntity();
    QueryArgValue* varQueryArgValue = variable.getQueryArgValue();
    if ((varQueryDesignEntity != nullptr && varQueryDesignEntity->getDesignEntity() != DesignEntity::VARIABLE) ||
    (varQueryArgValue != nullptr && varQueryArgValue->getDesignEntity() != DesignEntity::VARIABLE)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Assignment Pattern Clause: Second argument must be variable");
    }

}

FilterResult AssignmentPattern::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    bool shldReturnAssign = shldReturnFirst;

    string variable;
    bool shldReturnVariable = shldReturnSecond;

    if (designEntityArg.isWildCardArg()) {
        stmtNum = 0;
    } else if (designEntityArg.getQueryArgValue() == nullptr) {
        stmtNum = 0;
    } else if (designEntityArg.getQueryArgValue() != nullptr) {
        stmtNum = std::stoi(designEntityArg.getQueryArgValue()->getValue());
    }

    if (variableArg.isWildCardArg()) {
        variable = "";
    } else if (variableArg.getQueryArgValue() == nullptr) {
        variable = "";
    } else if (variableArg.getQueryArgValue() != nullptr) {
        variable = variableArg.getQueryArgValue()->getValue();
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*designEntityArg.getQueryDesignEntity(), value);
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*variableArg.getQueryDesignEntity(), value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (const pair<StmtNum, VarName>& pkbResult : pkbResults) {
            QueryArgValue valueFirstArg(DesignEntity::STMT, std::to_string(pkbResult.first));
            QueryArgValue valueSecondArg(DesignEntity::VARIABLE, pkbResult.second);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*designEntityArg.getQueryDesignEntity(), valueFirstArg);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg = pair(*variableArg.getQueryDesignEntity(), valueSecondArg);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePairFirstArg, entityValuePairSecondArg};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    }
}
