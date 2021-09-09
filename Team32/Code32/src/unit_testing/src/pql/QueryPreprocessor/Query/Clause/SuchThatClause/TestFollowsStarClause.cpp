#include "catch.hpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/FollowsStarClause.h"

using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::FollowsStarClause;

TEST_CASE("Follows Star Clause semantic errors", "[FollowsStarClause]") {
    SECTION("Should throw error if first argument is a variable") {
        // FollowsStar(v, 1) where v is a variable
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(FollowsStarClause(firstArg, secondArg), "Follows Star Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if first argument is a procedure") {
        // FollowsStar(p, 1) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::Procedure, "p");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(FollowsStarClause(firstArg, secondArg), "Follows Star Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if first argument is a constant") {
        // FollowsStar(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(FollowsStarClause(firstArg, secondArg), "Follows Star Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a variable") {
        // FollowsStar(1, v) where v is a variable
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&variableV, nullptr, true);
        REQUIRE_THROWS_WITH(FollowsStarClause(firstArg, secondArg), "Follows Star Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a procedure") {
        // FollowsStar(1, p) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::Procedure, "p");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&procedureP, nullptr, false);
        REQUIRE_THROWS_WITH(FollowsStarClause(firstArg, secondArg), "Follows Star Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a constant") {
        // FollowsStar(1, c) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_WITH(FollowsStarClause(firstArg, secondArg), "Follows Star Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if both arguments are of invalid design entities") {
        // FollowsStar("main", c) where "main" is a procedure and c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue procedureMain(DesignEntity::Procedure, "main");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_WITH(FollowsStarClause(firstArg, secondArg), "Follows Star Clause: First argument cannot be a variable, constant or procedure");
    }
}