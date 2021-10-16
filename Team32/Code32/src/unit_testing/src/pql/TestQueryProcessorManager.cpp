#include "catch.hpp"

#include <chrono>
#include "pql/QueryProcessorManager.h"

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using pql::DesignEntity;

TEST_CASE("Queries with no clauses") {
    SECTION("should return all variable") {
        // variable v; Select v
        VarTable::clear();
        VarTable::addVar("a");
        VarTable::addVar("b");
        VarTable::addVar("c");
        std::string queryString = "variable v;\nSelect v";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"a", "b", "c"};
        VarTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all constants") {
        // constant c; Select c
        ConstantTable::clear();
        ConstantTable::addConstant(1);
        ConstantTable::addConstant(2);
        ConstantTable::addConstant(3);
        std::string queryString = "constant c;\nSelect c";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        ConstantTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all assigns") {
        // assign a; Select a
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 3);
        std::string queryString = "assign a;\nSelect a";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        TypeToStmtNumTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all ifs") {
        // if i; Select i
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::IF, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::IF, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::IF, 3);
        std::string queryString = "if i;\nSelect i";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        TypeToStmtNumTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all whiles") {
        // while w; Select w
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 3);
        std::string queryString = "while w;\nSelect w";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        TypeToStmtNumTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all statements") {
        // stmt s; Select s
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::STMT, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::STMT, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::STMT, 3);
        std::string queryString = "stmt s;\nSelect s";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        TypeToStmtNumTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all prints") {
        // print p; Select p
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::PRINT, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::PRINT, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::PRINT, 3);
        std::string queryString = "print p;\nSelect p";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        TypeToStmtNumTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all reads") {
        // read r; Select r
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::READ, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::READ, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::READ, 3);
        std::string queryString = "read r;\nSelect r";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1", "2", "3"};
        TypeToStmtNumTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return all procedures") {
        // procedure proc; Select proc
        ProcTable::clear();
        ProcTable::addProc("main", std::unordered_set<StmtNo>{1});
        ProcTable::addProc("a", std::unordered_set<StmtNo>{2});
        ProcTable::addProc("b", std::unordered_set<StmtNo>{3});
        std::string queryString = "procedure proc;\nSelect proc";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"main", "a", "b"};
        ProcTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }
}

TEST_CASE("Queries with clauses") {
    SECTION("should return correct result with one follows clause") {
        // assign a;
        // Select a such that Follows(2, a)
        FollowTable::clear();
        TypeToStmtNumTable::clear();
        FollowTable::addFollow(1,2);
        FollowTable::addFollow(2,3);
        FollowTable::addFollow(3,4);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 3);
        std::string queryString = "assign a;\nSelect a such that Follows(2,a)";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"3"};
        FollowTable::clear();
        TypeToStmtNumTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return correct result for procedure name as first argument of modifies") {
        // variable v;
        // Select v such that Modifies("main", 1)
        VarTable::clear();
        ProcTable::clear();
        ModifyTable::clear();
        VarTable::addVar("a");
        ProcTable::addProc("main", std::unordered_set<StmtNo>{1});
        ModifyTable::addProcModify("main", "var");
        std::string queryString = "variable v;\nSelect v such that Modifies(\"main\", v)";\
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"var"};
        VarTable::clear();
        ProcTable::clear();
        ModifyTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return correct result for procedure synonym as first argument of modifies") {
        // procedure p;
        // Select p such that Modifies(p, 1)
        VarTable::clear();
        ProcTable::clear();
        ModifyTable::clear();
        VarTable::addVar("a");
        ProcTable::addProc("main", std::unordered_set<StmtNo>{1});
        ModifyTable::addProcModify("main", "var");
        std::string queryString = "procedure p; variable v;\nSelect p such that Modifies(p, v)";\
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"main"};
        VarTable::clear();
        ProcTable::clear();
        ModifyTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return correct result with one such that clause and pattern clause") {
        //  while w; assign a;
        //  Select w such that Parent(w, a) pattern a(_ , _”count”_)
        vector<string> postfix = { "count" };

        ParentTable::clear();
        TypeToStmtNumTable::clear();
        AssignPostFixTable::clear();
        ModifyTable::clear();
        ParentTable::addParent(1,{2});
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 2);
        AssignPostFixTable::addPostFix(2, postfix);
        ModifyTable::addStmtModify(2, "i");
        std::string queryString = "while w; assign a;\nSelect w such that Parent(w, a) pattern a(_ , _\"count\"_)";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {"1"};
        ParentTable::clear();
        TypeToStmtNumTable::clear();
        AssignPostFixTable::clear();
        ModifyTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return correct result with no matches in clauses") {
        //  while w; assign a;
        //  Select w such that Parent(w, a) pattern a(_ , _”count”_)
        //  Parent clause returns no matches.
        vector<string> postfix = { "count" };

        ParentTable::clear();
        TypeToStmtNumTable::clear();
        AssignPostFixTable::clear();
        ModifyTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 2);
        AssignPostFixTable::addPostFix(2, postfix);
        ModifyTable::addStmtModify(2, "i");
        std::string queryString = "while w; assign a;\nSelect w such that Parent(w, a) pattern a(_ , _\"count\"_)";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        ParentTable::clear();
        TypeToStmtNumTable::clear();
        AssignPostFixTable::clear();
        ModifyTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }
}

