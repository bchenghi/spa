#include "catch.hpp"

#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "Stubs/PkbAbstractorStub.cpp"
#include "Stubs/QueryResultProjectorStub.cpp"
#include "Stubs/SelectClauseStub.cpp"
#include "Stubs/SuchThatClauseStub.cpp"

using pql::Query;
using pql::QueryEvaluator;
using pql::QueryResult;
using pql::DesignEntity;
using pql::FilterClause;
using pql::QueryDesignEntity;
using qetest::PkbAbstractorStub;
using qetest::QueryResultProjectorStub;
using qetest::SelectClauseStub;
using qetest::SuchThatClauseStub;

TEST_CASE("Query evaluator can return result of query, iter 1", "[QueryEvaluator]") {
    PkbAbstractorStub pkbAbs;
    QueryResultProjectorStub queryResultProjector;
    QueryEvaluator qe(&pkbAbs, &queryResultProjector);


    SECTION("should pass query with no clause") {
        // Stmt s; Select s;

        // Select clause stmt s.
        QueryDesignEntity* qde = new QueryDesignEntity(DesignEntity::STMT, "s");
        SelectClauseStub* select = new SelectClauseStub({*qde});

        // Update Pkb Abstractor to return 1 as largest stmt num
        pkbAbs.largestStmtNum = 1;

        vector<QueryDesignEntity> queryDesignEntities = {*qde};
        vector<FilterClause*> filterClauses = {};

        Query query(select, queryDesignEntities, filterClauses);



        QueryResult expectedResult = {{{"1"}}};
        QueryResult obtainedResult = qe.executeQuery(query);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should pass query with Such That Clause with an argument the selected entity") {
        // Stmt s, Variable v;
        // Select s such that SuchThatClause(s, v);

        // Stmt can be 1, 2 or 3. Clause returns (1, "a") when s = 1, and (2, "b") when s = 2.
        // Expected result is 1 and 2.

        // Select clause 'Stmt s'.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        SelectClauseStub* select = new SelectClauseStub({*stmtSQde});

        pkbAbs.largestStmtNum = 3;

        // Such that clause stub returns [[(Stmt s, stmt 1), (Variable v, variable "a")]] when pkb queried with s = 1 as clause arg.
        // [(Stmt s, stmt 2), (Variable v, variable "b")]] when pkb queried with s = 2 in the clause arg.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryArgValue* stmtSResult1 = new QueryArgValue(DesignEntity::STMT, "2");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult1);

        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        QueryArgValue* varResult1 = new QueryArgValue(DesignEntity::VARIABLE, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {stmtSNameAndResult, varNameAndResult};
        // [(Stmt s, stmt 2), (Variable v, variable "b")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector1 = {stmtSNameAndResult1, varNameAndResult1};
        suchThatClauseResults.push_back(resultVector);
        suchThatClauseResults.push_back(resultVector1);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new qetest::SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        suchThatClauseStub->addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {*stmtSQde, *varVQde};
        vector<FilterClause*> filterClauses = {suchThatClauseStub};

        Query queryObject(select, queryDesignEntities, filterClauses);
        QueryResult expectedResult = {{{"1"}, {"2"}}};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should pass with multiple such that clauses") {
        // Stmt s;
        // Select s such that SuchThatClauseStub(s, "b") such that SuchThatClauseStub(s, "a");

        // Stmt can be 1, 2 or 3. Both clauses returns s = 1 as match. Expected result is s = 1.

        // Select clause 'Stmt s'.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* stmtSQde1 = new QueryDesignEntity(DesignEntity::STMT, "s");
        SelectClauseStub* select = new SelectClauseStub({*stmtSQde});

        pkbAbs.largestStmtNum = 3;

        // Returns [[(Stmt s, stmt 1)]] when pkb queried in the 1st clause and 2nd clause.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults1;
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);

        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        QueryArgValue* varResult1 = new QueryArgValue(DesignEntity::VARIABLE, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {stmtSNameAndResult};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgStmtS1(stmtSQde1, nullptr, false);
        QueryArg queryArgVarV(nullptr, varResult, false);
        QueryArg queryArgVarV1(nullptr, varResult1, false);

        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        suchThatClauseStub->addResults(suchThatClauseResults);

        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmtS1, queryArgVarV1);
        suchThatClauseStub1->addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {*stmtSQde, *varVQde};
        vector<FilterClause*> filterClauses = {suchThatClauseStub, suchThatClauseStub1};

        Query queryObject(select, queryDesignEntities, filterClauses);
        QueryResult expectedResult = {{{"1"}}};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return invalid result if clause does not return matches") {
        // Stmt v;
        // Select v such that SuchThatClause(10, v) such tht SuchThatClause(11, v)

        // v can be "a", "b", "c". First clause returns no matches, second returns matches for only when v = "a".
        // Should return invalid result.

        // Select clause 'Variable v'.
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        SelectClauseStub* select = new SelectClauseStub({*varVQde});

        pkbAbs.varLst = {"a", "b", "c"};

        // Returns [[(Stmt s, stmt 1)]] when pkb queried in the 1st clause and 2nd clause.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults1;
        QueryArgValue* varVResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varVNameAndValue = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varVResult);

        // [(Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {varVNameAndValue};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArgValue* stmtValue10 = new QueryArgValue(DesignEntity::STMT, "10");
        QueryArgValue* stmtValue11 = new QueryArgValue(DesignEntity::STMT, "11");
        QueryArg queryArgStmt10(nullptr, stmtValue10, false);
        QueryArg queryArgStmt11(nullptr, stmtValue11, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);

        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmt10, queryArgVarV);
        suchThatClauseStub->addResults({});

        QueryDesignEntity* varVQde1 = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArg queryArgVarV1(varVQde1, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmt11, queryArgVarV1);
        suchThatClauseStub1->addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {*varVQde};
        vector<FilterClause*> filterClauses = {suchThatClauseStub, suchThatClauseStub1};

        Query queryObject(select, queryDesignEntities, filterClauses);

        set<vector<string>> resultSet = {};
        QueryResult expectedResult = {resultSet};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }
}

