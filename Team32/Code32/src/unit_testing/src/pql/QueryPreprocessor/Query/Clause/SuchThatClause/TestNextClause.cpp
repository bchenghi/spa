#include "catch.hpp"

#include "pql/Errors/SemanticError.h"
#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/NextClause.h"

using clausetest::PkbAbstractorStub;
using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::NextClause;
using pql::FilterResult;
using pql::SemanticError;

TEST_CASE("Next Clause PKB Abstractor query", "[NextClause]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("should return matches if first argument is wildcard and second is design entity"){
        // Next(_, a) where a is assign
        // Expected to return {{(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,2), pair<int, int>(1,3)};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArg secondArg(&assignA, nullptr, false);
        NextClause nextClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArgValue value3(DesignEntity::STMT, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is wildcard and second is value"){
        // Next(_, "1")
        // Pkbabs returns {(1, 1), (2,1)}
        // Expected to return {}, has match is true
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(2, 1)};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg secondArg(nullptr, &stmt1, false);
        NextClause nextClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both arguments are wildcard"){
        // Next(_, _)
        // pkb abs returns no matches
        // Expected to return {}, has match false
        pkbAbsStub.resultStmtPair = {};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, nullptr, true);
        NextClause nextClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, false);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is design entity"){
        // Next(a, a) where a is assign
        // Pkb abs returns {(1,2), (2,2), (3,3)}
        // Expected to return {{(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,2), pair<int, int>(2, 2), pair<int, int>(3,3)};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(&assignA, nullptr, false);
        NextClause nextClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArgValue value3(DesignEntity::STMT, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is value"){
        // Next(a, 1) where a is assign
        // pkb abs returns {(1,1), (2,1), (3,1)}
        // Expected to return {{(a,1)}, {(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(2,1), pair<int, int>(3,1)};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArgValue value1(DesignEntity::STMT, "1");
        QueryArg secondArg(nullptr, &value1, false);
        NextClause nextClause(firstArg, secondArg);

        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArgValue value3(DesignEntity::STMT, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value1)}, {pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is wildcard"){
        // Next(a, _) where a is assign
        // pkb abs returns {(1,1), (1,2), (2,1)}
        // Expected to return {{(a, 1)}, {(a,2)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(1,2), pair<int, int>(2,1)};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, nullptr, true);
        NextClause nextClause(firstArg, secondArg);
        QueryArgValue value1(DesignEntity::STMT, "1");
        QueryArgValue value2(DesignEntity::STMT, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value1)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is design entity"){
        // Next(1, a) where a is assign
        // pkb abs returns {(1,1), (1,2), (1,3)}
        // Expected to return {{(a, 1)}, {(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(1,2), pair<int, int>(1,3)};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArgValue value1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(&assignA, nullptr, false);
        NextClause nextClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArgValue value3(DesignEntity::STMT, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is value"){
        // Next(1, 2)
        // Expected to return {}, has match true
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,2)};
        QueryArgValue value1(DesignEntity::STMT, "1");
        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(nullptr, &value2, false);
        NextClause nextClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is wildcard"){
        // Next(1, _)
        // pkb abs returns {(1,1), (1,2)}
        // Expected to return {}, has match true
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(1,2)};
        QueryArgValue value1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        NextClause nextClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = nextClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }
}
TEST_CASE("Next Clause semantic errors", "[NextClause]") {
    SECTION("Should throw error if first argument is a variable") {
        // Next(v, 1) where v is a variable
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArgValue stmtValue1(DesignEntity::STMT, "1");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_AS(NextClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a procedure") {
        // Next(p, 1) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryArgValue stmtValue1(DesignEntity::STMT, "1");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_AS(NextClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a constant") {
        // Next(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        QueryArgValue stmtValue1(DesignEntity::STMT, "1");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_AS(NextClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a variable") {
        // Next(1, v) where v is a variable
        QueryArgValue stmtValue1(DesignEntity::STMT, "1");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&variableV, nullptr, true);
        REQUIRE_THROWS_AS(NextClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a procedure") {
        // Next(1, p) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryArgValue stmtValue1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&procedureP, nullptr, false);
        REQUIRE_THROWS_AS(NextClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a constant") {
        // Next(1, c) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        QueryArgValue stmtValue1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_AS(NextClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if both arguments are of invalid design entities") {
        // Next("main", c) where "main" is a procedure and c is a constant.
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        QueryArgValue procedureMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_AS(NextClause(firstArg, secondArg), SemanticError);
    }
}
