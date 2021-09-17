#include "catch.hpp"
#include "Utils/TestUtils.h"

#include "PKB/AssignPostFixTable.h"

#include <string>
#include <vector>

using std::vector;
using std::string;

TEST_CASE("Testing postfix table", "[assignpostfixtable]") {
    vector<string> postfix = { "a", "b", "+" };

    SECTION("test get postfix") {
		AssignPostFixTable::clear();

		AssignPostFixTable::addPostFix(1, postfix);

		vector<string> res = AssignPostFixTable::getPostFix(1);

		REQUIRE(postfix == res);
		AssignPostFixTable::clear();
	}

	SECTION("test sub string") {
        vector<string> subTrue = { "a" };
        vector<string> subFalse = { "z" };

		AssignPostFixTable::clear();

		AssignPostFixTable::addPostFix(1, postfix);

		bool exp = true;
		bool res = AssignPostFixTable::isSubExpression(1, subTrue);

		bool exp2 = false;
		bool res2 = AssignPostFixTable::isSubExpression(1, subFalse);

		REQUIRE(exp == res);
		REQUIRE(exp2 == res2);
		AssignPostFixTable::clear();
	}
}
