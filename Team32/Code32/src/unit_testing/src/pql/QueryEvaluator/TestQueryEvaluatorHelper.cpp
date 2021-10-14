#include "catch.hpp"

#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "pql/QueryEvaluator/QueryEvaluatorHelper.h"
#include "Stubs/PkbAbstractorStub.cpp"
#include "Stubs/QueryResultProjectorStub.cpp"
#include "Stubs/SelectClauseStub.cpp"
#include "Stubs/SuchThatClauseStub.cpp"

using pql::AttributeType;
using pql::Query;
using pql::QueryEvaluator;
using pql::QueryEvaluatorHelper;
using pql::QueryEvaluatorResult;
using pql::DesignEntity;
using pql::FilterClause;
using pql::QueryDesignEntity;
using qetest::PkbAbstractorStub;
using qetest::QueryResultProjectorStub;
using qetest::SelectClauseStub;
using qetest::SuchThatClauseStub;

TEST_CASE("Query Evaluator Helper should update usedVariablesMap correctly", "[QueryEvaluatorHelper]") {
    PkbAbstractorStub pkbAbs;

    SECTION("should return empty map if usedVariablesMap and filterClauses are empty") {
        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap = {};
        std::vector<FilterClause*> filterClausesLeftVector = {};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap,
                                                 filterClausesLeftVector, &pkbAbs);
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> resultVector = {};
        QueryEvaluatorResult expectedResult = {resultVector};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should update empty usedVariablesMap with values if filter clause provide matches") {
        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap = {};

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult =
                pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult =
                pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub->addResults(results);

        std::vector<FilterClause*> filterClausesLeftVector = {suchThatClauseStub};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap,
                                                 filterClausesLeftVector, &pkbAbs);
        QueryEvaluatorResult expectedResult = {{{stmtSNameAndResult, varNameAndResult}}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should return usedVariablesMap argument if filter clauses vector is empty") {
        // {(stmt s, 1)} in usedVariablesMap. No clauses. Should return [{(stmt s, 1)}].
        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity* qde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* qav = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(*qde, *qav);
        usedVariablesMap.insert(entityAndValuePair);
        std::vector<FilterClause*> filterClausesLeftVector = {};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap,
                                                 filterClausesLeftVector, &pkbAbs);
        QueryEvaluatorResult expectedResult = {{{entityAndValuePair}}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should update non-empty usedVariablesMap with values if clause provides matches") {
        // {(stmt s, 1), (stmt s1, 2)} in usedVariablesMap.
        // Clause returns the match {(stmt s, 1), (var v, "a")}.
        // Since stmt s = 1 matches, given var v = "a", var v = "a" should be added to usedVariablesMap.
        // Should return [{(stmt s, 1), (stmt s1, 2), (var v, "a")}].
        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity* qde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* qav = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(*qde, *qav);
        usedVariablesMap.insert(entityAndValuePair);

        QueryDesignEntity* qde1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryArgValue* qav1 = new QueryArgValue(DesignEntity::STMT, "2");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair1 = pair<QueryDesignEntity, QueryArgValue>(*qde1, *qav1);
        usedVariablesMap.insert(entityAndValuePair1);

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult =
                pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult =
                pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub->addResults(results);

        std::vector<FilterClause*> filterClausesLeftVector = {suchThatClauseStub};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap,
                                                 filterClausesLeftVector, &pkbAbs);
        QueryEvaluatorResult expectedResult =
                {{{entityAndValuePair, entityAndValuePair1, varNameAndResult}}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should return updated usedVariableMap if clause has match") {
        // usedVariablesMap is empty, clause returns the match {(stmt s, 1), (var v, "a")}.
        // Return value should be [{(stmt s, 1), (var v, "a")}].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub->addResults(results);

        std::vector<FilterClause*> filterClausesLeftVector = {suchThatClauseStub};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        QueryEvaluatorResult expectedResult = {{{stmtSNameAndResult, varNameAndResult}}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should pass query with Such That and Pattern") {
        // usedVariablesMap {(stmt s, 1), (stmt s1, 2)}.
        // First clause returns the match {(stmt s, 1), (var v, "a")}.
        // Second clause returns the match {(stmt s1, 2), (var v, "a")}
        // Return value should be [{(stmt s, 1), (stmt s1, 2), (var v, "a")}].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity* qde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* qav = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(*qde, *qav);
        usedVariablesMap.insert(entityAndValuePair);

        QueryDesignEntity* qde1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryArgValue* qav1 = new QueryArgValue(DesignEntity::STMT, "2");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair1 = pair<QueryDesignEntity, QueryArgValue>(*qde1, *qav1);
        usedVariablesMap.insert(entityAndValuePair1);

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub->addResults(results);

        // Set up such that clause that returns (Stmt s1, 2), (Var v, a) as match.
        QueryDesignEntity* stmtSQde1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryArgValue* stmtSResult1 = new QueryArgValue(DesignEntity::STMT, "2");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde1, *stmtSResult1);
        QueryArg queryArgStmtS1(stmtSQde1, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmtS1, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results1 = {{stmtSNameAndResult1, varNameAndResult}};
        suchThatClauseStub1->addResults(results1);

        std::vector<FilterClause*> filterClausesLeftVector = {suchThatClauseStub, suchThatClauseStub1};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        QueryEvaluatorResult expectedResult = {{{stmtSNameAndResult, stmtSNameAndResult1, varNameAndResult}}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should return empty vector if clauses fail to match") {
        // usedVariablesMap {(stmt s, 1), (stmt s1, 2)}.
        // First clause returns the match {(stmt s1, 2), (var v, "a")}.
        // Second clause returns the match {}.
        // Return value should be [].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity* qde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* qav = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(*qde, *qav);
        usedVariablesMap.insert(entityAndValuePair);

        QueryDesignEntity* qde1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryArgValue* qav1 = new QueryArgValue(DesignEntity::STMT, "2");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair1 = pair<QueryDesignEntity, QueryArgValue>(*qde1, *qav1);
        usedVariablesMap.insert(entityAndValuePair1);

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub->addResults(results);

        // Set up such that clause that returns (Stmt s1, 2), (Var v, a) as match.
        QueryDesignEntity* stmtSQde1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryArgValue* stmtSResult1 = new QueryArgValue(DesignEntity::STMT, "2");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde1, *stmtSResult1);
        QueryArg queryArgStmtS1(stmtSQde1, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmtS1, queryArgVarV);

        std::vector<FilterClause*> filterClausesLeftVector = {suchThatClauseStub, suchThatClauseStub1};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        QueryEvaluatorResult expectedResult = {false};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should pass with clause that returns multiple matches") {
        // usedVariablesMap {(stmt s, 1)}.
        // Clause contains [{(stmt s, 1), (var v, "a")}, {(stmt s, 1), (var v, "b")}] as data.
        // Will return the entire data as both items match with entity in usedVariablesMap.
        // Return value should be [{(stmt s, 1), (var v, "a")}, {(stmt s, 1), (var v, "b")}].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity* qde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* qav = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(*qde, *qav);
        usedVariablesMap.insert(entityAndValuePair);

        // Set up such that clause that returns [{(stmt s, 1), (var v, "a")}, {(stmt s, 1), (var v, "b")}] as match.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);

        QueryArgValue* varResult1 = new QueryArgValue(DesignEntity::VARIABLE, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult1);

        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results =
                {{stmtSNameAndResult, varNameAndResult}, {stmtSNameAndResult, varNameAndResult1}};
        suchThatClauseStub->addResults(results);

        std::vector<FilterClause*> filterClausesLeftVector = {suchThatClauseStub};
        QueryEvaluatorResult startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        QueryEvaluatorResult expectedResult =
                {{{stmtSNameAndResult, varNameAndResult}, {stmtSNameAndResult, varNameAndResult1}}};
        REQUIRE(startQueryResult == expectedResult);
    }
}

