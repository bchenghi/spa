#include "WhilePattern.h"
#include <set>
#include <utility>

using std::set;
using std::unordered_set;
using pql::WhilePattern;
using pql::FilterResult;
using pql::PkbAbstractor;

WhilePattern::WhilePattern(QueryArg designEntityArg, QueryArg variableArg) : PatternClause(designEntityArg, variableArg) {
    if (!SyntaxCheck::isEntRef(variableArg)) {
        throw "While Pattern Clause: arguments do not match the grammar.";
    }

    QueryDesignEntity* whileQueryDesignEntity = designEntityArg.getQueryDesignEntity();
    if (whileQueryDesignEntity != nullptr &&
    whileQueryDesignEntity->getDesignEntity() != DesignEntity::WHILE) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("While Pattern Clause: First argument must be while");
    }

    QueryDesignEntity* varQueryDesignEntity = variableArg.getQueryDesignEntity();
    QueryArgValue* varQueryArgValue = variableArg.getQueryArgValue();
    if ((varQueryDesignEntity != nullptr && varQueryDesignEntity->getDesignEntity() != DesignEntity::VARIABLE) ||
    (varQueryArgValue != nullptr && varQueryArgValue->getDesignEntity() != DesignEntity::VARIABLE)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("While Pattern Clause: Second argument must be variable");
    }
}

FilterResult WhilePattern::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    int stmtNum;
    bool shldReturnIf = shldReturnFirst;

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

    list<pair<StmtNum, std::unordered_set<VarName>>> pkbResults = pkbAbstractor->getWhilePattern(stmtNum, variable);

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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*designEntityArg.getQueryDesignEntity(), value);
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*variableArg.getQueryDesignEntity(), value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (pair<StmtNum, std::unordered_set<VarName>> pkbResult: pkbResults) {
            DesignEntity firstArgValueDesignEntity = DesignEntity::STMT;
            QueryArgValue valueFirstArg(firstArgValueDesignEntity, std::to_string(pkbResult.first));
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*designEntityArg.getQueryDesignEntity(),
                                                                                  valueFirstArg);
            for (auto matchedSecondArgValue = pkbResult.second.begin();
            matchedSecondArgValue != pkbResult.second.end(); ++matchedSecondArgValue) {
                QueryArgValue argValue(DesignEntity::VARIABLE, *matchedSecondArgValue);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg
                = pair(*variableArg.getQueryDesignEntity(), argValue);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues
                = { entityValuePairFirstArg, entityValuePairSecondArg };
                results.push_back(vectorOfEntityValues);
            }
        }
        return FilterResult(results, true);
    }
}
