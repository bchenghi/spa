#include "catch.hpp"

#include "PKB/ModifyTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Modify Table", "[modifytable]") {
    SECTION("test stmt modify") {
        ModifyTable::clear();

        ModifyTable::addStmtModify(1, "x");
        ModifyTable::addStmtModify(1, "z");
        ModifyTable::addStmtModify(2, "y");

        bool exp = true;
        bool res = ModifyTable::isStmtModify(2, "y");

        ListOfVarNames exp2 = {"z", "x" };
        ListOfVarNames res2 = ModifyTable::getStmtModify(1);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        ModifyTable::clear();
    }

    SECTION("test proc modify") {
        ModifyTable::clear();

        ModifyTable::addProcModify("test", "x");
        ModifyTable::addProcModify("test", "y");
        ModifyTable::addProcModify("test", "z");

        bool exp = false;
        bool res = ModifyTable::isProcModify("test", "t");

        ListOfVarNames exp2 = {"z", "x" , "y" };
        ListOfVarNames res2 = ModifyTable::getProcModify("test");

        ListOfVarNames exp3 = ListOfVarNames();
        ListOfVarNames res3 = ModifyTable::getProcModify("test2");

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        REQUIRE(exp3 == res3);
        ModifyTable::clear();
    }
}
