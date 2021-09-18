#include "catch.hpp"

#include "PKB/ProcTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Procedure Table", "[proctable]") {
    SECTION("test getProcStmtList()") {
        ProcTable::clear();

        ProcTable::addProc("test", { 1, 2, 3, 4 });

        ListOfStmtNos exp = {1, 2, 3, 4 };
        ListOfStmtNos res = ProcTable::getProcStmtList("test");

        REQUIRE(exp == res);
        ProcTable::clear();
    }

    SECTION("test getAllProcedure()") {
        ProcTable::clear();

        ProcTable::addProc("test", { 1, 2, 3, 4 });
        ProcTable::addProc("test2", {});
        ProcTable::addProc("test3", {});

        ListOfProcNames exp = {"test", "test2", "test3" };
        ListOfProcNames res = ProcTable::getAllProcedure();

        REQUIRE(exp == res);
        ProcTable::clear();
    }

    SECTION("test size") {
        ProcTable::clear();

        ProcTable::addProc("test", { 1, 2, 3, 4 });
        ProcTable::addProc("test2", {});
        ProcTable::addProc("test3", {});

        size_t exp = 3;
        size_t res = ProcTable::getSize();

        REQUIRE(exp == res);
        ProcTable::clear();
    }
}
