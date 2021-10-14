#include "catch.hpp"

#include <chrono>
#include "pql/QueryEvaluator/QueryEvaluator.h"
#include "pql/QueryPreprocessor/Query/Clause/SelectClause.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/FollowsClause.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ModifiesClause.h"
#include "pql/PkbAbstractor/PkbAbstractor.h"
#include "Stubs/PkbAbstractorStub.cpp"
#include "Stubs/QueryResultProjectorStub.cpp"
#include "Stubs/SelectClauseStub.cpp"
#include "Stubs/SuchThatClauseStub.cpp"

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using pql::Query;
using pql::QueryEvaluator;
using pql::QueryResult;
using pql::DesignEntity;
using pql::FilterClause;
using pql::QueryDesignEntity;
using pql::FollowsClause;
using pql::ModifiesClause;
using pql::SelectClause;
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
        pair<QueryDesignEntity, QueryArgValue> placeholderEntityAndValue = pair<QueryDesignEntity, QueryArgValue>(*varVQde, *varVResult);
        // [(Variable v, variable "a")]
        vector<pair<QueryDesignEntity, QueryArgValue>> resultVector = {placeholderEntityAndValue, varVNameAndValue};
        suchThatClauseResults.push_back(resultVector);

        // Set up such that clause with its arguments and result of pkb query.
        QueryArgValue* stmtValue11 = new QueryArgValue(DesignEntity::STMT, "11");
        QueryDesignEntity* varVQde1 = new QueryDesignEntity(DesignEntity::VARIABLE, "v");

        QueryArg queryArgStmtS(stmtSQde, nullptr, false);
        QueryArg queryArgStmt11(nullptr, stmtValue11, false);
        QueryArg queryArgVarV(varVQde, nullptr, false);
        QueryArg queryArgVarV1(varVQde1, nullptr, false);

        SuchThatClauseStub* suchThatClauseStub = new SuchThatClauseStub(queryArgStmt11, queryArgVarV);
        suchThatClauseStub->addResults(suchThatClauseResults);

        SuchThatClauseStub* suchThatClauseStub1 = new SuchThatClauseStub(queryArgStmtS, queryArgVarV1);
        suchThatClauseStub1->addResults({});



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

