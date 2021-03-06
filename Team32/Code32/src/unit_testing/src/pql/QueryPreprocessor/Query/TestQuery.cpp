#include "catch.hpp"

#include "pql/AttributeType.h"
#include "pql/Errors/SemanticError.h"
#include "pql/DesignEntity.h"
#include "pql/QueryPreprocessor/Query/Clause/PatternClause/AssignmentPattern.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ModifiesClause.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ParentClause.h"
#include "pql/QueryPreprocessor/Query/Query.h"

#include <string>
#include <vector>

using pql::AttributeType;
using pql::DesignEntity;
using pql::ModifiesClause;
using pql::Query;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using pql::SelectClause;
using std::string;
using std::vector;
using pql::SemanticError;

TEST_CASE("Query", "[query]") {
    pql::SyntaxCheck::setSyntaxCheckFlag(false);
    SECTION("Should throw error if synonym is declared repeatedly") {
        // Stmt s; Assign a; Procedure s;
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity procedureS(DesignEntity::PROCEDURE, "s");
        SelectClause selectS({stmtS});
        REQUIRE_THROWS_AS(Query(&selectS, {stmtS, assignA, procedureS}, {}), SemanticError);
    }

    SECTION("Should throw error if select clause uses an entity that is not declared") {
        // Stmt s; Assign a;
        // Select s1 such that Modifies(s, "abc");
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity stmtS1(DesignEntity::STMT, "s1");
        SelectClause selectS1({stmtS1});
        QueryArg modifiesFirstArg(&stmtS, nullptr, false);
        QueryArgValue variableAbc(DesignEntity::VARIABLE, "abc");
        QueryArg modifiesSecondArg(nullptr, &variableAbc, false);
        ModifiesClause modifiesClause(modifiesFirstArg, modifiesSecondArg);
        REQUIRE_THROWS_AS(Query(&selectS1, {stmtS, assignA}, {&modifiesClause}),SemanticError);
    }

    SECTION("Should throw error if such that clauses uses an entity that is not declared") {
        // Stmt s; Assign a;
        // Select s such that Modifies(s1, "abc");
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity stmtS1(DesignEntity::STMT, "s1");
        SelectClause selectS({stmtS});
        QueryArg modifiesFirstArg(&stmtS1, nullptr, false);
        QueryArgValue variableAbc(DesignEntity::VARIABLE, "abc");
        QueryArg modifiesSecondArg(nullptr, &variableAbc, false);
        ModifiesClause modifiesClause(modifiesFirstArg, modifiesSecondArg);
        REQUIRE_THROWS_AS(Query(&selectS, {stmtS, assignA}, {&modifiesClause}), SemanticError);
    }

    SECTION("Should not throw error if select clauses uses an existing entity but has attribute type") {
        // Stmt s; Assign a;
        // Select s such that Modifies(s1, "abc");
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity stmtSStmtNum(DesignEntity::STMT, "s", AttributeType::STMT_NUM);
        SelectClause selectS({stmtSStmtNum});
        QueryArg modifiesFirstArg(&stmtS, nullptr, false);
        QueryArgValue variableAbc(DesignEntity::VARIABLE, "abc");
        QueryArg modifiesSecondArg(nullptr, &variableAbc, false);
        ModifiesClause modifiesClause(modifiesFirstArg, modifiesSecondArg);
        Query(&selectS, {stmtS, assignA}, {&modifiesClause});
    }
}

TEST_CASE("Queries equality operator", "[Query]") {
    SECTION("should be equal with multiple filter clauses") {
        vector<string> postfix = { "count" };

        // while w; assign a; Select w such that Parent(a, w) pattern a(_, _"count"_)
        QueryDesignEntity whileW(QueryDesignEntity(DesignEntity::WHILE, "w"));
        QueryDesignEntity assignA(QueryDesignEntity(DesignEntity::ASSIGN, "a"));
        SelectClause selectW({whileW});
        pql::ParentClause parentClause(pql::QueryArg(&whileW, nullptr, false), pql::QueryArg(&assignA, nullptr, false));
        pql::AssignmentPattern assignmentPattern(pql::QueryArg(&assignA, nullptr, false), pql::QueryArg(nullptr, nullptr, true), postfix, false);
        Query queryObj(&selectW, {whileW, assignA},{&parentClause, &assignmentPattern});

        QueryDesignEntity whileW1(QueryDesignEntity(DesignEntity::WHILE, "w"));
        QueryDesignEntity assignA1(QueryDesignEntity(DesignEntity::ASSIGN, "a"));
        SelectClause selectW1({whileW1});
        pql::ParentClause parentClause1(pql::QueryArg(&whileW1, nullptr, false), pql::QueryArg(&assignA1, nullptr, false));
        pql::AssignmentPattern assignmentPattern1(pql::QueryArg(&assignA1, nullptr, false), pql::QueryArg(nullptr, nullptr, true), postfix, false);
        Query queryObj1(&selectW1, {whileW1, assignA1},{&parentClause1, &assignmentPattern1});
        REQUIRE(queryObj == queryObj1);
    }
}
