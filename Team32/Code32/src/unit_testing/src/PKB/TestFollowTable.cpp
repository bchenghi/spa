#include "catch.hpp"

#include "PKB/FollowTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Follow Table", "[followtable]") {
    SECTION("test follow") {
        FollowTable::clear();

        FollowTable::addFollow(1, 2);
        FollowTable::addFollow(2, 3);

        bool exp = true;
        bool exp2 = false;
        bool res = FollowTable::isFollow(1, 2);
        bool res2 = FollowTable::isFollow(1, 3);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        FollowTable::clear();
    }

    SECTION("test get follow") {
        FollowTable::clear();

        FollowTable::addFollow(1, 2);
        FollowTable::addFollow(2, 3);

        STMT_NO exp = 2;
        STMT_NO res = FollowTable::getFollow(1);
        STMT_NO exp2 = 2;
        STMT_NO res2 = FollowTable::getFollowedBy(3);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        FollowTable::clear();
    }

    SECTION("test follow star") {
        FollowTable::clear();

        FollowTable::addFollowStar(1, {2, 3});
        FollowTable::addFollowStarBy(3, { 1, 2 });
        FollowTable::addFollowStar(2, { 3 });
        FollowTable::addFollowStarBy(2, { 1 });

        bool exp = true;
        bool exp2 = false;
        bool res = FollowTable::isFollowStar(1, 3);
        bool res2 = FollowTable::isFollowStar(3, 2);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        FollowTable::clear();
    }

    SECTION("test get follow star") {
        FollowTable::clear();

        FollowTable::addFollowStar(1, { 2, 3 });
        FollowTable::addFollowStarBy(3, { 1, 2 });
        FollowTable::addFollowStar(2, { 3 });
        FollowTable::addFollowStarBy(2, { 1 });

        LIST_OF_STMT_NO exp = { 2, 3 };
        LIST_OF_STMT_NO exp2 = {1};
        LIST_OF_STMT_NO res = FollowTable::getFollowStar(1);
        LIST_OF_STMT_NO res2 = FollowTable::getFollowedStarBy(2);

        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        FollowTable::clear();
    }
}
