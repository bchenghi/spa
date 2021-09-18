#include "catch.hpp"

#include "PKB/TypeToStmtNumTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Type to StmtNum Table", "[typetostmtnumtable]") {
    SECTION("test get stmt type") {
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::IF, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 4);

        pql::DesignEntity exp = pql::DesignEntity::IF;
        pql::DesignEntity res = TypeToStmtNumTable::getTypeOfStmt(3);

        REQUIRE(exp == res);
        TypeToStmtNumTable::clear();
    }

    SECTION("test get type stmts") {
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::IF, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 4);

        ListOfStmtNos exp = {1, 4 };
        ListOfStmtNos res = TypeToStmtNumTable::getStmtWithType(pql::DesignEntity::ASSIGN);

        REQUIRE(exp == res);
        TypeToStmtNumTable::clear();
    }

    SECTION("test get largest stmt") {
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::IF, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 4);

        StmtNo exp = 4;
        StmtNo res = TypeToStmtNumTable::getLargestStmt();

        REQUIRE(exp == res);
        TypeToStmtNumTable::clear();
    }
}
