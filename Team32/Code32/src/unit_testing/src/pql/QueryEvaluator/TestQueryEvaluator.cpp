#include "catch.hpp"
#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "Stubs/SuchThatClauseStub.cpp"
#include "Stubs/PkbAbstractorStub.cpp"
#include "Stubs/QueryResultProjectorStub.cpp"
#include "Stubs/SelectClauseStub.cpp"

using pql::Query;
using pql::QueryEvaluator;
using pql::DesignEntity;
using pql::FilterClause;
using pql::QueryDesignEntity;
using pql::PkbAbstractorStub;
using pql::QueryResultProjectorStub;
using pql::SelectClauseStub;
using pql::SuchThatClauseStub;

TEST_CASE("QueryEvaluator", "[query evaluator]") {
    PkbAbstractorStub pkbAbs;
    QueryResultProjectorStub queryResultProjector;
    QueryEvaluator qe(&pkbAbs, &queryResultProjector);


    SECTION("should pass query with no clause") {
        // Stmt s; Select s;

        // Select clause stmt s.
        QueryDesignEntity qde(DesignEntity::Stmt, "s");
        SelectClauseStub select(qde);

        // Modify Select clause stub such that it returns [[(Stmt s, Stmt 1)]]
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> selectClauseResults;
        QueryArgValue selectClauseResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult = pair<QueryDesignEntity, QueryArgValue>(qde, selectClauseResult);
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector = {selectClauseNameAndResult};
        selectClauseResults.push_back(selectClauseResultVector);
        select.addResults(selectClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {qde};
        vector<FilterClause*> filterClauses = {};

        Query query(&select, queryDesignEntities, filterClauses);



        set<string> expectedResult = {"1"};
        REQUIRE(qe.executeQuery(query) == expectedResult);
    }

    SECTION("should pass query with Such That Clause with an argument the selected entity") {
        // Stmt s, Variable v;
        // Select s such that SuchThatClause(s, v);

        // Stmt can be 1, 2 or 3. Clause returns (1, "a") when s = 1, and (2, "b") when s = 2.
        // Expected result is 1 and 2.

        // Select clause 'Stmt s'.
        QueryDesignEntity stmtSQde(DesignEntity::Stmt, "s");
        SelectClauseStub select(stmtSQde);

        // Modify Select clause stub such that it returns [[(Stmt s, Stmt 1)], [(Stmt s, Stmt 2)], [(Stmt s, Stmt 3)]]
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> selectClauseResults;
        QueryArgValue selectClauseResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, selectClauseResult);
        QueryArgValue selectClauseResult1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, selectClauseResult1);
        QueryArgValue selectClauseResult2(DesignEntity::Stmt, "3");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult2 = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, selectClauseResult2);
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector = {selectClauseNameAndResult};
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector1 = {selectClauseNameAndResult1};
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector2 = {selectClauseNameAndResult2};;
        selectClauseResults.push_back(selectClauseResultVector);
        selectClauseResults.push_back(selectClauseResultVector1);
        selectClauseResults.push_back(selectClauseResultVector2);

        select.addResults(selectClauseResults);

        // Such that clause stub returns [[(Stmt s, stmt 1), (Variable v, variable "a")]] when pkb queried with s = 1 as clause arg.
        // [(Stmt s, stmt 2), (Variable v, variable "b")]] when pkb queried with s = 2 in the clause arg.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        QueryArgValue stmtSResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult);
        QueryArgValue stmtSResult1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult1);

        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        QueryArgValue varResult(DesignEntity::Variable, "a");
        QueryArgValue varResult1(DesignEntity::Variable, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {stmtSNameAndResult, varNameAndResult};
        // [(Stmt s, stmt 2), (Variable v, variable "b")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector1 = {stmtSNameAndResult1, varNameAndResult1};
        suchThatClauseResults.push_back(resultVector);
        suchThatClauseResults.push_back(resultVector1);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArg queryArgStmtS(&stmtSQde, nullptr, false);
        QueryArg queryArgVarV(&varVQde, nullptr, false);
        SuchThatClauseStub suchThatClauseStub(queryArgStmtS, queryArgVarV);
        suchThatClauseStub.addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {stmtSQde, varVQde};
        vector<FilterClause*> filterClauses = {&suchThatClauseStub};

        Query queryObject(&select, queryDesignEntities, filterClauses);
        set<string> expectedResult = {"1", "2"};
        set<string> obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should pass with multiple such that clauses") {
        // Stmt s;
        // Select s such that SuchThatClauseStub(s, "b") such that SuchThatClauseStub(s, "a");

        // Stmt can be 1, 2 or 3. Both clauses returns s = 1 as match. Expected result is s = 1.

        // Select clause 'Stmt s'.
        QueryDesignEntity stmtSQde(DesignEntity::Stmt, "s");
        SelectClauseStub select(stmtSQde);

        // Modify Select clause stub such that the possbiel Stmt s values are [[(Stmt s, Stmt 1)], [(Stmt s, Stmt 2)], [(Stmt s, Stmt 3)]]
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> selectClauseResults;
        QueryArgValue selectClauseResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, selectClauseResult);
        QueryArgValue selectClauseResult1(DesignEntity::Stmt, "2");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, selectClauseResult1);
        QueryArgValue selectClauseResult2(DesignEntity::Stmt, "3");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult2 = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, selectClauseResult2);
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector = {selectClauseNameAndResult};
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector1 = {selectClauseNameAndResult1};
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector2 = {selectClauseNameAndResult2};;
        selectClauseResults.push_back(selectClauseResultVector);
        selectClauseResults.push_back(selectClauseResultVector1);
        selectClauseResults.push_back(selectClauseResultVector2);

        select.addResults(selectClauseResults);

        // Returns [[(Stmt s, stmt 1)]] when pkb queried in the 1st clause and 2nd clause.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults1;
        QueryArgValue stmtSResult(DesignEntity::Stmt, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(stmtSQde, stmtSResult);

        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        QueryArgValue varResult(DesignEntity::Variable, "a");
        QueryArgValue varResult1(DesignEntity::Variable, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {stmtSNameAndResult};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArg queryArgStmtS(&stmtSQde, nullptr, false);
        QueryArg queryArgVarV(nullptr, &varResult, false);
        QueryArg queryArgVarV1(nullptr, &varResult1, false);

        SuchThatClauseStub suchThatClauseStub(queryArgStmtS, queryArgVarV);
        suchThatClauseStub.addResults(suchThatClauseResults);

        SuchThatClauseStub suchThatClauseStub1(queryArgStmtS, queryArgVarV1);
        suchThatClauseStub1.addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {stmtSQde, varVQde};
        vector<FilterClause*> filterClauses = {&suchThatClauseStub, &suchThatClauseStub1};

        Query queryObject(&select, queryDesignEntities, filterClauses);
        set<string> expectedResult = {"1"};
        set<string> obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return empty set if clause does not return matches") {
        // Stmt v;
        // Select v such that SuchThatClause(10, v) such tht SuchThatClause(11, v)

        // v can be "a", "b", "c". First clause returns no matches, second returns matches for all 3 v values.
        // Should return empty set.

        // Select clause 'Variable v'.
        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
        SelectClauseStub select(varVQde);

        // Modify Select clause stub such that the possible Var v values are "a", "b", "c"
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> selectClauseResults;
        QueryArgValue selectClauseResult(DesignEntity::Variable, "a");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, selectClauseResult);
        QueryArgValue selectClauseResult1(DesignEntity::Variable, "b");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(varVQde, selectClauseResult1);
        QueryArgValue selectClauseResult2(DesignEntity::Variable, "c");
        pair<QueryDesignEntity, QueryArgValue> selectClauseNameAndResult2 = pair<QueryDesignEntity, QueryArgValue>(varVQde, selectClauseResult2);
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector = {selectClauseNameAndResult};
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector1 = {selectClauseNameAndResult1};
        vector<pair<QueryDesignEntity, QueryArgValue>> selectClauseResultVector2 = {selectClauseNameAndResult2};;
        selectClauseResults.push_back(selectClauseResultVector);
        selectClauseResults.push_back(selectClauseResultVector1);
        selectClauseResults.push_back(selectClauseResultVector2);

        select.addResults(selectClauseResults);

        // Returns [[(Stmt s, stmt 1)]] when pkb queried in the 1st clause and 2nd clause.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults1;
        QueryArgValue varVResult(DesignEntity::Variable, "a");
        pair<QueryDesignEntity, QueryArgValue> varVNameAndValue = pair<QueryDesignEntity, QueryArgValue>(varVQde, varVResult);

//        QueryDesignEntity varVQde(DesignEntity::Variable, "v");
//        QueryArgValue varResult(DesignEntity::Variable, "a");
//        QueryArgValue varResult1(DesignEntity::Variable, "b");
//        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult);
//        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(varVQde, varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {varVNameAndValue};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArgValue stmtValue10(DesignEntity::Stmt, "10");
        QueryArgValue stmtValue11(DesignEntity::Stmt, "11");
        QueryArg queryArgStmt10(nullptr, &stmtValue10, false);
        QueryArg queryArgStmt11(nullptr, &stmtValue11, false);
        QueryArg queryArgVarV(&varVQde, nullptr, false);

        SuchThatClauseStub suchThatClauseStub(queryArgStmt10, queryArgVarV);
        suchThatClauseStub.addResults({});

        SuchThatClauseStub suchThatClauseStub1(queryArgStmt11, queryArgVarV);
        suchThatClauseStub1.addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {varVQde};
        vector<FilterClause*> filterClauses = {&suchThatClauseStub, &suchThatClauseStub1};

        Query queryObject(&select, queryDesignEntities, filterClauses);
        set<string> expectedResult = {};
        set<string> obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }
}