TEST_CASE("test optimisation on evaluator", "[QueryEvaluator]") {
    QueryEvaluator qe;
    SECTION("query with larger intermediate table without optimisation") {
        // stmt s, s1, s2; variable v;
        // select s such that Follows(s, s1) such that Modifies(s2, v) such that follows(s, s2)

        // follows(s, s1) modifies(s2, v) follows(s, s2)
        // without optimisation, there is cartesian product between follows(s, s1) modifies(a, v). Largest intermediate table is 64 rows
        // With optimisation, it should be arranged such that the two follows clause are together. No cartesian product. Largest intermediate table is 8 rows.

        TypeToStmtNumTable::clear();
        FollowTable::clear();
        ModifyTable::clear();
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 2);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 3);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 4);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 5);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 6);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 7);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 8);
        FollowTable::addFollow(1,2);
        FollowTable::addFollow(2,3);
        FollowTable::addFollow(3,4);
        FollowTable::addFollow(4,5);
        FollowTable::addFollow(5,6);
        FollowTable::addFollow(6,7);
        FollowTable::addFollow(7,8);
        ModifyTable::addStmtModify(1,"v");
        ModifyTable::addStmtModify(2,"v");
        ModifyTable::addStmtModify(3,"v");
        ModifyTable::addStmtModify(4,"v");
        ModifyTable::addStmtModify(5,"v");
        ModifyTable::addStmtModify(6,"v");
        ModifyTable::addStmtModify(7,"v");
        ModifyTable::addStmtModify(8,"v");

        QueryDesignEntity* stmtS = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* secondStmtS = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* stmtS1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryDesignEntity* stmtS2 = new QueryDesignEntity(DesignEntity::STMT, "s2");
        QueryDesignEntity* secondStmtS2 = new QueryDesignEntity(DesignEntity::STMT, "s2");
        QueryDesignEntity* varV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");

        QueryArg stmtSArg(stmtS, nullptr, false);
        QueryArg secondStmtSArg(secondStmtS, nullptr, false);
        QueryArg stmtS1Arg(stmtS1, nullptr, false);
        QueryArg varVArg(varV, nullptr, false);
        QueryArg stmtS2Arg(stmtS2, nullptr, false);
        QueryArg secondStmtS2Arg(secondStmtS2, nullptr, false);
        FollowsClause* follows = new FollowsClause(stmtSArg, stmtS1Arg);
        ModifiesClause* modifies = new ModifiesClause(stmtS2Arg, varVArg);
        FollowsClause* secondFollows = new FollowsClause(secondStmtSArg, secondStmtS2Arg);

        vector<QueryDesignEntity> designEntityVector = {*stmtS, *stmtS1, *stmtS2, *varV};
        vector<FilterClause*> filterClauses = {follows, modifies, secondFollows};
        SelectClause* select = new SelectClause({*stmtS});
        Query queryObject(select, designEntityVector, filterClauses);


        steady_clock::time_point beginWithoutOpt = steady_clock::now();

        QueryResult unoptimisedResult = qe.executeQuery(queryObject, false);

        steady_clock::time_point endWithoutOpt = steady_clock::now();

        stmtS = new QueryDesignEntity(DesignEntity::STMT, "s");
        secondStmtS = new QueryDesignEntity(DesignEntity::STMT, "s");
        stmtS1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        stmtS2 = new QueryDesignEntity(DesignEntity::STMT, "s2");
        secondStmtS2 = new QueryDesignEntity(DesignEntity::STMT, "s2");
        varV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");

        stmtSArg = QueryArg(stmtS, nullptr, false);
        secondStmtSArg = QueryArg(secondStmtS, nullptr, false);
        stmtS1Arg = QueryArg(stmtS1, nullptr, false);
        varVArg = QueryArg(varV, nullptr, false);
        stmtS2Arg = QueryArg(stmtS2, nullptr, false);
        secondStmtS2Arg = QueryArg(secondStmtS2, nullptr, false);
        follows = new FollowsClause(stmtSArg, stmtS1Arg);
        modifies = new ModifiesClause(stmtS2Arg, varVArg);
        secondFollows = new FollowsClause(secondStmtSArg, secondStmtS2Arg);

        designEntityVector = {*stmtS, *stmtS1, *stmtS2, *varV};
        filterClauses = {follows, modifies, secondFollows};
        select = new SelectClause({*stmtS});

        queryObject = Query(select, designEntityVector, filterClauses);

        steady_clock::time_point beginWithOpt = steady_clock::now();

        QueryResult optimisedResult = qe.executeQuery(queryObject, true);

        steady_clock::time_point endWithOpt = steady_clock::now();

        std::cout << "Without Optimisation = " <<
        duration_cast<microseconds>(endWithoutOpt - beginWithoutOpt).count() << "[µs], With Optimisation = " <<
        duration_cast<microseconds>(endWithOpt - beginWithOpt).count() << "[µs]" << std::endl;

        TypeToStmtNumTable::clear();
        FollowTable::clear();
        ModifyTable::clear();

        REQUIRE((duration_cast<microseconds>(endWithoutOpt - beginWithoutOpt).count() >
        duration_cast<microseconds>(endWithOpt - beginWithOpt).count() && unoptimisedResult == optimisedResult));
    }

    SECTION("query with entities that are unnecessarily stored without optimisation") {
        // stmt s, s1, s2; variable v;
        // select v such that Modifies(s, v) and Modifies(s1, v) and Modifies(s2, v)
        // without optimisation, s, s1 and s2 are stored, largest intermediate table is 512 rows.
        // with optimisation, s, s1 and s2 are not stored, largest intermediate table is 8 rows.
        TypeToStmtNumTable::clear();
        ModifyTable::clear();

        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 2);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 3);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 4);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 5);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 6);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 7);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 8);
        ModifyTable::addStmtModify(1,"v");
        ModifyTable::addStmtModify(2,"v");
        ModifyTable::addStmtModify(3,"v");
        ModifyTable::addStmtModify(4,"v");
        ModifyTable::addStmtModify(5,"v");
        ModifyTable::addStmtModify(6,"v");
        ModifyTable::addStmtModify(7,"v");
        ModifyTable::addStmtModify(8,"v");

        QueryDesignEntity* stmtS = new QueryDesignEntity(DesignEntity::STMT, "s");
        QueryDesignEntity* stmtS1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        QueryDesignEntity* stmtS2 = new QueryDesignEntity(DesignEntity::STMT, "s2");
        QueryDesignEntity* varV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryDesignEntity* secondVarV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryDesignEntity* thirdVarV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        QueryArg stmtSArg(stmtS, nullptr, false);
        QueryArg stmtS1Arg(stmtS1, nullptr, false);
        QueryArg varVArg(varV, nullptr, false);
        QueryArg secondVarVArg(secondVarV, nullptr, false);
        QueryArg thirdVarVArg(thirdVarV, nullptr, false);
        QueryArg stmtS2Arg(stmtS2, nullptr, false);
        ModifiesClause* modifies = new ModifiesClause(stmtSArg, varVArg);
        ModifiesClause* modifies1 = new ModifiesClause(stmtS1Arg, secondVarVArg);
        ModifiesClause* modifies2 = new ModifiesClause(stmtS2Arg, thirdVarVArg);

        vector<QueryDesignEntity> designEntityVector = {*stmtS, *stmtS1, *stmtS2, *varV};
        vector<FilterClause*> filterClauses = {modifies, modifies1, modifies2};
        SelectClause* select = new SelectClause({*varV});
        Query queryObject(select, designEntityVector, filterClauses);

        steady_clock::time_point beginWithoutOpt = steady_clock::now();

        QueryResult unoptimisedResult = qe.executeQuery(queryObject, false);

        steady_clock::time_point endWithoutOpt = steady_clock::now();

        stmtS = new QueryDesignEntity(DesignEntity::STMT, "s");
        stmtS1 = new QueryDesignEntity(DesignEntity::STMT, "s1");
        stmtS2 = new QueryDesignEntity(DesignEntity::STMT, "s2");
        varV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        secondVarV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");
        thirdVarV = new QueryDesignEntity(DesignEntity::VARIABLE, "v");

        stmtSArg = QueryArg(stmtS, nullptr, false);
        stmtS1Arg = QueryArg(stmtS1, nullptr, false);
        varVArg = QueryArg(varV, nullptr, false);
        secondVarVArg = QueryArg(secondVarV, nullptr, false);
        thirdVarVArg = QueryArg(thirdVarV, nullptr, false);
        stmtS2Arg = QueryArg(stmtS2, nullptr, false);
        modifies = new ModifiesClause(stmtSArg, varVArg);
        modifies1 = new ModifiesClause(stmtS1Arg, secondVarVArg);
        modifies2 = new ModifiesClause(stmtS2Arg, thirdVarVArg);

        designEntityVector = {*stmtS, *stmtS1, *stmtS2, *varV};
        filterClauses = {modifies, modifies1, modifies2};
        select = new SelectClause({*varV});

        queryObject = Query(select, designEntityVector, filterClauses);

        steady_clock::time_point beginWithOpt = steady_clock::now();

        QueryResult optimisedResult = qe.executeQuery(queryObject, true);

        steady_clock::time_point endWithOpt = steady_clock::now();

        std::cout << "Without Optimisation = " <<
        duration_cast<microseconds>(endWithoutOpt - beginWithoutOpt).count() << "[µs], With Optimisation = " <<
        duration_cast<microseconds>(endWithOpt - beginWithOpt).count() << "[µs]" << std::endl;

        TypeToStmtNumTable::clear();
        ModifyTable::clear();

        REQUIRE((duration_cast<microseconds>(endWithoutOpt - beginWithoutOpt).count() >
        duration_cast<microseconds>(endWithOpt - beginWithOpt).count() && unoptimisedResult == optimisedResult));
    }
}