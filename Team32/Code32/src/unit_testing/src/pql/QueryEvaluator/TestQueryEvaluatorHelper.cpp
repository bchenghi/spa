#include "catch.hpp"
#include "pql/QueryEvaluator/QueryEvaluatorHelper.h"
#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "Stubs/SuchThatClauseStub.cpp"
#include "Stubs/PkbAbstractorStub.cpp"
#include "Stubs/QueryResultProjectorStub.cpp"
#include "Stubs/SelectClauseStub.cpp"

using pql::Query;
using pql::QueryEvaluator;
using pql::QueryEvaluatorHelper;
using pql::DesignEntity;
using pql::FilterClause;
using pql::QueryDesignEntity;
using pql::PkbAbstractorStub;
using pql::QueryResultProjectorStub;
using pql::SelectClauseStub;
using pql::SuchThatClauseStub;

TEST_CASE("QueryEvaluatorHelper", "[query evaluator helper]") {
    PkbAbstractorStub pkbAbs;
    QueryResultProjectorStub queryResultProjector;
    QueryEvaluatorHelper qeh;

    SECTION("should return usedVariablesMap argument if filter clauses vector is empty") {
        // {(stmt s, 1)} in usedVariablesMap. No clauses. Should return [{(stmt s, 1)}].
        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity qde(DesignEntity::Stmt, "s");
        QueryArgValue qav(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(qde, qav);
        usedVariablesMap.insert(entityAndValuePair);
        std::vector<FilterClause*> filterClausesLeftVector = {};
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQueryResult = QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> expectedResult = {{entityAndValuePair}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should update usedVariablesMap with design entity values if match") {
        // {(stmt s, 1), (stmt s1, 2)} in usedVariablesMap.
        // Clause returns the match {(stmt s, 1), (var v, "a")}.
        // Since stmt s = 1 matches, given var v = "a", var v = "a" should be added to usedVariablesMap.
        // Should return [{(stmt s, 1), (stmt s1, 2), (var v, "a")}].
        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity qde(DesignEntity::Stmt, "s");
        QueryArgValue qav(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(qde, qav);
        usedVariablesMap.insert(entityAndValuePair);

        QueryDesignEntity qde1(DesignEntity::Stmt, "s1");
        QueryArgValue qav1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair1 = pair<QueryDesignEntity, QueryArgValue>(qde1, qav1);
        usedVariablesMap.insert(entityAndValuePair1);

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity stmtSQde(DesignEntity::Stmt, "s");
        QueryArgValue stmtSResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult);
        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        QueryArgValue varResult(DesignEntity::Variable, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);
        QueryArg queryArgStmtS(&stmtSQde, nullptr, false);
        QueryArg queryArgVarV(&varVQde, nullptr, false);
        SuchThatClauseStub suchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub.addResults(results);

        std::vector<FilterClause*> filterClausesLeftVector = {&suchThatClauseStub};
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQueryResult = QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> expectedResult = {{entityAndValuePair, entityAndValuePair1, varNameAndResult}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should return updated usedVariableMap if clause has match") {
        // usedVariablesMap is empty, clause returns the match {(stmt s, 1), (var v, "a")}.
        // Return value should be [{(stmt s, 1), (var v, "a")}].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity stmtSQde(DesignEntity::Stmt, "s");
        QueryArgValue stmtSResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult);
        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        QueryArgValue varResult(DesignEntity::Variable, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);
        QueryArg queryArgStmtS(&stmtSQde, nullptr, false);
        QueryArg queryArgVarV(&varVQde, nullptr, false);
        SuchThatClauseStub suchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub.addResults(results);

        std::vector<FilterClause*> filterClausesLeftVector = {&suchThatClauseStub};
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> expectedResult = {{stmtSNameAndResult, varNameAndResult}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should pass query with Such That and Pattern") {
        // usedVariablesMap {(stmt s, 1), (stmt s1, 2)}.
        // First clause returns the match {(stmt s, 1), (var v, "a")}.
        // Second clause returns the match {(stmt s1, 2), (var v, "a")}
        // Return value should be [{(stmt s, 1), (stmt s1, 2), (var v, "a")}].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity qde(DesignEntity::Stmt, "s");
        QueryArgValue qav(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(qde, qav);
        usedVariablesMap.insert(entityAndValuePair);

        QueryDesignEntity qde1(DesignEntity::Stmt, "s1");
        QueryArgValue qav1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair1 = pair<QueryDesignEntity, QueryArgValue>(qde1, qav1);
        usedVariablesMap.insert(entityAndValuePair1);

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity stmtSQde(DesignEntity::Stmt, "s");
        QueryArgValue stmtSResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult);
        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        QueryArgValue varResult(DesignEntity::Variable, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);
        QueryArg queryArgStmtS(&stmtSQde, nullptr, false);
        QueryArg queryArgVarV(&varVQde, nullptr, false);
        SuchThatClauseStub suchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub.addResults(results);

        // Set up such that clause that returns (Stmt s1, 2), (Var v, a) as match.
        QueryDesignEntity stmtSQde1(DesignEntity::Stmt, "s1");
        QueryArgValue stmtSResult1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(stmtSQde1, stmtSResult1);
        QueryArg queryArgStmtS1(&stmtSQde1, nullptr, false);
        SuchThatClauseStub suchThatClauseStub1(queryArgStmtS1, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results1 = {{stmtSNameAndResult1, varNameAndResult}};
        suchThatClauseStub1.addResults(results1);

        std::vector<FilterClause*> filterClausesLeftVector = {&suchThatClauseStub, &suchThatClauseStub1};
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> expectedResult = {{stmtSNameAndResult, stmtSNameAndResult1, varNameAndResult}};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should return empty vector if clauses fail to match") {
        // usedVariablesMap {(stmt s, 1), (stmt s1, 2)}.
        // First clause returns the match {(stmt s1, 2), (var v, "a")}.
        // Second clause returns the match {}.
        // Return value should be [].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity qde(DesignEntity::Stmt, "s");
        QueryArgValue qav(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(qde, qav);
        usedVariablesMap.insert(entityAndValuePair);

        QueryDesignEntity qde1(DesignEntity::Stmt, "s1");
        QueryArgValue qav1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair1 = pair<QueryDesignEntity, QueryArgValue>(qde1, qav1);
        usedVariablesMap.insert(entityAndValuePair1);

        // Set up such that clause that returns (Stmt s, 1), (Var v, a) as match.
        QueryDesignEntity stmtSQde(DesignEntity::Stmt, "s");
        QueryArgValue stmtSResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult);
        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        QueryArgValue varResult(DesignEntity::Variable, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);
        QueryArg queryArgStmtS(&stmtSQde, nullptr, false);
        QueryArg queryArgVarV(&varVQde, nullptr, false);
        SuchThatClauseStub suchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results = {{stmtSNameAndResult, varNameAndResult}};
        suchThatClauseStub.addResults(results);

        // Set up such that clause that returns (Stmt s1, 2), (Var v, a) as match.
        QueryDesignEntity stmtSQde1(DesignEntity::Stmt, "s1");
        QueryArgValue stmtSResult1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(stmtSQde1, stmtSResult1);
        QueryArg queryArgStmtS1(&stmtSQde1, nullptr, false);
        SuchThatClauseStub suchThatClauseStub1(queryArgStmtS1, queryArgVarV);

        std::vector<FilterClause*> filterClausesLeftVector = {&suchThatClauseStub, &suchThatClauseStub1};
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> expectedResult = {};
        REQUIRE(startQueryResult == expectedResult);
    }

    SECTION("should pass with clause that returns multiple matches") {
        // usedVariablesMap {(stmt s, 1)}.
        // Clause contains [{(stmt s, 1), (var v, "a")}, {(stmt s, 1), (var v, "b")}] as data.
        // Will return the entire data as both items match with entity in usedVariablesMap.
        // Return value should be [{(stmt s, 1), (var v, "a")}, {(stmt s, 1), (var v, "b")}].

        unordered_map<QueryDesignEntity, QueryArgValue> usedVariablesMap;
        QueryDesignEntity qde(DesignEntity::Stmt, "s");
        QueryArgValue qav(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> entityAndValuePair = pair<QueryDesignEntity, QueryArgValue>(qde, qav);
        usedVariablesMap.insert(entityAndValuePair);

        // Set up such that clause that returns [{(stmt s, 1), (var v, "a")}, {(stmt s, 1), (var v, "b")}] as match.
        QueryDesignEntity stmtSQde(DesignEntity::Stmt, "s");
        QueryArgValue stmtSResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult);
        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        QueryArgValue varResult(DesignEntity::Variable, "a");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);

        QueryArgValue varResult1(DesignEntity::Variable, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult1);

        QueryArg queryArgStmtS(&stmtSQde, nullptr, false);
        QueryArg queryArgVarV(&varVQde, nullptr, false);
        SuchThatClauseStub suchThatClauseStub(queryArgStmtS, queryArgVarV);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results =
                {{stmtSNameAndResult, varNameAndResult}, {stmtSNameAndResult, varNameAndResult1}};
        suchThatClauseStub.addResults(results);

        std::vector<FilterClause*> filterClausesLeftVector = {&suchThatClauseStub};
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> startQueryResult =
                QueryEvaluatorHelper::startQuery(usedVariablesMap, filterClausesLeftVector, &pkbAbs);
        vector<unordered_map<QueryDesignEntity, QueryArgValue>> expectedResult = {{stmtSNameAndResult, varNameAndResult}, {stmtSNameAndResult, varNameAndResult1}};
        REQUIRE(startQueryResult == expectedResult);
    }
}