TEST_CASE("Query evaluator can return result of query, iter 2", "[QueryEvaluator]") {
    PkbAbstractorStub pkbAbs;
    QueryResultProjectorStub queryResultProjector;
    QueryEvaluator qe(&pkbAbs, &queryResultProjector);


    SECTION("should pass query with no clause, multiple selects") {
        // Stmt s, s1; assign a; Select <s, s1, a>;
        // Stmt can be 1, 2 or 3 and assign can be 1, 2 or 4.

        // Select <s, s1, a>
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* stmtS1Qde = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryDesignEntity* assignAQde = new QueryDesignEntity(DesignEntity::ASSIGN, "a");
        SelectClauseStub* select = new SelectClauseStub({*stmtSQde, *stmtS1Qde, *assignAQde});

        // Update Pkb Abstractor to return 1 as largest stmt num and set the assign stmts to be 1, 2, 4
        pkbAbs.largestStmtNum = 3;
        pkbAbs.resultStmtList = {1,2,4};
        vector<QueryDesignEntity> queryDesignEntities = {*stmtSQde, *stmtS1Qde, *assignAQde};
        vector<FilterClause*> filterClauses = {};

        Query query(select, queryDesignEntities, filterClauses);



        QueryResult expectedResult = {{{"1", "1", "1"}, {"1", "1", "2"}, {"1", "1", "4"},
                                       {"1", "2", "1"}, {"1", "2", "2"}, {"1", "2", "4"},
                                       {"1", "3", "1"}, {"1", "3", "2"}, {"1", "3", "4"},
                                       {"2", "1", "1"}, {"2", "1", "2"}, {"2", "1", "4"},
                                       {"2", "2", "1"}, {"2", "2", "2"}, {"2", "2", "4"},
                                       {"2", "3", "1"}, {"2", "3", "2"}, {"2", "3", "4"},
                                       {"3", "1", "1"}, {"3", "1", "2"}, {"3", "1", "4"},
                                       {"3", "2", "1"}, {"3", "2", "2"}, {"3", "2", "4"},
                                       {"3", "3", "1"}, {"3", "3", "2"}, {"3", "3", "4"}}};
        QueryResult obtainedResult = qe.executeQuery(query);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should pass query with Such That Clause with an argument the selected entity and is a tuple") {
        // Stmt s, s1, Variable v;
        // Select <s1,v> such that SuchThatClause(s, v);

        // Stmt can be 1, 2 or 3. Clause returns (1, "a") when s = 1, and (2, "b") when s = 2.
        // Expected result is (1, a), (1, b), (2, a) and (2, b).

        // Select clause 'Stmt s'.
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "V");
        QueryDesignEntity* stmtS1Qde = new QueryDesignEntity(DesignEntity::STMT, "s1");
        SelectClauseStub* select = new SelectClauseStub({*stmtS1Qde, *varVQde});

        // Pkb abs only used for getting synonym that are selected but not in clauses. (no need for vars)
        pkbAbs.largestStmtNum = 3;

        // Such that clause stub returns [[(Stmt s, stmt 1), (Variable v, variable "a")]] when pkb queried with s = 1 as clause arg.
        // [(Stmt s, stmt 2), (Variable v, variable "b")]] when pkb queried with s = 2 in the clause arg.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);
        QueryArgValue* stmtSResult1 = new QueryArgValue(DesignEntity::STMT, "2");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult1);

        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        QueryArgValue* varResult1 = new QueryArgValue(DesignEntity::VARIABLE, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {stmtSNameAndResult, varNameAndResult};
        // [(Stmt s, stmt 2), (Variable v, variable "b")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector1 = {stmtSNameAndResult1, varNameAndResult1};
        suchThatClauseResults.push_back(resultVector);
        suchThatClauseResults.push_back(resultVector1);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub = new qetest::SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        suchThatClauseStub->addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {*stmtSQde, *stmtS1Qde, *varVQde};
        vector<FilterClause*> filterClauses = {suchThatClauseStub};

        Query queryObject(select, queryDesignEntities, filterClauses);
        QueryResult expectedResult = {{{"1", "a"}, {"1", "b"}, {"2", "a"}, {"2", "b"}, {"3", "a"}, {"3", "b"}}};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should pass with multiple such that clauses") {
        // Stmt s, variable v;
        // Select <v, s> such that SuchThatClauseStub(s, "b") such that SuchThatClauseStub(s, "a");

        // Stmt can be 1, 2 or 3. Both clauses returns s = 1 as match. Expected result is s = 1.

        // Select clause 'Stmt s'.
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* stmtSQde1 = new QueryDesignEntity(DesignEntity::STMT, "s");
        SelectClauseStub* select = new SelectClauseStub({*varVQde, *stmtSQde});

        pkbAbs.largestStmtNum = 3;
        pkbAbs.varLst = {"a", "b"};
        // Returns [[(Stmt s, stmt 1)]] when pkb queried in the 1st clause and 2nd clause.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults1;
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);

        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        QueryArgValue* varResult1 = new QueryArgValue(DesignEntity::VARIABLE, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {stmtSNameAndResult};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgStmtS1(stmtSQde1, nullptr, false);
        QueryArg queryArgVarV(nullptr, varResult, false);
        QueryArg queryArgVarV1(nullptr, varResult1, false);

        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        suchThatClauseStub->addResults(suchThatClauseResults);

        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmtS1, queryArgVarV1);
        suchThatClauseStub1->addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {*stmtSQde, *varVQde};
        vector<FilterClause*> filterClauses = {suchThatClauseStub, suchThatClauseStub1};

        Query queryObject(select, queryDesignEntities, filterClauses);
        QueryResult expectedResult = {{{"a", "1"}, {"b", "1"}}};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return empty set if clause does not return matches") {
        // variable v, stmt s;
        // Select <s,v> such that SuchThatClause(10, v) such tht SuchThatClause(s, v)

        // v can be "a", "b", "c". First clause returns v = "a", second returns no matches
        // Should return invalid result.

        // Select <s, v>'.
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        SelectClauseStub* select = new SelectClauseStub({*stmtSQde, *varVQde});

        pkbAbs.varLst = {"a", "b", "c"};

        // Returns [[(Stmt s, stmt 1)]] when pkb queried in the 1st clause and 2nd clause.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults1;
        QueryArgValue* varVResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        pair<QueryDesignEntity, QueryArgValue> varVNameAndValue = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varVResult);

        // [(Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {varVNameAndValue};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArgValue* stmtValue11 = new QueryArgValue(DesignEntity::STMT, "11");
        QueryArg queryArgStmt10(stmtSQde, nullptr, false);
        QueryArg queryArgStmt11(nullptr, stmtValue11, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);

        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmt10, queryArgVarV);
        suchThatClauseStub->addResults({});

        QueryDesignEntity* varVQde1 = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArg queryArgVarV1(varVQde1, nullptr, false);
        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmt11, queryArgVarV1);
        suchThatClauseStub1->addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {*varVQde, *stmtSQde};
        vector<FilterClause*> filterClauses = {suchThatClauseStub, suchThatClauseStub1};

        Query queryObject(select, queryDesignEntities, filterClauses);

        set<vector<string>> resultSet = {};
        QueryResult expectedResult = {resultSet};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should pass with no clauses with boolean select") {
        // Stmt s
        // Select BOOLEAN;

        // Should return valid

        SelectClauseStub* select = new SelectClauseStub({});
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        vector<QueryDesignEntity> queryDesignEntities = {*stmtSQde};
        vector<FilterClause*> filterClauses = {};

        Query queryObject(select, queryDesignEntities, filterClauses);
        QueryResult expectedResult = {true};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should pass with multiple such that clauses with boolean select") {
        // Stmt s
        // Select BOOLEAN such that SuchThatClauseStub(s, "b") such that SuchThatClauseStub(s, "a");

        // Stmt can be 1, 2 or 3. Both clauses returns s = 1 as match. Expected result is s = 1.

        // Select clause 'Stmt s'.

        SelectClauseStub* select = new SelectClauseStub({});

        pkbAbs.largestStmtNum = 3;
        pkbAbs.varLst = {"a", "b"};

        QueryDesignEntity* varVQde = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryDesignEntity* stmtSQde = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* stmtSQde1 = new QueryDesignEntity(DesignEntity::STMT, "s");
        // Returns [[(Stmt s, stmt 1)]] when pkb queried in the 1st clause and 2nd clause.
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> suchThatClauseResults1;
        QueryArgValue* stmtSResult = new QueryArgValue(DesignEntity::STMT, "1");
        pair<QueryDesignEntity, QueryArgValue> stmtSNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*stmtSQde, *stmtSResult);

        QueryArgValue* varResult = new QueryArgValue(DesignEntity::VARIABLE, "a");
        QueryArgValue* varResult1 = new QueryArgValue(DesignEntity::VARIABLE, "b");
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult);
        pair<QueryDesignEntity, QueryArgValue> varNameAndResult1 = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varResult1);
        // [(Stmt s, stmt 1), (Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {stmtSNameAndResult};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgStmtS1(stmtSQde1, nullptr, false);
        QueryArg queryArgVarV(nullptr, varResult, false);
        QueryArg queryArgVarV1(nullptr, varResult1, false);

        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmtS, queryArgVarV);
        suchThatClauseStub->addResults(suchThatClauseResults);

        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmtS1, queryArgVarV1);
        suchThatClauseStub1->addResults(suchThatClauseResults);

        vector<QueryDesignEntity> queryDesignEntities = {*stmtSQde};
        vector<FilterClause*> filterClauses = {suchThatClauseStub, suchThatClauseStub1};

        Query queryObject(select, queryDesignEntities, filterClauses);
        QueryResult expectedResult = {true};
        QueryResult obtainedResult = qe.executeQuery(queryObject);
        REQUIRE(obtainedResult == expectedResult);
    }
}