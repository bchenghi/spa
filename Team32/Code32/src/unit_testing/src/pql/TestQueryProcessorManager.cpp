#include "catch.hpp"
#include "pql/QueryProcessorManager.h"

TEST_CASE("Queries with no clauses") {
    SECTION("should return all variable") {
        // variable v; Select v
        VarTable::addVar("a");
        VarTable::addVar("b");
        VarTable::addVar("c");
        std::string queryString = "variable v;\nSelect v";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"a", "b", "c"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all constants") {
        // constant c; Select c
        ConstantTable::addConstant(1);
        ConstantTable::addConstant(2);
        ConstantTable::addConstant(3);
        std::string queryString = "constant c;\nSelect c";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all assigns") {
        // assign a; Select a
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 3);
        std::string queryString = "assign a;\nSelect a";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all ifs") {
        // if i; Select i
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::If, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::If, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::If, 3);
        std::string queryString = "if i;\nSelect i";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all whiles") {
        // while w; Select w
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, 3);
        std::string queryString = "while w;\nSelect w";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all statements") {
        // stmt s; Select s
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Stmt, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Stmt, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Stmt, 3);
        std::string queryString = "stmt s;\nSelect s";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all prints") {
        // print p; Select p
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Print, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Print, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Print, 3);
        std::string queryString = "print p;\nSelect p";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all reads") {
        // read r; Select r
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Read, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Read, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Read, 3);
        std::string queryString = "read r;\nSelect r";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all procedures") {
        // procedure proc; Select proc
        ProcTable::addProc("main", std::unordered_set<STMT_NO>{1});
        ProcTable::addProc("a", std::unordered_set<STMT_NO>{2});
        ProcTable::addProc("b", std::unordered_set<STMT_NO>{3});
        std::string queryString = "procedure proc;\nSelect proc";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"main", "a", "b"};
        REQUIRE(obtainedResults == expectedResults);
    }
}

TEST_CASE("Queries with clauses") {
    SECTION("should return correct result with one follows clause") {
        // assign a;
        // Select a such that Follows(2, a)
        FollowTable::addFollow(1,2);
        FollowTable::addFollow(2,3);
        FollowTable::addFollow(3,4);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 3);
        std::string queryString = "assign a;\nSelect a such that Follows(2,a)";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"3"};
        REQUIRE(obtainedResults == expectedResults);
    }

    // Unable to parse input
//    SECTION("should return correct result with one such that clause and pattern clause") {
//        //  while w; assign a;
//        //  Select w such that Parent(w, a) pattern a(_ , _”count”_)
//        ParentTable::addParent(1,{2});
//        ParentTable::addParent(2,{3, 4});
//        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, 1);
//        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 2);
//        AssignPostFixTable::addPostFix(2, "count");
//        std::string queryString = "while w; assign a;\nSelect w such that Parent(w, a) pattern a(_ , _\"count\"_)";
//        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
//        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
//        set<string> expectedResults = {"1"};
//        REQUIRE(obtainedResults == expectedResults);
//    }
}

TEST_CASE("Queries with semantic errors") {
    SECTION("should return empty result with undeclared design entity") {
        // variable v;
        // Select a
        VarTable::addVar("a");
        std::string queryString = "variable v; Select a";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return empty result with wildcard as Uses clause's first argument") {
        // assign a; variable v;
        // Select a such that Uses(_, v)
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 3);
        VarTable::addVar("a");
        UseTable::addStmtUse(3, "a");
        std::string queryString = "assign a; variable v;\nSelect a such that Uses(_, v)";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        REQUIRE(obtainedResults == expectedResults);
    }
}

TEST_CASE("Queries with syntactic errors") {
    SECTION("should return empty result with missing colon") {
        // variable v
        // Select v
        VarTable::addVar("a");
        std::string queryString = "variable v\nSelect v";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return empty result unknown design entity") {
        // varia v; Select v
        VarTable::addVar("a");
        std::string queryString = " varia v; Select v";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        REQUIRE(obtainedResults == expectedResults);
    }

    // Modifies/Uses clause, no procedures for first argument in iter 1.
//    SECTION("should return empty result if clause has syntactically invalid argument") {
//        // variable v;
//        // Select v such that Modifies("main", 1)
//        VarTable::addVar("a");
//        ProcTable::addProc("main", std::unordered_set<STMT_NO>{1});
//        std::string queryString = "variable v;\nSelect v such that Modifies(\"main\", 1)";\
//        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
//        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
//        set<string> expectedResults = {};
//        REQUIRE(obtainedResults == expectedResults);
//    }
}