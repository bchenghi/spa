#include "catch.hpp"

#include "pql/Errors/SemanticError.h"
#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/PatternClause/AssignmentPattern.h"

#include <iostream>
#include <string>
#include <vector>

using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::AssignmentPattern;
using clausetest::PkbAbstractorStub;
using pql::FilterResult;
using std::vector;
using std::string;
using pql::SemanticError;

TEST_CASE("Assignment Pattern Clause PKB Abstractor query", "[AssignmentPattern]") {
    PkbAbstractorStub pkbAbsStub;
    vector<string> postfix = { "subtreeStr" };

    SECTION("should return matches if first argument is wildcard and second is design entity"){
        // AssignmentPattern(_, v, "subtreestr") where v is variable
        // pkb returns {(1, "var"), (1, "var1"), (2, "var1")}
        // Expected to return {{(v, "var")}, {(v,"var1")}}
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(1,"var1"), pair<int, string>(2,"var1")};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is wildcard and second is variable"){
        // AssignmentPattern(_, "var", "subtreestr")
        // pkb returns {(1, "var"), (2, "var")}
        // Expected to return {}, has match is true
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(2,"var1")};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector =  {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both arguments are wildcards") {
        // AssignmentPattern(_, _, "subtreestr") where v is variable
        // pkb returns {(1, "var"), (2, "var1")}
        // Expected to return {{(v, "var")}, {(v,"var1")}}
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(2,"var1")};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, nullptr, true);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both args are design entities"){
        // AssignmentPattern(a, v, "subtreestr") where a is assign and v is variable
        // pkb returns {(1, "var"), (2, "var1")}
        // Expected to return {{(a, 1), (v, "var")}, {(a, 2), (v,"var1")}}
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(2,"var1")};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, assign1),
                pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
               {pair<QueryDesignEntity, QueryArgValue>(assignA, assign2),
               pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is variable"){
        // AssignmentPattern(a, "var", "subtreestr") where v is variable
        // pkb returns {(1, "var"), (2, "var")}
        // Expected to return {{(a, 1)}, {(a, 2)}}
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(2,"var")};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, assign1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(assignA, assign2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is wildcard"){
        // AssignmentPattern(a, _, "subtreestr") where v is variable
        // pkb returns {(1, "var"), (1, "var1"), (2, "var1")}
        // Expected to return {{(a, 1)}, {(a, 2)}}
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(1,"var1"), pair<int, string>(2,"var1")};
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, nullptr, true);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(assignA, assign1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(assignA, assign2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is design entity"){
        // AssignmentPattern(1, v, "subtreestr") where v is variable
        // pkb returns {(1, "var"), (1, "var1")}
        // Expected to return {{(v, "var")}, {(v, "var1")}}
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(2,"var1")};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is variable name"){
        // AssignmentPattern(1, "var", "subtreestr") where v is variable
        // pkb returns {(1, "var")}
        // Expected to return {}, has match true
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var")};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is wildcard"){
        // AssignmentPattern(1, _, "subtreestr") where v is variable
        // pkb returns {(1, "var"), (1, "var1")}
        // Expected to return {}
        pkbAbsStub.resultStmtVar = {pair<int, string>(1,"var"), pair<int, string>(1,"var1")};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        AssignmentPattern assignmentPattern(firstArg, secondArg, postfix, false);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

}
TEST_CASE("Assignment Pattern Clause semantic errors", "[AssignmentPatternClause]") {
    vector<string> postfix = { "_" };

    SECTION("Should throw error if first argument is not assignment") {
        // AssignmentPattern(p, v, "_") where p is a procedure v is a variable
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(&variableV, nullptr, false);
        REQUIRE_THROWS_AS(AssignmentPattern(firstArg, secondArg, postfix, false), SemanticError);
    }

    SECTION("Should throw error if second argument is not variable") {
        // AssignmentPattern(a, 1, "_") where a is an assignment and "1" is a stmt num
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(&stmtS, nullptr, false);
        REQUIRE_THROWS_AS(AssignmentPattern(firstArg, secondArg, postfix, false), SemanticError);
    }
}
