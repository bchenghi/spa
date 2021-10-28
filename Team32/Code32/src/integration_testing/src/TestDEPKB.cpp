#include "catch.hpp"

#include "PKB/CallTable.h"
#include "PKB/FollowTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ParentTable.h"
#include "PKB/ProcTable.h"
#include "PKB/TypeToStmtNumTable.h"
#include "PKB/UseTable.h"
#include "simple/SourceProcessor/DesignExtractor.h"
#include "Utils/TestUtils.h"

TEST_CASE("Design extractor and PKB integration") {
    SECTION("Design extractor can extract transitive relation") {
        clearPKB();

        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 1);

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

        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 4);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 3);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::ASSIGN, 2);
        TypeToStmtNumTable::addStmtWithType(pql::DesignEntity::WHILE, 1);

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

        REQUIRE(modifyRes == modifyExp);
    }
}

TEST_CASE("Test call feature") {
    SECTION("Design extractor can check whether the call graph is a DAG") {
        clearPKB();
        ProcTable::addProc("A", {1});
        ProcTable::addProc("B", {2});
        CallTable::addCall("A", "B");
        CallTable::addCall("B", "A");

        simple::DesignExtractor designExtractor;
        REQUIRE_THROWS(designExtractor.extractDesign());
    }

    SECTION("Design extractor can extract transitive call") {
        clearPKB();
        ProcTable::addProc("A", {1});
        ProcTable::addProc("B", {2});
        ProcTable::addProc("C", {3});
        CallTable::addCall("A", "B");
        CallTable::addCall("B", "C");

        simple::DesignExtractor designExtractor;
        designExtractor.extractDesign();

        ListOfProcNames  list = CallTable::getCallStar("A");
        ListOfProcNames  exp = {"B", "C"};

        REQUIRE(list == exp);

        ListOfProcNames  list1 = CallTable::getCallStar("B");
        ListOfProcNames  exp1 = {"C"};
        REQUIRE(list1 == exp1);
    }
}

TEST_CASE("ModifiesP and UsesP") {
    clearPKB();
    ProcTable::addProc("A", {1});
    ProcTable::addProc("B", {2});
    ProcTable::addProc("C", {3});
    CallTable::addCall("A", "B");
    CallTable::addCall("B", "C");
    UseTable::addProcUse("A", "x");
    UseTable::addProcUse("B", "y");
    UseTable::addProcUse("C", "z");
    ModifyTable::addProcModify("A", "x");
    ModifyTable::addProcModify("B", "y");
    ModifyTable::addProcModify("C", "z");

    simple::DesignExtractor designExtractor;
    designExtractor.extractDesign();

    ListOfVarNames useA = UseTable::getProcUse("A");
    ListOfVarNames useB = UseTable::getProcUse("B");
    ListOfVarNames useC = UseTable::getProcUse("C");

    ListOfVarNames modifyA = ModifyTable::getProcModify("A");
    ListOfVarNames modifyB = ModifyTable::getProcModify("B");
    ListOfVarNames modifyC = ModifyTable::getProcModify("C");

    ListOfVarNames expA = {"x", "y", "z"};
    ListOfVarNames expB = {"y", "z"};
    ListOfVarNames expC = {"z"};

    REQUIRE(expA == useA);
    REQUIRE(expA == modifyA);

    REQUIRE(expB == useB);
    REQUIRE(expB == modifyB);

    REQUIRE(expC == useC);
    REQUIRE(expC == modifyC);
}