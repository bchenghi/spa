#include "catch.hpp"
#include "Utils/TestUtils.h"

#include "PKB/AssignPostFixTable.h"

TEST_CASE("Testing postfix table", "[assignpostfixtable]") {
	SECTION("test get postfix") {
		AssignPostFixTable::clear();

		AssignPostFixTable::addPostFix(1, "ab+");

		string exp = "ab+";
		string res = AssignPostFixTable::getPostFix(1);

		REQUIRE(exp == res);
		AssignPostFixTable::clear();
	}

	SECTION("test sub string") {
		AssignPostFixTable::clear();

		AssignPostFixTable::addPostFix(1, "ab+");

		bool exp = true;
		bool res = AssignPostFixTable::isSubString(1, "a");

		bool exp2 = false;
		bool res2 = AssignPostFixTable::isSubString(1, "z");

		REQUIRE(exp == res);
		REQUIRE(exp2 == res2);
		AssignPostFixTable::clear();
	}
}
