#include "catch.hpp"

#include "pql/Errors/SemanticError.h"
#include "../Stubs/PkbAbstractorStub.cpp"
#include "pql/QueryPreprocessor/Query/Clause/PatternClause/IfPattern.h"

#include <iostream>
#include <string>
#include <vector>

using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::IfPattern;
using clausetest::PkbAbstractorStub;
using pql::FilterResult;
using std::vector;
using std::string;
using pql::SemanticError;

TEST_CASE("If Pattern Clause PKB Abstractor query", "[AssignmentPattern]") {
    PkbAbstractorStub pkbAbsStub;

    SECTION("should return matches if first argument is wildcard and second is design entity"){
        // IfPattern(_, v) where v is variable
        // pkb returns {{1, {"var", "var1"}}, {2, {"var1"}}}
        // Expected to return {{(v, "var")}, {(v,"var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}, {2, {"var1"}}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        IfPattern assignmentPattern(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = assignmentPattern.executePKBAbsQuery(&pkbAbsStub);
        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is wildcard and second is variable"){
        // IfPattern(_, "var")
        // pkb returns {{1, {"var"}}, {2, {"var"}}}
        // Expected to return {}, has match is true
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var"}}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        IfPattern ifPattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector =  {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both arguments are wildcards") {
        // IfPattern(_, _) where v is variable
        // pkb returns {{1, {"var"}}, {2, {"var1"}}}
        // Expected to return {{(v, "var")}, {(v,"var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var1"}}};
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, nullptr, true);
        IfPattern ifPattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if both args are design entities"){
        // IfPattern(i, v) where i is assign and v is variable
        // pkb returns {{1, {"var"}}, {2, {"var1"}}}
        // Expected to return {{(a, 1), (v, "var")}, {(a, 2), (v,"var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var1"}}};
        QueryDesignEntity ifI(DesignEntity::IF, "a");
        QueryArg firstArg(&ifI, nullptr, false);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        IfPattern ifPattern(firstArg, secondArg);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(ifI, assign1),
                                                                                pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(ifI, assign2),
                                                                                pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is variable"){
        // IfPattern(i, "var") where v is variable
        // pkb returns {{1, {"var"}}, {2, {"var"}}}
        // Expected to return {{(a, 1)}, {(a, 2)}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}, {2, {"var"}}};
        QueryDesignEntity ifI(DesignEntity::IF, "a");
        QueryArg firstArg(&ifI, nullptr, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        IfPattern ifPattern(firstArg, secondArg);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(ifI, assign1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(ifI, assign2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is design entity and second is wildcard"){
        // IfPattern(i, _) where v is variable
        // pkb returns {{1, {"var", "var1"}}, {2, {"var1"}}}
        // Expected to return {{(a, 1)}, {(a, 2)}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}, {2, {"var1"}}};
        QueryDesignEntity ifI(DesignEntity::IF, "a");
        QueryArg firstArg(&ifI, nullptr, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, nullptr, true);
        IfPattern ifPattern(firstArg, secondArg);
        QueryArgValue assign1(DesignEntity::STMT, "1");
        QueryArgValue assign2(DesignEntity::STMT, "2");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(ifI, assign1)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(ifI, assign2)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is design entity"){
        // IfPattern(1, v) where v is variable
        // pkb returns {{1, {"var", "var1"}}}
        // Expected to return {{(v, "var")}, {(v, "var1")}}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg secondArg(&variableV, nullptr, false);
        IfPattern ifPattern(firstArg, secondArg);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArgValue variableVar1(DesignEntity::VARIABLE, "var1");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {{pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar)},
                                                                               {pair<QueryDesignEntity, QueryArgValue>(variableV, variableVar1)}};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is variable name"){
        // IfPattern(1, "var")
        // pkb returns {{1, {"var"}}}
        // Expected to return {}, has match true
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var"}}};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArgValue variableVar(DesignEntity::VARIABLE, "var");
        QueryArg secondArg(nullptr, &variableVar, false);
        IfPattern ifPattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

    SECTION("should return matches if first argument is stmt num and second is wildcard"){
        // IfPattern(1, _)
        // pkb returns {{1, {"var", "var1"}}}
        // Expected to return {}
        pkbAbsStub.resultStmtNumVarSet = {{1, {"var", "var1"}}};
        QueryArgValue stmt1(DesignEntity::STMT, "1");
        QueryArg firstArg(nullptr, &stmt1, false);
        QueryArg secondArg(nullptr, nullptr, true);
        IfPattern ifPattern(firstArg, secondArg);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> resultVector = {};
        FilterResult expectedResult = FilterResult(resultVector, true);
        FilterResult obtainedResult = ifPattern.executePKBAbsQuery(&pkbAbsStub);

        REQUIRE(obtainedResult == expectedResult);
    }

}
TEST_CASE("If Pattern Clause semantic errors", "[IfPatternClause]") {
    SECTION("Should throw error if first argument is not if") {
        // IfPattern(p, v, "_") where p is a procedure v is a variable
        QueryDesignEntity procedureP(DesignEntity::PROCEDURE, "p");
        QueryDesignEntity variableV(DesignEntity::VARIABLE, "v");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(&variableV, nullptr, false);
        REQUIRE_THROWS_AS(IfPattern(firstArg, secondArg), SemanticError);
    }

    SECTION("Should throw error if second argument is not variable") {
        // IfPattern(i, 1, "_") where a is an assignment and "1" is a stmt num
        QueryDesignEntity ifI(DesignEntity::IF, "a");
        QueryArgValue stmtValue1(DesignEntity::STMT, "1");
        QueryArg firstArg(&ifI, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_AS(IfPattern(firstArg, secondArg), SemanticError);
    }
}
