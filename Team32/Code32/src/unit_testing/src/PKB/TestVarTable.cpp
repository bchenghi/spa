#include "catch.hpp"

#include "PKB/VarTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Variable Table","[vartable]") {
    SECTION("test getVarName()") {
        VarTable::clear();
        VarTable::addVar("t");
        VarName exp = "t";
        VarName res = VarTable::getVarName(1);

        REQUIRE(exp == res);
        VarTable::clear();
    }

    SECTION("test getAllVarName()") {
        VarTable::clear();
        VarTable::addVar("x");
        VarTable::addVar("y");
        VarTable::addVar("a");
        VarTable::addVar("b");

        ListOfVarNames exp = {"y", "x", "a", "b" };
        ListOfVarNames res = VarTable::getAllVarName();

        REQUIRE(exp == res);
        VarTable::clear();
    }

    SECTION("test size") {
        VarTable::clear();
        VarTable::addVar("x");
        VarTable::addVar("y");
        VarTable::addVar("a");
        VarTable::addVar("b");

        size_t exp = 4;
        size_t res = VarTable::getSize();

        REQUIRE(exp == res);
        VarTable::clear();
    }

    SECTION("test index") {
        VarTable::clear();
        VarTable::addVar("x");
        VarTable::addVar("y");
        VarTable::addVar("a");
        VarTable::addVar("b");

        VarIndex exp = 4;
        VarIndex res = VarTable::getVarIndex("b");

        REQUIRE(exp == res);
        VarTable::clear();
    }
}
