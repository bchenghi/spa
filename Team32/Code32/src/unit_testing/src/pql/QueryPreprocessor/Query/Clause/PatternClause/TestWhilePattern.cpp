#include "catch.hpp"

#include "pql/Errors/SemanticError.h"
#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/PatternClause/WhilePattern.h"

#include <iostream>
#include <string>
#include <vector>

using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::WhilePattern;
using clausetest::PkbAbstractorStub;
using pql::FilterResult;
using std::vector;
using std::string;
using pql::SemanticError;

TEST_CASE("While Pattern Clause PKB Abstractor query", "[AssignmentPattern]") {
    PkbAbstractorStub pkbAbsStub;

    SECTION("should return matches if first argument is wildcard and second is design entity"){
        // WhilePattern(_, v) where v is variable
        // pkb returns {{1, {"var", "var1"}}, {2, {"var1"}}}
        // Expected to return {{(v, "var")}, {(v,"var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}, {2, {"var1"}}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        WhilePattern assignmentPattern(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is wildcard and second is variable"){
        // WhilePattern(_, "var")
        // pkb returns {{1, {"var"}}, {2, {"var"}}}
        // Expected to return {}, has match is true
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var"}}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        WhilePattern whilePattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector =  {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both arguments are wildcards") {
        // WhilePattern(_, _) where v is variable
        // pkb returns {{1, {"var"}}, {2, {"var1"}}}
        // Expected to return {{(v, "var")}, {(v,"var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var1"}}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, nullptr, true);
        WhilePattern whilePattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both args are design entities"){
        // WhilePattern(w, v) where w is assign and v is variable
        // pkb returns {{1, {"var"}}, {2, {"var1"}}}
        // ExpecDesignEntity::WHILEted to return {{(w, 1), (v, "var")}, {(w, 2), (v,"var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var1"}}};
        QueryDesignEntity whileW(DesignEntity::WHILE, "w");
        QueryArg firstArg(&whileW, nullptr, false);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        WhilePattern whilePattern(firstArg, secondArg);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(whileW, assign1),
                                                                                pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(whileW, assign2),
                                                                                pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is variable"){
        // WhilePattern(w, "var", "subtreestr") where v is variable
        // pkb returns {{1, {"var"}}, {2, {"var"}}}
        // Expected to return {{(w, 1)}, {(w, 2)}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var"}}};
        QueryDesignEntity whileW(DesignEntity::WHILE, "w");
        QueryArg firstArg(&whileW, nullptr, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        WhilePattern whilePattern(firstArg, secondArg);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(whileW, assign1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(whileW, assign2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is wildcard"){
        // WhilePattern(w, _, "subtreestr") where v is variable
        // pkb returns {{1, {"var", "var1"}}, {2, {"var1"}}}
        // Expected to return {{(w, 1)}, {(w, 2)}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}, {2, {"var1"}}};
        QueryDesignEntity whileW(DesignEntity::WHILE, "w");
        QueryArg firstArg(&whileW, nullptr, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, nullptr, true);
        WhilePattern whilePattern(firstArg, secondArg);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(whileW, assign1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(whileW, assign2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is design entity"){
        // WhilePattern(1, v, "subtreestr") where v is variable
        // pkb returns {{1, {"var", "var1"}}}
        // Expected to return {{(v, "var")}, {(v, "var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        WhilePattern whilePattern(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is variable name"){
        // WhilePattern(1, "var", "subtreestr") where v is variable
        // pkb returns {{1, {"var"}}}
        // Expected to return {}, has match true
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        WhilePattern whilePattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is wildcard"){
        // WhilePattern(1, _, "subtreestr") where v is variable
        // pkb returns {{1, {"var", "var1"}}}
        // Expected to return {}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        WhilePattern whilePattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = whilePattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }
}

TEST_CASE("While Pattern Clause semantic errors", "[WhilePatternClause]") {
    SECTION("Should throw error if first argument is not if") {
        // WhilePattern(p, v, "_") where p is a procedure v is a variable
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(&variableV, nullptr, false);
        REQUIRE_THROWS_AS(WhilePattern(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is not variable") {
        // WhilePattern(w, 1, "_") where a is an assignment and "1" is a stmt num
        QueryDesignEntity whileW(DesignEntity::WHILE, "w");
        QueryDesignEntity stmtS(DesignEntity::STMT, "1");
        QueryArg firstArg(&whileW, nullptr, false);
        QueryArg secondArg(&stmtS, nullptr, false);
        REQUIRE_THROWS_AS(WhilePattern(firstArg, secondArg), SemanticError);
    }
}
