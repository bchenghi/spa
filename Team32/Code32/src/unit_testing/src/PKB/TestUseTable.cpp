#include "catch.hpp"

#include "PKB/UseTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Use Table", "[usetable]") {
    SECTION("test stmt use") {
        UseTable::clear();

        UseTable::addStmtUse(1, "x");
        UseTable::addStmtUse(1, "z");
        UseTable::addStmtUse(2, "y");

        bool exp = true;
        bool res = UseTable::isStmtUse(2, "y");

        LIST_OF_VAR_NAME exp2 = { "z", "x" };
        LIST_OF_VAR_NAME res2 = UseTable::getStmtUse(1);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        UseTable::clear();
    }

    SECTION("test proc use") {
        UseTable::clear();

        UseTable::addProcUse("test", "x");
        UseTable::addProcUse("test", "y");
        UseTable::addProcUse("test", "z");

        bool exp = false;
        bool res = UseTable::isProcUse("test", "t");

        LIST_OF_VAR_NAME exp2 = { "z", "x" , "y"};
        LIST_OF_VAR_NAME res2 = UseTable::getProcUse("test");

        LIST_OF_VAR_NAME exp3 = LIST_OF_VAR_NAME();
        LIST_OF_VAR_NAME res3 = UseTable::getProcUse("test2");

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        REQUIRE(exp3 == res3);
        UseTable::clear();
    }
}