TEST_CASE("Query evaluator helper should return all entity values", "[QueryEvaluatorHelper]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("Query evaluator helper should return all stmt design entities (assign/call/if/while/etc)") {
        pkbAbsStub.resultStmtList = {1,2,3};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> obtainedResult = QueryEvaluatorHelper::getAllValuesOfEntities({assignA}, &pkbAbsStub);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue stmt2(DesignEntity::STMT, "2");
        QueryArgValue stmt3(DesignEntity::STMT, "3");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> expectedResult = {{assignA, {stmt1, stmt2, stmt3}}};

        // Convert the values from vectors to sets to ensure equality works.
        unordered_map<QueryDesignEntity, set<QueryArgValue>> obtainedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            obtainedResultWithSetValue.insert({it->first, newSet});
        }
        unordered_map<QueryDesignEntity, set<QueryArgValue>> expectedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            expectedResultWithSetValue.insert({it->first, newSet});
        }
        REQUIRE(obtainedResultWithSetValue == expectedResultWithSetValue);
    }

    SECTION("Query evaluator helper should return all values (procedure/variables/constants)") {
        pkbAbsStub.resultStrList = {"1", "2", "3"};
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> obtainedResult = QueryEvaluatorHelper::getAllValuesOfEntities({constantC}, &pkbAbsStub);
        QueryArgValue constant1(DesignEntity::CONSTANT, "1");
        QueryArgValue constant2(DesignEntity::CONSTANT, "2");
        QueryArgValue constant3(DesignEntity::CONSTANT, "3");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> expectedResult = {{constantC, {constant1, constant2, constant3}}};

        // Convert the values from vectors to sets to ensure equality works.
        unordered_map<QueryDesignEntity, set<QueryArgValue>> obtainedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            obtainedResultWithSetValue.insert({it->first, newSet});
        }
        unordered_map<QueryDesignEntity, set<QueryArgValue>> expectedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            expectedResultWithSetValue.insert({it->first, newSet});
        }
        REQUIRE(obtainedResultWithSetValue == expectedResultWithSetValue);
    }

    SECTION("Query evaluator helper should return all stmts") {
        pkbAbsStub.largestStmtNum = 3;
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> obtainedResult = QueryEvaluatorHelper::getAllValuesOfEntities({stmtS}, &pkbAbsStub);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue stmt2(DesignEntity::STMT, "2");
        QueryArgValue stmt3(DesignEntity::STMT, "3");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> expectedResult = {{stmtS, {stmt1, stmt2, stmt3}}};

        // Convert the values from vectors to sets to ensure equality works.
        unordered_map<QueryDesignEntity, set<QueryArgValue>> obtainedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            obtainedResultWithSetValue.insert({it->first, newSet});
        }
        unordered_map<QueryDesignEntity, set<QueryArgValue>> expectedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            expectedResultWithSetValue.insert({it->first, newSet});
        }
        REQUIRE(obtainedResultWithSetValue == expectedResultWithSetValue);
    }

    SECTION("Query evaluator helper should return all values of design entities") {
        pkbAbsStub.largestStmtNum = 3;
        pkbAbsStub.resultStmtList = {1,2,3};
        pkbAbsStub.resultStrList = {"1", "2", "3"};
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> obtainedResult = QueryEvaluatorHelper::getAllValuesOfEntities({stmtS, constantC, assignA}, &pkbAbsStub);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue stmt2(DesignEntity::STMT, "2");
        QueryArgValue stmt3(DesignEntity::STMT, "3");
        QueryArgValue constant1(DesignEntity::CONSTANT, "1");
        QueryArgValue constant2(DesignEntity::CONSTANT, "2");
        QueryArgValue constant3(DesignEntity::CONSTANT, "3");
        unordered_map<QueryDesignEntity, vector<QueryArgValue>> expectedResult = {{stmtS, {stmt1, stmt2, stmt3}},
                                                                                  {constantC, {constant1, constant2, constant3}},
                                                                                  {assignA, {stmt1, stmt2, stmt3}}};

        // Convert the values from vectors to sets to ensure equality works.
        unordered_map<QueryDesignEntity, set<QueryArgValue>> obtainedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            obtainedResultWithSetValue.insert({it->first, newSet});
        }
        unordered_map<QueryDesignEntity, set<QueryArgValue>> expectedResultWithSetValue = {};
        for (auto it = obtainedResult.begin(); it != obtainedResult.end(); it++) {
            vector<QueryArgValue> currentValues = it->second;
            set<QueryArgValue> newSet(currentValues.begin(), currentValues.end());
            expectedResultWithSetValue.insert({it->first, newSet});
        }
        REQUIRE(obtainedResultWithSetValue == expectedResultWithSetValue);
    }
}

