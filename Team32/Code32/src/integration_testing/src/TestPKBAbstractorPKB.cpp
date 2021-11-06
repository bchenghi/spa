#include "catch.hpp"

#include "PKB/FollowTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ProcTable.h"
#include "PKB/UseTable.h"
#include "pql/PkbAbstractor/PkbAbstractor.h"

using pql::PkbAbstractor;
using pql::DesignEntity;
using pql::AttributeType;

TEST_CASE("Test PKBAbstractor and PKB integration") {
    PkbAbstractor pkbAbstractor;
    SECTION("Test valid affects relation") {
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 2);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 3);
        ModifyTable::addStmtModify(1, "v");
        UseTable::addStmtUse(3, "v");
        ProcTable::addProc("proc", {1, 2, 3});
        NextTable::addNext(1,2);
        NextTable::addNext(2,3);
        list<pair<StmtNum, StmtNum>> obtainedResult = pkbAbstractor.getAffects(1, 3);
        list<pair<StmtNum, StmtNum>> requiredResult = {{1,3}};
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        REQUIRE(obtainedResult == requiredResult);
    }

    SECTION("Test invalid affects relation") {
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 2);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 3);
        ModifyTable::addStmtModify(1, "v");
        ModifyTable::addStmtModify(2, "v");
        UseTable::addStmtUse(3, "v");
        ProcTable::addProc("proc", {1, 2, 3});
        NextTable::addNext(1,2);
        NextTable::addNext(2,3);
        list<pair<StmtNum, StmtNum>> obtainedResult = pkbAbstractor.getAffects(1, 3);
        list<pair<StmtNum, StmtNum>> requiredResult = {};
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        REQUIRE(obtainedResult == requiredResult);
    }

    SECTION("Test affects star relation") {
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 2);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 3);
        ModifyTable::addStmtModify(1, "v");
        UseTable::addStmtUse(3, "v");
        ProcTable::addProc("proc", {1, 2, 3});
        NextTable::addNext(1,2);
        NextTable::addNext(2,3);
        list<pair<StmtNum, StmtNum>> obtainedResult = pkbAbstractor.getAffectsStar(1, 3);
        list<pair<StmtNum, StmtNum>> requiredResult = {{1,3}};
        pkbAbstractor.clear();
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        REQUIRE(obtainedResult == requiredResult);
    }

    SECTION("Test invalid affects star relation") {
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 2);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::ASSIGN, 3);
        ModifyTable::addStmtModify(1, "v");
        ModifyTable::addStmtModify(2, "v");
        UseTable::addStmtUse(3, "v");
        ProcTable::addProc("proc", {1, 2, 3});
        NextTable::addNext(1,2);
        NextTable::addNext(2,3);
        list<pair<StmtNum, StmtNum>> obtainedResult = pkbAbstractor.getAffectsStar(1, 3);
        list<pair<StmtNum, StmtNum>> requiredResult = {};
        pkbAbstractor.clear();
        TypeToStmtNumTable::clear();
        ModifyTable::clear();
        UseTable::clear();
        ProcTable::clear();
        NextTable::clear();
        REQUIRE(obtainedResult == requiredResult);
    }

    SECTION("Test with relation") {
        TypeToStmtNumTable::clear();
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::STMT, 2);
        list<pair<Value, Value>> obtainedResult =
                pkbAbstractor.getWith(DesignEntity::STMT, AttributeType::STMT_NUM,
                                      DesignEntity::PROGRAM_LINE, AttributeType::NONE);

        list<pair<Value, Value>> expectedResult = {{"1","1"}, {"2","2"}};
        TypeToStmtNumTable::clear();
        REQUIRE(expectedResult == obtainedResult);
        TypeToStmtNumTable::clear();
        CallStmtTable::clear();
        UseTable::clear();
        CallStmtTable::insert(1, "a");
        ModifyTable::addStmtModify(2, "a");
        TypeToStmtNumTable::addStmtWithType(DesignEntity::CALL, 1);
        TypeToStmtNumTable::addStmtWithType(DesignEntity::READ, 2);
        obtainedResult =
                pkbAbstractor.getWith(DesignEntity::READ, AttributeType::VARIABLE_NAME,
                                      DesignEntity::CALL, AttributeType::PROCEDURE_NAME);

        expectedResult = {{"2","1"}};
        TypeToStmtNumTable::clear();
        CallStmtTable::clear();
        UseTable::clear();
        REQUIRE(expectedResult == obtainedResult);
    }
}