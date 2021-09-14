#include "catch.hpp"
#include <iostream>

#include "pql/PkbAbstractor/PkbAbstractor.h"
#include "pql/DesignEntity.h"
#include "PKB/FollowTable.h"
#include "PKB/TypeToStmtNumTable.h"
//#include "Stubs/FollowTableStub.cpp"

//using PkbAbsTest::FollowTableStub;

using pql::PkbAbstractor;

// For each function, test all the args, valid and invalid

TEST_CASE("PkbAbstractor", "[pkb abstractor]") {
//    FollowTableStub followTableStub;
    FollowTable followTable;
    TypeToStmtNumTable typeToStmtNumTable;
    PkbAbstractor pkbAbstractor;

    // Follows
    SECTION("getDataFromFollows() should return values if first argument is stmt num and second argument is matching design entity") {
        // Case: (num, entity)
        followTable.addFollow(1, 2);
        followTable.addFollow(2, 3);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(1, pql::DesignEntity::None, -1, pql::DesignEntity::Assign);
        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2)};
        REQUIRE(output == expected);
    }

    SECTION("getDataFromFollows() should return values if first argument is stmt num and second argument is wildcard") {
        // Case: (num, _)
        followTable.addFollow(1, 2);
        followTable.addFollow(2, 3);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(1, pql::DesignEntity::None, -1, pql::DesignEntity::None);
        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2)};
        REQUIRE(output == expected);
    }

    SECTION("getDataFromFollows() should return values if first argument is stmt num and second argument is stmt num") {
        // Case: (num, num)
        followTable.addFollow(1, 2);
        followTable.addFollow(2, 3);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(1, pql::DesignEntity::None, 2, pql::DesignEntity::None);
        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2)};
        REQUIRE(output == expected);
    }

    SECTION("getDataFromFollows() should return values if first argument is entity and second argument is stmt num") {
        // Case: (entity, num)
        followTable.addFollow(1, 2);
        followTable.addFollow(2, 3);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(-1, pql::DesignEntity::While, 2, pql::DesignEntity::None);
        list<pair<StmtNum, StmtNum>> expected = {};
        REQUIRE(output == expected);
    }

//    SECTION("getDataFromFollows() should return values if first argument is entity and second argument is wildcard") {
//        // Case: (entity, _)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(-1, pql::DesignEntity::Assign, -1, pql::DesignEntity::None);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2), pair<StmtNum, StmtNum>(2, 3)};
//        REQUIRE(output == expected);
//    }

//    SECTION("getDataFromFollows() should return values if first argument is wildcard and second argument is entity") {
//        // Case: (_, entity)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(-1, pql::DesignEntity::None, -1, pql::DesignEntity::Assign);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2), pair<StmtNum, StmtNum>(2, 3)};
//        REQUIRE(output == expected);
//    }

//    SECTION("getDataFromFollows() should return values if first argument is wildcard and second argument is num") {
//        // Case: (_, num)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(-1, pql::DesignEntity::None, 2, pql::DesignEntity::None);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2)};
//        for (auto pair: output) {
//            std::cout << pair.first<< "," << pair.second << "\n";
//        }
//        // getFollowedBy() does not seem to return the right value
//        REQUIRE(output == expected);
//    }

//    SECTION("getDataFromFollows() should return values if first argument is entity and second argument is entity") {
//        // Case: (entity, entity)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
//        std::cout << TypeToStmtNumTable::getTypeOfStmt(1);
//
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(-1, pql::DesignEntity::Assign, -1, pql::DesignEntity::Assign);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2), pair<StmtNum, StmtNum>(2, 3)};
//        // getting none stmt type unexpected error
//            // is it cos the for loop overshoots?
//        REQUIRE(output == expected);
//    }

    // FollowsStar
//    SECTION("getDataFromFollowsStar() should return values if first argument is stmt num and second argument is matching design entity") {
//        // Case: (num, entity)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        followTable.addFollowStar(1, {2, 3});
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::Assign, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollowsStar(1, pql::DesignEntity::None, -1, pql::DesignEntity::Assign);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 3), pair<StmtNum, StmtNum>(1, 2)};
//        for (auto pair: output) {
//            std::cout << pair.first<< "," << pair.second << "\n";
//        }
//
//        REQUIRE(output == expected);
//    }

}