#include "catch.hpp"
#include "pql/QueryPreprocessor/Query/Clause/PatternClause/AssignmentPattern.h"

using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::AssignmentPattern;

TEST_CASE("Assignment Pattern Clause semantic errors", "[AssignmentPatternClause]") {
    SECTION("Should throw error if first argument is not assignment") {
        // AssignmentPattern(p, v, "_") where p is a procedure v is a variable
        QueryDesignEntity procedureP(DesignEntity::Procedure, "p");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(&variableV, nullptr, false);
        REQUIRE_THROWS_WITH(AssignmentPattern(firstArg, secondArg, "_"), "Assignment Pattern Clause: First argument must be assignment");
    }

    SECTION("Should throw error if second argument is not variable") {
        // AssignmentPattern(a, 1, "_") where a is an assignment and "1" is a stmt num
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&assignA, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(AssignmentPattern(firstArg, secondArg, "_"), "Assignment Pattern Clause: Second argument must be variable");
    }
}