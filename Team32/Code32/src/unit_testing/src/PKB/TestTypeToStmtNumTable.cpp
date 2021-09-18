#include "catch.hpp"

#include "PKB/TypeToStmtNumTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Type to StmtNum Table", "[typetostmtnumtable]") {
    SECTION("test get stmt type") {
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::If, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 4);

        pql::DesignEntity exp = pql::DesignEntity::If;
        pql::DesignEntity res = TypeToStmtNumTable::getTypeOfStmt(3);

        REQUIRE(exp == res);
        TypeToStmtNumTable::clear();
    }

    SECTION("test get type stmts") {
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::If, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 4);

        LIST_OF_STMT_NO exp = { 1, 4 };
        LIST_OF_STMT_NO res = TypeToStmtNumTable::getStmtWithType(pql::DesignEntity::Assign);

        REQUIRE(exp == res);
        TypeToStmtNumTable::clear();
    }

    SECTION("test get largest stmt") {
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 1);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::While, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::If, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::Assign, 4);

        STMT_NO exp = 4;
        STMT_NO res = TypeToStmtNumTable::getLargestStmt();

        REQUIRE(exp == res);
        TypeToStmtNumTable::clear();
    }
}
