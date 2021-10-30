#include "catch.hpp"

#include "PKB/FollowTable.h"
#include "PKB/TypeToStmtNumTable.h"
#include "pql/DesignEntity.h"
#include "pql/PkbAbstractor/PkbAbstractor.h"
#include "pql/PkbAbstractor/PkbAbstractorHelper.h"


#include <iostream>

using pql::PkbAbstractor;

TEST_CASE("PkbAbstractor", "[pkb abstractor]") {
    //FollowTable followTable;
    //TypeToStmtNumTable typeToStmtNumTable;
    PkbAbstractor pkbAbstractor;

    //NextTable nextTable;
    pql::PkbAbstractorHelper pkbAbstractorHelper;

    // Follows
//    SECTION("getDataFromFollows() should return values if first argument is stmt num and second argument is matching design entity") {
//        // Case: (num, entity)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(1, pql::DesignEntity::NONE, -1, pql::DesignEntity::ASSIGN);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2)};
//        REQUIRE(output == expected);
//    }
//
//    SECTION("getDataFromFollows() should return values if first argument is stmt num and second argument is wildcard") {
//        // Case: (num, _)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(1, pql::DesignEntity::NONE, -1, pql::DesignEntity::NONE);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2)};
//        REQUIRE(output == expected);
//    }
//
//    SECTION("getDataFromFollows() should return values if first argument is stmt num and second argument is stmt num") {
//        // Case: (num, num)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(1, pql::DesignEntity::NONE, 2, pql::DesignEntity::NONE);
//        list<pair<StmtNum, StmtNum>> expected = {pair<StmtNum, StmtNum>(1, 2)};
//        REQUIRE(output == expected);
//    }
//
//    SECTION("getDataFromFollows() should return values if first argument is entity and second argument is stmt num") {
//        // Case: (entity, num)
//        followTable.addFollow(1, 2);
//        followTable.addFollow(2, 3);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 1);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 2);
//        typeToStmtNumTable.addStmtWithType(pql::DesignEntity::ASSIGN, 3);
//        list<pair<StmtNum, StmtNum>> output = pkbAbstractor.getDataFromFollows(-1, pql::DesignEntity::WHILE, 2, pql::DesignEntity::NONE);
//        list<pair<StmtNum, StmtNum>> expected = {};
//        REQUIRE(output == expected);
//        followTable.clear();
//        typeToStmtNumTable.clear();
//    }

//    SECTION("test dfs") {
//        nextTable.addNext(1, 2);
//        nextTable.addNext(2, 3);
//        nextTable.addNext(2, 4);
//        nextTable.addNext(3, 5);
//        nextTable.addNext(4, 5);
//
//        list<vector<StmtNum>> output = pkbAbstractorHelper.getAllPaths(1, 5);
//        list<vector<StmtNum>> expected;
//        vector<StmtNum> path1 = { 1, 2, 3, };
//        for (vector<StmtNum> list: output) {
//            for (StmtNum num: list) {
//                std::cout << num << " ";
//            }
//        }
//    }

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
