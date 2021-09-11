#include "catch.hpp"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/FollowsClause.h"
#include "PKB/AssignPostFixTable.h"
#include "PKB/FollowTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ParentTable.h"

using pql::DesignEntity;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::FollowsClause;

TEST_CASE("Follows Clause PKB Abstractor query", "[FollowsClause]") {

    SECTION("should return matches if first argument is wildcard and second is design entity"){

    }

    SECTION("should return matches if first argument is wildcard and second is value"){

    }

    SECTION("should return matches if both arguments are wildcard"){

    }

    SECTION("should return matches if first argument is design entity and second is design entity"){

    }

    SECTION("should return matches if first argument is design entity and second is value"){

    }

    SECTION("should return matches if first argument is design entity and second is wildcard"){

    }

    SECTION("should return matches if first argument is value and second is design entity"){

    }

    SECTION("should return matches if first argument is value and second is value"){

    }

    SECTION("should return matches if first argument is value and second is wildcard"){

    }
}

TEST_CASE("Follows Clause semantic errors", "[FollowsClause]") {
    SECTION("Should throw error if first argument is a variable") {
        // Follows(v, 1) where v is a variable
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&variableV, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(FollowsClause(firstArg, secondArg), "Follows Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if first argument is a procedure") {
        // Follows(p, 1) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::Procedure, "p");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&procedureP, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(FollowsClause(firstArg, secondArg), "Follows Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if first argument is a constant") {
        // Follows(c, 1) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(&constantC, nullptr, false);
        QueryArg secondArg(nullptr, &stmtValue1, false);
        REQUIRE_THROWS_WITH(FollowsClause(firstArg, secondArg), "Follows Clause: First argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a variable") {
        // Follows(1, v) where v is a variable
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryDesignEntity variableV(DesignEntity::Variable, "v");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&variableV, nullptr, true);
        REQUIRE_THROWS_WITH(FollowsClause(firstArg, secondArg), "Follows Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a procedure") {
        // Follows(1, p) where p is a procedure
        QueryDesignEntity procedureP(DesignEntity::Procedure, "p");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&procedureP, nullptr, false);
        REQUIRE_THROWS_WITH(FollowsClause(firstArg, secondArg), "Follows Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if second argument is a constant") {
        // Follows(1, c) where c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue stmtValue1(DesignEntity::Stmt, "1");
        QueryArg firstArg(nullptr, &stmtValue1, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_WITH(FollowsClause(firstArg, secondArg), "Follows Clause: Second argument cannot be a variable, constant or procedure");
    }

    SECTION("Should throw error if both arguments are of invalid design entities") {
        // Follows("main", c) where "main" is a procedure and c is a constant.
        QueryDesignEntity constantC(DesignEntity::Constant, "c");
        QueryArgValue procedureMain(DesignEntity::Procedure, "main");
        QueryArg firstArg(nullptr, &procedureMain, false);
        QueryArg secondArg(&constantC, nullptr, false);
        REQUIRE_THROWS_WITH(FollowsClause(firstArg, secondArg), "Follows Clause: First argument cannot be a variable, constant or procedure");
    }
}