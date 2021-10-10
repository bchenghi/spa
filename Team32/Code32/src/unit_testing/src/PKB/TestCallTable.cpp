#include "catch.hpp"

#include "PKB/CallTable.h"
#include "Utils/TestUtils.h"

TEST_CASE("Testing Call Table", "[calltable]") {
	SECTION("test call") {
		CallTable::clear();

        CallTable::addCall("p", "n");
        CallTable::addCall("n", "l");
        CallTable::addCallStar("p", "n");
        CallTable::addCallStar("n", "l");
        CallTable::addCallStar("p", "l");

		bool exp = true;
		bool exp2 = false;
		bool exp3 = true;
		bool res = CallTable::isCall("p", "n");
		bool res2 = CallTable::isCall("p", "l");
		bool res3 = CallTable::isCallStar("p", "l");

		REQUIRE(exp == res);
		REQUIRE(exp2 == res2);
		REQUIRE(exp3 == res3);
		CallTable::clear();
	}

	SECTION("test get call") {
		CallTable::clear();

        CallTable::addCall("p", "n");
        CallTable::addCall("n", "l");
        CallTable::addCallStar("p", "n");
        CallTable::addCallStar("n", "l");
        CallTable::addCallStar("p", "l");

		ListOfProcNames exp = { "n" };
		ListOfProcNames res = CallTable::getCall("p");
        ListOfProcNames exp2 = { "n" };
        ListOfProcNames res2 = CallTable::getCalledBy("l");
		ListOfProcNames exp3 = { "n", "l"};
		ListOfProcNames res3 = CallTable::getCallStar("p");
        ListOfProcNames exp4 = { "n", "p" };
        ListOfProcNames res4 = CallTable::getCalledStarBy("l");

		REQUIRE(exp == res);
		REQUIRE(exp2 == res2);
        REQUIRE(exp3 == res3);
        REQUIRE(exp4 == res4);
		CallTable::clear();
	}
}