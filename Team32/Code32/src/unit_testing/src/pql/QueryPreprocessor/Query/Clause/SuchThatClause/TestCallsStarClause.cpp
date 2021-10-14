#include "catch.hpp"

#include "pql/Errors/SemanticError.h"
#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/CallsStarClause.h"

using clausetest::PkbAbstractorStub;
using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::CallsStarClause;
using pql::FilterResult;
using pql::SemanticError;

TEST_CASE("Calls Star Clause PKB Abstractor query", "[CallsStarClause]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("should return matches if first argument is wildcard and second is design entity"){
        // CallsStar(_, p) where p is procedure
        // Pkb abs returns {{"rand", "main"}, {"rand", "main1"}}
        // Expected to return {{(p, main)}, {(p,main1)}}
        pkbAbsStub.resultValPair = {{"rand", "main"}, {"rand", "main1"}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryDesignEntity procP(DesignEntity::PROCEDURE, "p");
        QueryArg secondArg(&procP, nullptr, false);
        CallsStarClause callsClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::PROCEDURE, "main");
        QueryArgValue value3(DesignEntity::PROCEDURE, "main1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(procP, value2)},{pair<QueryDesignEntity, QueryArgValue>(procP, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is wildcard and second is value"){
        // CallsStar(_, "main")
        // Pkbabs returns {{"rand", "main"}, {"rand1", "main"}}
        // Expected to return {}, has match is true
        pkbAbsStub.resultValPair = {{"rand", "main"}, {"rand1", "main"}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArgValue procMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(nullptr, &procMain, false);
        CallsStarClause callsClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both arguments are wildcard"){
        // CallsStar(_, _)
        // pkb abs returns no matches
        // Expected to return {}, has match false
        pkbAbsStub.resultValPair = {};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, nullptr, true);
        CallsStarClause callsClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, false);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is design entity"){
        // CallsStar(p, p) where p is procedure
        // Pkb abs returns {{"main", "main1"}, {"main1", "main1"}, {"main2", "main2"}}
        // Expected to return {{(p, main1)}, {(p, main2)}}
        pkbAbsStub.resultValPair = {{"main", "main1"}, {"main1", "main1"}, {"main2", "main2"}};
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(&procedureP, nullptr, false);
        CallsStarClause callsClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::PROCEDURE, "main1");
        QueryArgValue value3(DesignEntity::PROCEDURE, "main2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(procedureP, value2)},{pair<QueryDesignEntity, QueryArgValue>(procedureP, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is value"){
        // CallsStar(p, main) where p is procedure
        // pkb abs returns {{"main", "main"}, {"main1", "main"},{"main2", "main"}}
        // Expected to return {{(p, "main")}, {(p, "main1")}, {(p, "main2")}}
        pkbAbsStub.resultValPair = {{"main", "main"}, {"main1", "main"},{"main2", "main"}};
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArgValue value1(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(nullptr, &value1, false);
        CallsStarClause callsClause(firstArg, secondArg);

        QueryArgValue value2(DesignEntity::PROCEDURE, "main1");
        QueryArgValue value3(DesignEntity::PROCEDURE, "main2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(procedureP, value1)}, {pair<QueryDesignEntity, QueryArgValue>(procedureP, value2)},{pair<QueryDesignEntity, QueryArgValue>(procedureP, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is wildcard"){
        // CallsStar(p, _) where p is procedure
        // pkb abs returns {{"main", "main"}, {"main", "main1"},{"main1", "main"}}
        // Expected to return {{(p, "main")}, {(p, "main1")}}
        pkbAbsStub.resultValPair = {{"main", "main"}, {"main", "main1"},{"main1", "main"}};
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(nullptr, nullptr, true);
        CallsStarClause callsClause(firstArg, secondArg);
        QueryArgValue value1(DesignEntity::PROCEDURE, "main");
        QueryArgValue value2(DesignEntity::PROCEDURE, "main1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(procedureP, value1)},{pair<QueryDesignEntity, QueryArgValue>(procedureP, value2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is design entity"){
        // CallsStar("main", p) where p is procedure
        // pkb abs returns {{"main", "main"}, {"main", "main1"},{"main", "main2"}}
        // Expected to return {{(p, main)}, {(p, main1)}, {(p, main2)}}
        pkbAbsStub.resultValPair = {{"main", "main"}, {"main", "main1"},{"main", "main2"}};
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryArgValue value1(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(&procedureP, nullptr, false);
        CallsStarClause callsClause(firstArg, secondArg);
        QueryArgValue value2(DesignEntity::PROCEDURE, "main1");
        QueryArgValue value3(DesignEntity::PROCEDURE, "main2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(procedureP, value1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(procedureP, value2)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(procedureP, value3)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is value"){
        // CallsStar(main, main1)
        // Expected to return {}, has match true
        pkbAbsStub.resultValPair = {{"main", "main1"}};
        QueryArgValue value1(DesignEntity::PROCEDURE, "main");
        QueryArgValue value2(DesignEntity::PROCEDURE, "main1");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(nullptr, &value2, false);
        CallsStarClause callsClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is value and second is wildcard"){
        // CallsStar(main, _)
        // pkb abs returns {(main, main1), (main, main2)}
        // Expected to return {}, has match true
        pkbAbsStub.resultValPair = {{"main", "main1"}, {"main", "main2"}};
        QueryArgValue value1(DesignEntity::PROCEDURE, "proc");
        QueryArg firstArg(nullptr, &value1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        CallsStarClause callsClause(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = callsClause.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }
}

TEST_CASE("Calls Star Clause semantic errors", "[CallsStarClause]") {
    SECTION("Should throw error if first argument is a assign") {
        // CallsStar(a, 1) where a is a procedure
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a call") {
        // CallsStar(c, 1) where c is calls
        QueryDesignEntity callsC(DesignEntity::CALL, "c");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&callsC, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a constant") {
        // CallsStar(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a if") {
        // CallsStar(i, 1) where i is a if.
        QueryDesignEntity ifI(DesignEntity::IF, "i");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&ifI, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a print") {
        // CallsStar(p, 1) where p is a print.
        QueryDesignEntity printP(DesignEntity::PRINT, "p");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&printP, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a program line") {
        // CallsStar(p, 1) where p is a program line.
        QueryDesignEntity programLineP(DesignEntity::PROGRAM_LINE, "p");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&programLineP, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a read") {
        // CallsStar(r, 1) where r is a read.
        QueryDesignEntity readR(DesignEntity::READ, "r");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&readR, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a stmt") {
        // CallsStar(s, 1) where s is a stmt.
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&stmtS, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a variable") {
        // CallsStar(v, 1) where v is a variable
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if first argument is a while") {
        // CallsStar(w, 1) where w is a while.
        QueryDesignEntity whileW(DesignEntity::WHILE, "w");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg firstArg(&whileW, nullptr, false);
        QueryArg secondArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a assign") {
        // CallsStar(a, 1) where a is a procedure
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&assignA, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a call") {
        // CallsStar(c, 1) where c is calls
        QueryDesignEntity callsC(DesignEntity::CALL, "c");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&callsC, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a constant") {
        // CallsStar(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::CONSTANT, "c");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&constantC, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a if") {
        // CallsStar(i, 1) where i is a if.
        QueryDesignEntity ifI(DesignEntity::IF, "i");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&ifI, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a print") {
        // CallsStar(p, 1) where p is a print.
        QueryDesignEntity printP(DesignEntity::PRINT, "p");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&printP, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a program line") {
        // CallsStar(p, 1) where p is a program line.
        QueryDesignEntity programLineP(DesignEntity::PROGRAM_LINE, "p");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&programLineP, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a read") {
        // CallsStar(r, 1) where r is a read.
        QueryDesignEntity readR(DesignEntity::READ, "r");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&readR, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a stmt") {
        // CallsStar(s, 1) where s is a stmt.
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&stmtS, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a variable") {
        // CallsStar(v, 1) where v is a variable
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&variableV, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is a while") {
        // CallsStar(w, 1) where w is a while.
        QueryDesignEntity whileW(DesignEntity::WHILE, "w");
        QueryArgValue procValueMain(DesignEntity::PROCEDURE, "main");
        QueryArg secondArg(&whileW, nullptr, false);
        QueryArg firstArg(nullptr, &procValueMain, false);
        REQUIRE_THROWS_AS(CallsStarClause(firstArg, secondArg), SemanticError);
    }
}