TEST_CASE("should return correct results for updateResultWithAttrVals", "[QueryEvaluatorHelper]") {
    PkbAbstractorStub pkbAbstractorStub;
    SECTION("should not fail with empty design enitity vector and empty valueStringSet") {
        pkbAbstractorStub.resultValList = {};
        set<vector<string>> obtainedResult = QueryEvaluatorHelper::updateResultWithAttrVals({}, {}, &pkbAbstractorStub);
        set<vector<string>> expectedResult = {};
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should not fail with design enitity vector with no attributes and non-empty valueStringSet") {
        pkbAbstractorStub.resultValList = {"a"};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity procP(DesignEntity::PROCEDURE, "p");
        set<vector<string>> obtainedResult = QueryEvaluatorHelper::updateResultWithAttrVals({assignA, procP}, {{"1", "main"}, {"2", "main"}}, &pkbAbstractorStub);
        set<vector<string>> expectedResult = {{"1", "main"}, {"2", "main"}};
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should not fail with design enitity vector with attributes and non-empty valueStringSet") {
        pkbAbstractorStub.resultValList = {"var", "var1"};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a", AttributeType::STMT_NUM);
        QueryDesignEntity readRWithVarNameAttr(DesignEntity::READ, "r", AttributeType::VARIABLE_NAME);
        set<vector<string>> obtainedResult = QueryEvaluatorHelper::updateResultWithAttrVals({assignA, readRWithVarNameAttr}, {{"1", "3"}, {"2", "3"}}, &pkbAbstractorStub);
        set<vector<string>> expectedResult = {{"1", "var"}, {"2", "var1"}};
        REQUIRE(obtainedResult == expectedResult);
    }
}
