#include "catch.hpp"

#include "PKB/NextTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing next table", "[nexttable]") {
    SECTION("test is next") {
        NextTable::clear();

        NextTable::addNext(1, 2);
        NextTable::addNext(2, 3);
        NextTable::addNext(3, 4);

        bool exp1 = true;
        bool res1 = NextTable::isNext(2, 3);
        bool exp2 = false;
        bool res2 = NextTable::isNext(1, 3);
        bool exp3 = false;
        bool res3 = NextTable::isNext(5, 3);
        bool exp4 = false;
        bool res4 = NextTable::isNext(1, 5);

        REQUIRE(exp1 == res1);
        REQUIRE(exp2 == res2);
        REQUIRE(exp3 == res3);
        REQUIRE(exp4 == res4);

        NextTable::clear();
    }

    SECTION("test get") {
        NextTable::clear();

        NextTable::addNext(1, 2);
        NextTable::addNext(2, 3);
        NextTable::addNext(3, 4);
        NextTable::addNext(3, 5);
        NextTable::addNext(4, 1);
        NextTable::addNext(5, 1);

        ListOfProgLines exp = { 2 };
        ListOfProgLines res = NextTable::getNext(1);
        ListOfProgLines exp2 = { 4, 5 };
        ListOfProgLines res2 = NextTable::getNext(3);
        ListOfProgLines exp3 = { 4, 5 };
        ListOfProgLines res3 = NextTable::getPrev(1);


        REQUIRE(exp == res);
        REQUIRE(exp2 == res2);
        REQUIRE(exp3 == res3);

        NextTable::clear();
    }
}
