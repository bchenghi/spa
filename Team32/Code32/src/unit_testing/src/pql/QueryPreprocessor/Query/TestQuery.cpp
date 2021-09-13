#include "catch.hpp"
#include "pql/DesignEntity.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ModifiesClause.h"
#include "pql/QueryPreprocessor/Query/Query.h"

using pql::DesignEntity;
using pql::ModifiesClause;
using pql::Query;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::SelectClause;

TEST_CASE("Query", "[query]") {
    SECTION("Should throw error if synonym is declared repeatedly") {
        // Stmt s; Assign a; Procedure s;
        QueryDesignEntity stmtS(DesignEntity::Stmt, "s");
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryDesignEntity procedureS(DesignEntity::Procedure, "s");
        SelectClause selectS(stmtS);
        REQUIRE_THROWS_WITH(Query(&selectS, {stmtS, assignA, procedureS}, {}), "Query: Repeated use of same synonym not allowed");
    }

    SECTION("Should throw error if select clause uses an entity that is not declared") {
        // Stmt s; Assign a;
        // Select s1 such that Modifies(s, "abc");
        QueryDesignEntity stmtS(DesignEntity::Stmt, "s");
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryDesignEntity stmtS1(DesignEntity::Stmt, "s1");
        SelectClause selectS1(stmtS1);
        QueryArg modifiesFirstArg(&stmtS, nullptr, false);
        QueryArgValue variableAbc(DesignEntity::Variable, "abc");
        QueryArg modifiesSecondArg(nullptr, &variableAbc, false);
        ModifiesClause modifiesClause(modifiesFirstArg, modifiesSecondArg);
        REQUIRE_THROWS_WITH(Query(&selectS1, {stmtS, assignA}, {&modifiesClause}), "Query: Selected entity is not declared");
    }

    SECTION("Should throw error if such that clauses uses an entity that is not declared") {
        // Stmt s; Assign a;
        // Select s such that Modifies(s1, "abc");
        QueryDesignEntity stmtS(DesignEntity::Stmt, "s");
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        QueryDesignEntity stmtS1(DesignEntity::Stmt, "s1");
        SelectClause selectS(stmtS);
        QueryArg modifiesFirstArg(&stmtS1, nullptr, false);
        QueryArgValue variableAbc(DesignEntity::Variable, "abc");
        QueryArg modifiesSecondArg(nullptr, &variableAbc, false);
        ModifiesClause modifiesClause(modifiesFirstArg, modifiesSecondArg);
        REQUIRE_THROWS_WITH(Query(&selectS, {stmtS, assignA}, {&modifiesClause}), "Query: Query argument in clause is not declared");
    }
}