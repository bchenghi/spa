#include "catch.hpp"


#include "pql/Errors/SemanticError.h"
#include "pql/AttributeType.h"
#include "./Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/WithClause.h"

using pql::AttributeType;
using clausetest::PkbAbstractorStub;
using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::WithClause;
using pql::FilterResult;
using pql::SemanticError;

TEST_CASE("With Clause PKB Abstractor query", "[WithClause]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("should return matches if first argument is design entity and second is design entity"){
        // With(a, a) where a is assign
        // Pkb abs returns {(1,2), (2,2), (3,3)}
        // Expected to return {{(a, 2)}, {(a,3)}}
        pkbAbsStub.resultValPair = {{"1","2"}, {"2", "2"},{"3","3"}};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a", AttributeType::STMT_NUM);
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(&assignA, nullptr, false);
        WithClause WithClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArgValue value3(DesignEntity::STMT, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = WithClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is value"){
        // With(a, 1) where a is assign
        // pkb abs returns {(1,1), (2,1), (3,1)}
        // Expected to return {{(a,1)}, {(a, 2)}, {(a,3)}}
        pkbAbsStub.resultValPair = {{"1","1"}, {"2", "1"},{"3","1"}};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a", AttributeType::STMT_NUM);
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArgValue value1(DesignEntity::STMT, "1");
        QueryArg secondArg(nullptr, &value1, false);
        WithClause WithClause(firstArg, secondArg);

        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArgValue value3(DesignEntity::STMT, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, value1)}, {pair<QueryDesignEntity, QueryArgValue>(assignA, value2)},{pair<QueryDesignEntity, QueryArgValue>(assignA, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = WithClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is design entity"){
        // With("rand", p.procName) where p is procedure
        // Pkb abs returns {{"rand", "main"}, {"rand", "main1"}}
        // Expected to return {{(p, main)}, {(p,main1)}}
        pkbAbsStub.resultValPair = {{"rand", "main"}, {"rand", "main1"}};
        QueryArgValue procRand(DesignEntity::PROCEDURE, "rand");
        QueryArg firstArg(nullptr, &procRand, false);
        QueryDesignEntity procP(DesignEntity::PROCEDURE, "p", AttributeType::PROCEDURE_NAME);
        QueryArg secondArg(&procP, nullptr, false);
        WithClause withClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::PROCEDURE, "main");
        QueryArgValue value3(DesignEntity::PROCEDURE, "main1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(procP, value2)},{pair<QueryDesignEntity, QueryArgValue>(procP, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = withClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is value"){
        // With(1, 2)
        // Expected to return {}, has match true
        pkbAbsStub.resultValPair = {{"1", "2"}};
        QueryArgValue value1(DesignEntity::STMT, "1");
        QueryArgValue value2(DesignEntity::STMT, "2");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(nullptr, &value2, false);
        WithClause WithClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = WithClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }
}

TEST_CASE("With Clause semantic errors", "[WithClause]") {
    SECTION("Should throw error if first argument has no attribute and is not program line") {
        // With(a, 1) where a is a assign
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument has no attribute and is not program line") {
        // With("main", c) where c is calls
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryDesignEntity callsC(DesignEntity::CALL, "c");
        QueryArg firstArg(nullptr, &procValueMain, false);
        QueryArg secondArg(&callsC, nullptr, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is int design entity and second argument is string design entity") {
        // With(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c", AttributeType::VALUE);
        QueryDesignEntity procP(DesignEntity::PROCEDURE, "p", AttributeType::PROCEDURE_NAME);
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(&procP, nullptr, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is string design entity and second argument is int design entity") {
        // With(c, 1) where c is a constant.
        QueryDesignEntity procP(DesignEntity::PROCEDURE, "p", AttributeType::PROCEDURE_NAME);
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c", AttributeType::VALUE);
        QueryArg firstArg(&procP, nullptr, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is int value and second argument is string design entity") {
        // With(c, 1) where c is a constant.
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryDesignEntity procP(DesignEntity::PROCEDURE, "p", AttributeType::PROCEDURE_NAME);
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(&procP, nullptr, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is string value and second argument is int design entity") {
        // With(c, 1) where c is a constant.
        QueryArgValue varV(DesignEntity::VARIABLE, "a");
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c", AttributeType::VALUE);
        QueryArg firstArg(nullptr, &varV, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is int design entity and second argument is string value") {
        // With(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c", AttributeType::VALUE);
        QueryArgValue varV(DesignEntity::VARIABLE, "a");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &varV, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is string design entity and second argument is int value") {
        // With(c, 1) where c is a constant.
        QueryDesignEntity procP(DesignEntity::PROCEDURE, "p", AttributeType::PROCEDURE_NAME);
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(&procP, nullptr, false);
        QueryArg secondArg(nullptr, &stmt1, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is int value and second argument is string value") {
        // With(c, 1) where c is a constant.
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArgValue varV(DesignEntity::VARIABLE, "a");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, &varV, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is string value and second argument is int value") {
        // With(c, 1) where c is a constant.
        QueryArgValue varV(DesignEntity::VARIABLE, "a");
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &varV, false);
        QueryArg secondArg(nullptr, &stmt1, false);
        REQUIRE_THROWS_AS(WithClause(firstArg, secondArg), SemanticError);
    }
}
