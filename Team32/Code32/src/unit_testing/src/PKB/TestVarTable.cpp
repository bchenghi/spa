#include "catch.hpp"
#include "Utils/TestUtils.h"

#include "PKB/VarTable.h"

TEST_CASE("Testing Variable Table","[vartable]") {
	SECTION("test getVarName()") {
		VarTable::clear();
		VarTable::addVar("t");
		VAR_NAME exp = "t";
		VAR_NAME res = VarTable::getVarName(1);

		REQUIRE(exp == res);
		VarTable::clear();
	}

	SECTION("test getAllVarName()") {
		VarTable::clear();
		VarTable::addVar("x");
		VarTable::addVar("y");
		VarTable::addVar("a");
		VarTable::addVar("b");

		LIST_OF_VAR_NAME exp = { "y", "x", "a", "b" };
		LIST_OF_VAR_NAME res = VarTable::getAllVarName();

		REQUIRE(exp == res);
		VarTable::clear();
	}

	SECTION("test size") {
		VarTable::clear();
		VarTable::addVar("x");
		VarTable::addVar("y");
		VarTable::addVar("a");
		VarTable::addVar("b");

		size_t exp = 4;
		size_t res = VarTable::getSize();

		REQUIRE(exp == res);
		VarTable::clear();
	}

	SECTION("test index") {
		VarTable::clear();
		VarTable::addVar("x");
		VarTable::addVar("y");
		VarTable::addVar("a");
		VarTable::addVar("b");

		VAR_INDEX exp = 4;
		VAR_INDEX res = VarTable::getVarIndex("b");

		REQUIRE(exp == res);
		VarTable::clear();
	}
}