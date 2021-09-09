#include "catch.hpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ModifiesClause.h"

using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::ModifiesClause;

TEST_CASE("Modifies Clause Semantic errors", "[ModifiesClause]") {
    SECTION("Should throw error if first argument is a wildcard") {
        // Modifies(_, "abc")
        QueryArgValue variableValueAbc(DesignEntity::Variable, "abc");
        QueryArg firstArg(nullptr, nullptr, true);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: First argument cannot be a wildcard");
    }

    SECTION("Should throw error if first argument is a variable") {
        // Modifies(v, "abc") where v is a variable
        QueryArgValue variableValueAbc(DesignEntity::Variable, "abc");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: First argument cannot be a variable or constant");
    }

    SECTION("Should throw error if first argument is a constant") {
        // Modifies(c, "abc") where c is a constant.
        QueryArgValue variableValueAbc(DesignEntity::Variable, "abc");
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &variableValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: First argument cannot be a variable or constant");
    }

    SECTION("should throw error if second argument is not a variable") {
        // Modifies(s, p) where s is Stmt and p is Procedure
        QueryArgValue procedureValueAbc(DesignEntity::Procedure, "abc");
        QueryDesignEntity stmtS(DesignEntity::Stmt, "s");
        QueryArg firstArg(&stmtS, nullptr, false);
        QueryArg secondArg(nullptr, &procedureValueAbc, false);
        REQUIRE_THROWS_WITH(ModifiesClause(firstArg, secondArg), "Modifies Clause: Second argument must be a variable");
    }
}
