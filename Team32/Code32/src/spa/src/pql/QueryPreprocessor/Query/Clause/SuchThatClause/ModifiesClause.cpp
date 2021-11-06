#include "ModifiesClause.h"
#include <set>

using std::unordered_set;
using std::set;
using std::string;
using pql::FilterResult;
using pql::ModifiesClause;
using pql::PkbAbstractor;

ModifiesClause::ModifiesClause(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg) {
    if (!SyntaxCheck::isEntRef(secondArg)) {
        throw "Modifies Clause: arguments do not match the grammar.";
    }

    if (firstArg.isWildCardArg()) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Modifies Clause: First argument cannot be a wildcard");
    }

    QueryArgValue* firstQueryArgValue = firstArg.getQueryArgValue();
    if (firstQueryArgValue != nullptr &&
    firstQueryArgValue->getDesignEntity() == DesignEntity::VARIABLE) {
        firstQueryArgValue->setDesignEntity(DesignEntity::PROCEDURE);
    }

    QueryDesignEntity* firstQueryDesignEntity = firstArg.getQueryDesignEntity();
    if (firstQueryDesignEntity != nullptr) {
        DesignEntity designEntity = firstQueryDesignEntity->getDesignEntity();
        if (designEntity == DesignEntity::VARIABLE ||
        designEntity == DesignEntity::CONSTANT) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Modifies Clause: First argument cannot be a variable or constant");
        }
    }

    QueryDesignEntity* secondQueryDesignEntity = secondArg.getQueryDesignEntity();
    QueryArgValue* secondQueryArgValue = secondArg.getQueryArgValue();
    if ((secondQueryDesignEntity != nullptr &&
    secondQueryDesignEntity->getDesignEntity() != DesignEntity::VARIABLE) ||
    (secondQueryArgValue != nullptr && secondQueryArgValue->getDesignEntity() != DesignEntity::VARIABLE)) {
        if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Modifies Clause: Second argument must be a variable");
    }
}

FilterResult ModifiesClause::executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
    string value;
    DesignEntity designEntity;

    string variable;

    if (firstArg.isWildCardArg()) {
        value = "";
        designEntity = DesignEntity::NONE;
    } else if (firstArg.getQueryArgValue() == nullptr) {
        value = "";
        designEntity = firstArg.getQueryDesignEntity()->getDesignEntity();
    } else if (firstArg.getQueryArgValue() != nullptr) {
        value = firstArg.getQueryArgValue()->getValue();
        designEntity = DesignEntity::NONE;
    }

    if (secondArg.isWildCardArg()) {
        variable = "";
    } else if (secondArg.getQueryArgValue() == nullptr) {
        variable = "";
    } else if (secondArg.getQueryArgValue() != nullptr) {
        variable = secondArg.getQueryArgValue()->getValue();
    }

    list<pair<Value, std::unordered_set<VarName>>> pkbResults = pkbAbstractor->getModifies(value, designEntity,
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*secondArg.getQueryDesignEntity(), value);
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
            pair<QueryDesignEntity, QueryArgValue> entityValuePair = pair(*firstArg.getQueryDesignEntity(), value);
            vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues = {entityValuePair};
            results.push_back(vectorOfEntityValues);
        }
        return FilterResult(results, true);
    } else {
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;
        for (pair<Value, std::unordered_set<VarName>> pkbResult: pkbResults) {
            DesignEntity firstArgValueDesignEntity;
            if (firstArg.getQueryDesignEntity()->getDesignEntity() == DesignEntity::PROCEDURE) {
                firstArgValueDesignEntity = DesignEntity::PROCEDURE;
            } else {
                firstArgValueDesignEntity = DesignEntity::STMT;
            }
            QueryArgValue valueFirstArg(firstArgValueDesignEntity, pkbResult.first);
            pair<QueryDesignEntity, QueryArgValue> entityValuePairFirstArg = pair(*firstArg.getQueryDesignEntity(),
                                                                                  valueFirstArg);
            for (
                auto matchedSecondArgValue = pkbResult.second.begin();
                matchedSecondArgValue != pkbResult.second.end();
                ++matchedSecondArgValue
            ) {
                QueryArgValue argValue(DesignEntity::VARIABLE, *matchedSecondArgValue);
                pair<QueryDesignEntity, QueryArgValue> entityValuePairSecondArg
                        = pair(*secondArg.getQueryDesignEntity(), argValue);
                vector<pair<QueryDesignEntity, QueryArgValue>> vectorOfEntityValues
                        = { entityValuePairFirstArg, entityValuePairSecondArg };
                results.push_back(vectorOfEntityValues);
            }
        }
        return FilterResult(results, true);
    }
}
