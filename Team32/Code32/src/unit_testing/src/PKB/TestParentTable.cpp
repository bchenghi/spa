#include "catch.hpp"

#include "PKB/ParentTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Parent Table", "[parenttable]") {
    SECTION("test parent") {
        ParentTable::clear();

        ParentTable::addParent(1, {2,3});
        ParentTable::addParent(3, {4,5});

        bool exp = true;
        bool exp2 = false;
        bool res = ParentTable::isParent(1, 2);
        bool res2 = ParentTable::isParent(1, 4);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        ParentTable::clear();
    }

    SECTION("test get parent") {
        ParentTable::clear();

        ParentTable::addParent(1, { 2,3 });
        ParentTable::addParent(3, { 4,5 });

        StmtNo exp = 1;
        ListOfStmtNos exp2 = {4, 5 };
        StmtNo res = ParentTable::getParent(3);
        ListOfStmtNos res2 = ParentTable::getChildren(3);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        ParentTable::clear();
    }

    SECTION("test parent star") {
        ParentTable::clear();

        ParentTable::addChildrenStar(1, { 2,3,4,5 });
        ParentTable::addParentStar(5, {1,3});

        bool exp = true;
        bool exp2 = false;
        bool res = ParentTable::isParentStar(1, 4);
        bool res2 = ParentTable::isParentStar(5, 1);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        ParentTable::clear();
    }
}
