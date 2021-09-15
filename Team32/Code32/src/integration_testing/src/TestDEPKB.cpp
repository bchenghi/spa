#include <catch.hpp>
#include <simple/SourceProcessor/DesignExtractor.h>
#include <PKB/FollowTable.h>
#include <PKB/ParentTable.h>
#include <PKB/ModifyTable.h>
#include <PKB/UseTable.h>

TEST_CASE("Design extractor can extract transitive relation") {
        FollowTable::addFollow(1, 2);
        FollowTable::addFollow(2, 3);

        simple::DesignExtractor designExtractor;
        designExtractor.extractDesign();

        LIST_OF_STMT_NO res = FollowTable::getFollowStar(1);
        LIST_OF_STMT_NO expected = {2, 3};

        REQUIRE(res == expected);

        LIST_OF_STMT_NO res1 = FollowTable::getFollowStar(2);
        LIST_OF_STMT_NO expected1 = {3};

        REQUIRE(res1 == expected1);

        LIST_OF_STMT_NO res2 = FollowTable::getFollowStar(3);
        LIST_OF_STMT_NO expected2 = {};

        REQUIRE(res2 == expected2);
}

TEST_CASE("Design extractor can extract use and modify for container statement") {
        UseTable::addStmtUse(2, "x");
        UseTable::addStmtUse(3, "y");
        UseTable::addStmtUse(4, "z");

        ParentTable::addParent(1, {2, 3, 4});

        ModifyTable::addStmtModify(2, "x");
        ModifyTable::addStmtModify(3, "y");
        ModifyTable::addStmtModify(4, "z");

        simple::DesignExtractor designExtractor;
        designExtractor.extractDesign();

        LIST_OF_VAR_NAME useRes = UseTable::getStmtUse(1);
        LIST_OF_VAR_NAME useExp = {"x", "y", "z"};

        REQUIRE(useRes == useExp);

        LIST_OF_VAR_NAME modifyRes = ModifyTable::getStmtModify(1);
        LIST_OF_VAR_NAME modifyExp = {"x", "y", "z"};
}


