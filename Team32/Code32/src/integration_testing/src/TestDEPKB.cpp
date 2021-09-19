#include "catch.hpp"

#include "PKB/FollowTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ParentTable.h"
#include "PKB/UseTable.h"
#include "simple/SourceProcessor/DesignExtractor.h"
#include "Utils/TestUtils.h"

TEST_CASE("Design extractor and PKB integration") {
    SECTION("Design extractor can extract transitive relation") {
        clearPKB();
        FollowTable::addFollow(1, 2);
        FollowTable::addFollow(2, 3);

        simple::DesignExtractor designExtractor;
        designExtractor.extractDesign();

        ListOfStmtNos res = FollowTable::getFollowStar(1);
        ListOfStmtNos expected = {2, 3};

        REQUIRE(res == expected);

        ListOfStmtNos res1 = FollowTable::getFollowStar(2);
        ListOfStmtNos expected1 = {3};

        REQUIRE(res1 == expected1);

        ListOfStmtNos res2 = FollowTable::getFollowStar(3);
        ListOfStmtNos expected2 = {};

        REQUIRE(res2 == expected2);
    }

    SECTION("Design extractor can extract use and modify for container statement") {
        clearPKB();
        UseTable::addStmtUse(2, "x");
        UseTable::addStmtUse(3, "y");
        UseTable::addStmtUse(4, "z");

        ParentTable::addParent(1, {2, 3, 4});

        ModifyTable::addStmtModify(2, "x");
        ModifyTable::addStmtModify(3, "y");
        ModifyTable::addStmtModify(4, "z");

        simple::DesignExtractor designExtractor;
        designExtractor.extractDesign();

        ListOfVarNames useRes = UseTable::getStmtUse(1);
        ListOfVarNames useExp = {"x", "y", "z"};

        REQUIRE(useRes == useExp);

        ListOfVarNames modifyRes = ModifyTable::getStmtModify(1);
        ListOfVarNames modifyExp = {"x", "y", "z"};
    }
}