TEST_CASE("test optimisation") {
    SECTION("query with larger intermediate table without optimisation") {
//         stmt s, s1, s2; variable v;
//         select s such that Follows(s, s1) such that Modifies(s2, v) such that follows(s, s2)

//         follows(s, s1) modifies(s2, v) follows(s, s2)
//         without optimisation, there is cartesian product between follows(s, s1) modifies(a, v). Largest intermediate table is 64 rows
//         With optimisation, it should be arranged such that the two follows clause are together. No cartesian product. Largest intermediate table is 8 rows.

        TypeToStmtNumTable::clear();
        FollowTable::clear();
        ModifyTable::clear();
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 2);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 3);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 4);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 5);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 6);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 7);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 8);
        FollowTable::addFollow(1,2);
        FollowTable::addFollow(2,3);
        FollowTable::addFollow(3,4);
        FollowTable::addFollow(4,5);
        FollowTable::addFollow(5,6);
        FollowTable::addFollow(6,7);
        FollowTable::addFollow(7,8);
        ModifyTable::addStmtModify(1,"v");
        ModifyTable::addStmtModify(2,"v");
        ModifyTable::addStmtModify(3,"v");
        ModifyTable::addStmtModify(4,"v");
        ModifyTable::addStmtModify(5,"v");
        ModifyTable::addStmtModify(6,"v");
        ModifyTable::addStmtModify(7,"v");
        ModifyTable::addStmtModify(8,"v");

        std::string queryString = "stmt s, s1, s2; variable v;\nSelect s such that Follows(s, s1) such that Modifies(s2, v) such that Follows(s, s2)";

        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        queryProcessorManager.setOptimisation(false);

        steady_clock::time_point beginWithoutOpt = steady_clock::now();

        set<string> nonOptimizedResult = queryProcessorManager.executeQuery(queryString);

        steady_clock::time_point endWithoutOpt = steady_clock::now();

        queryProcessorManager.setOptimisation(true);

        steady_clock::time_point beginWithOpt = steady_clock::now();

        set<string> optimizedResult = queryProcessorManager.executeQuery(queryString);

        steady_clock::time_point endWithOpt = steady_clock::now();

        std::cout << "QueryProcessorManager: Without optimisation = " <<
        duration_cast<microseconds>(endWithoutOpt - beginWithoutOpt).count() << "[µs], With optimisation = " <<
        duration_cast<microseconds>(endWithOpt - beginWithOpt).count() << "[µs]" << std::endl;

        REQUIRE((duration_cast<microseconds>(endWithoutOpt - beginWithoutOpt).count() >
        duration_cast<microseconds>(endWithOpt - beginWithOpt).count() && nonOptimizedResult == optimizedResult));

        TypeToStmtNumTable::clear();
        FollowTable::clear();
        ModifyTable::clear();
    }
}

TEST_CASE("Queries with semantic errors") {
    SECTION("should return empty result with undeclared design entity") {
        // variable v;
        // Select a
        VarTable::clear();
        VarTable::addVar("a");
        std::string queryString = "variable v; Select a";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        VarTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return empty result with wildcard as Uses clause's first argument") {
        // assign a; variable v;
        // Select a such that Uses(_, v)
        TypeToStmtNumTable::clear();
        VarTable::clear();
        UseTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 3);
        VarTable::addVar("a");
        UseTable::addStmtUse(3, "a");
        std::string queryString = "assign a; variable v;\nSelect a such that Uses(_, v)";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        TypeToStmtNumTable::clear();
        VarTable::clear();
        UseTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }
}

TEST_CASE("Queries with syntactic errors") {
    SECTION("should return empty result with missing colon") {
        // variable v
        // Select v
        VarTable::clear();
        VarTable::addVar("a");
        std::string queryString = "variable v\nSelect v";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        VarTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }

    SECTION("should return empty result unknown design entity") {
        // varia v; Select v
        VarTable::clear();
        VarTable::addVar("a");
        std::string queryString = " varia v; Select v";
        pql::QueryProcessorManager queryProcessorManager = pql::QueryProcessorManager();
        set<string> obtainedResults = queryProcessorManager.executeQuery(queryString);
        set<string> expectedResults = {};
        VarTable::clear();
        REQUIRE(obtainedResults == expectedResults);
    }
}
