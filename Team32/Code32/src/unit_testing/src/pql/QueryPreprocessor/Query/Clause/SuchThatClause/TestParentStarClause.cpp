#include "catch.hpp"

#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ParentStarClause.h"

using clausetest::PkbAbstractorStub;
using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::ParentStarClause;
using pql::FilterResult;

TEST_CASE("Parent Star Clause PKB Abstractor query", "[ParentStarClause]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("should return matches if first argument is wildcard and second is design entity"){
        // Follows(_, a) where a is assign
        // Expected to return {{(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,2), pair<int, int>(1,3)};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryArg secondArg(&assignA, nullptr, false);
        ParentStarClause parentStarClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::Stmt, "2");
        QueryArgValue value3(DesignEntity::Stmt, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is wildcard and second is value"){
        // Follows(_, "1")
        // Pkbabs returns {(1, 1), (2,1)}
        // Expected to return {}, has match is true
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(2, 1)};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryArg secondArg(nullptr, &stmt1, false);
        ParentStarClause parentStarClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both arguments are wildcard"){
        // Follows(_, _)
        // pkb abs returns no matches
        // Expected to return {}, has match false
        pkbAbsStub.resultStmtPair = {};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, nullptr, true);
        ParentStarClause parentStarClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, false);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is design entity"){
        // Follows(a, a) where a is assign
        // Pkb abs returns {(1,2), (2,2), (3,3)}
        // Expected to return {{(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,2), pair<int, int>(2, 2), pair<int, int>(3,3)};
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(&assignA, nullptr, false);
        ParentStarClause parentStarClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::Stmt, "2");
        QueryArgValue value3(DesignEntity::Stmt, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is value"){
        // Follows(a, 1) where a is assign
        // pkb abs returns {(1,1), (2,1), (3,1)}
        // Expected to return {{(a,1)}, {(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(2,1), pair<int, int>(3,1)};
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArgValue value1(DesignEntity::Stmt, "1");
        QueryArg secondArg(nullptr, &value1, false);
        ParentStarClause parentStarClause(firstArg, secondArg);

        QueryArgValue value2(DesignEntity::Stmt, "2");
        QueryArgValue value3(DesignEntity::Stmt, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value1)}, {pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is wildcard"){
        // Follows(a, _) where a is assign
        // pkb abs returns {(1,1), (1,2), (2,1)}
        // Expected to return {{(a, 1)}, {(a,2)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(1,2), pair<int, int>(2,1)};
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, nullptr, true);
        ParentStarClause parentStarClause(firstArg, secondArg);
        QueryArgValue value1(DesignEntity::Stmt, "1");
        QueryArgValue value2(DesignEntity::Stmt, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value1)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is design entity"){
        // Follows(1, a) where a is assign
        // pkb abs returns {(1,1), (1,2), (1,3)}
        // Expected to return {{(a, 1)}, {(a, 2)}, {(a,3)}}
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(1,2), pair<int, int>(1,3)};
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryArgValue value1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(&assignA, nullptr, false);
        ParentStarClause parentStarClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::Stmt, "2");
        QueryArgValue value3(DesignEntity::Stmt, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is value"){
        // Follows(1, 2)
        // Expected to return {}, has match true
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,2)};
        QueryArgValue value1(DesignEntity::Stmt, "1");
        QueryArgValue value2(DesignEntity::Stmt, "2");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(nullptr, &value2, false);
        ParentStarClause parentStarClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is wildcard"){
        // Follows(1, _)
        // pkb abs returns {(1,1), (1,2)}
        // Expected to return {}, has match true
        pkbAbsStub.resultStmtPair = {pair<int, int>(1,1), pair<int, int>(1,2)};
        QueryArgValue value1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        ParentStarClause parentStarClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = parentStarClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }
}
TEST_CASE("Parent Star Clause semantic errors", "[ParentStarClause]") {
    SECTION("Should throw error if first argument is a variable") {
        // ParentStar(v, 1) where v is a variable
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(ParentStarClause(firstArg, secondArg), "Parent Star Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if first argument is a procedure") {
        // ParentStar(p, 1) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::Procedure, "p");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(ParentStarClause(firstArg, secondArg), "Parent Star Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if first argument is a constant") {
        // ParentStar(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(ParentStarClause(firstArg, secondArg), "Parent Star Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a variable") {
        // ParentStar(1, v) where v is a variable
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&variableV, nullptr, true);
        REQUIRE_THROWS_WITH(ParentStarClause(firstArg, secondArg), "Parent Star Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a procedure") {
        // ParentStar(1, p) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::Procedure, "p");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&procedureP, nullptr, false);
        REQUIRE_THROWS_WITH(ParentStarClause(firstArg, secondArg), "Parent Star Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a constant") {
        // ParentStar(1, c) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_WITH(ParentStarClause(firstArg, secondArg), "Parent Star Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if both arguments are of invalid design entities") {
        // ParentStar("main", c) where "main" is a procedure and c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue procedureMain(DesignEntity::Procedure, "main");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_WITH(ParentStarClause(firstArg, secondArg), "Parent Star Clause: First argument cannot be a variable, constant or procedure");
    }
}
