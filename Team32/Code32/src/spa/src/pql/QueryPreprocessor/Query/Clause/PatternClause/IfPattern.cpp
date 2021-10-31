#include "IfPattern.h"
#include <set>
#include <utility>

using std::set;
using std::unordered_set;
using pql::IfPattern;
using pql::FilterResult;
using pql::PkbAbstractor;

IfPattern::IfPattern(QueryArg designEntityArg, QueryArg variableArg) : PatternClause(designEntityArg, variableArg) {
    if (!SyntaxCheck::isEntRef(variableArg)) {
        throw "If Pattern Clause: arguments do not match the grammar.";
    }
    if (designEntityArg.queryDesignEntity != nullptr &&
    designEntityArg.queryDesignEntity->designEntity != DesignEntity::IF) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("If Pattern Clause: First argument must be if");
    }

    if ((variableArg.queryDesignEntity != nullptr && variableArg.queryDesignEntity->designEntity != DesignEntity::VARIABLE) ||
    (variableArg.argValue != nullptr && variableArg.argValue->designEntity != DesignEntity::VARIABLE)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("If Pattern Clause: Second argument must be variable");
    }
    if (designEntityArg.queryDesignEntity != nullptr) {
        shldReturnFirst = true;
    }
    if (variableArg.queryDesignEntity != nullptr) {
        shldReturnSecond = true;
    }
}

FilterResult IfPattern::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    bool shldReturnIf = shldReturnFirst;

    string variable;
    bool shldReturnVariable = shldReturnSecond;

    if (designEntityArg.isWildCard) {
        stmtNum = 0;
    } else if (designEntityArg.argValue == nullptr) {
        stmtNum = 0;
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

    list<pair<StmtNum, std::unordered_set<VarName>>> pkbResults = pkbAbstractor->getIfPattern(stmtNum, variable);

    if (pkbResults.empty()) {
        return FilterResult({}, false);
    }

    if (!shldReturnIf && !shldReturnVariable) {
        return FilterResult({}, true);
    } else if (!shldReturnVariable) {
        set<StmtNum> matchedStmtNums = {};
        for (const pair<StmtNum, std::unordered_set<VarName>>& pkbResult : pkbResults) {
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
    } else if (!shldReturnIf) {
        set<VarName> matchedVariables = {};
        for (const pair<StmtNum, std::unordered_set<VarName>>& pkbResult : pkbResults) {
            matchedVariables.insert(pkbResult.second.begin(), pkbResult.second.end());
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
        for (pair<StmtNum, std::unordered_set<VarName>> pkbResult: pkbResults) {
            DesignEntity firstArgValueDesignEntity = DesignEntity::STMT;
            QueryArgValue valueFirstArg(firstArgValueDesignEntity, std::to_string(pkbResult.first));
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*designEntityArg.queryDesignEntity,
                                                                                  valueFirstArg);
            for (auto matchedSecondArgValue = pkbResult.second.begin();
            matchedSecondArgValue != pkbResult.second.end(); ++matchedSecondArgValue) {
                QueryArgValue argValue(DesignEntity::VARIABLE, *matchedSecondArgValue);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg
                = pair(*variableArg.queryDesignEntity, argValue);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues
                = { entityValuePairFirstArg, entityValuePairSecondArg };
                results.push_back(vectorOfEntityValues);
            }
        }
        return FilterResult(results, true);
    }
}