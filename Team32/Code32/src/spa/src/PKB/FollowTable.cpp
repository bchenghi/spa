#include "FollowTable.h"

#include <unordered_map>

#define INVALID_STMT_NO 0

std::unordered_map<StmtNo, StmtNo> FollowTable::followMap;
std::unordered_map<StmtNo, StmtNo> FollowTable::reverseFollowMap;
std::unordered_map<StmtNo, ListOfStmtNos> FollowTable::followStarMap;
std::unordered_map<StmtNo, ListOfStmtNos> FollowTable::reverseFollowStarMap;

bool FollowTable::addFollow(StmtNo stmt1, StmtNo stmt2)
{
    auto res = FollowTable::followMap.find(stmt1);
    if (res != FollowTable::followMap.end()) {
        if (res->second == stmt2) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        FollowTable::followMap[stmt1] = stmt2;
        FollowTable::reverseFollowMap[stmt2] = stmt1;
        return true;
    }
}

bool FollowTable::addFollowStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    auto res = FollowTable::followStarMap.find(stmt);
    if (res != FollowTable::followStarMap.end()) {
        //I am not sure the expected behavior here when already a stmtList exist.
        //Append to the stmtList? or Return a false.
        throw "Undefined.";
    }
    else {
        FollowTable::followStarMap[stmt] = stmtList;
        return true;
    }
}

bool FollowTable::addFollowStarBy(StmtNo stmt, ListOfStmtNos stmtList)
{
    auto res = FollowTable::reverseFollowStarMap.find(stmt);
    if (res != FollowTable::reverseFollowStarMap.end()) {
        //I am not sure the expected behavior here when already a stmtList exist.
        //Append to the stmtList? or Return a false.
        throw "Undefined.";
    }
    else {
        FollowTable::reverseFollowStarMap[stmt] = stmtList;
        return true;
    }
}

bool FollowTable::isFollow(StmtNo stmt1, StmtNo stmt2)
{
    auto res = FollowTable::followMap.find(stmt1);
    if (res != FollowTable::followMap.end()) {
        if (res->second == stmt2) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool FollowTable::isFollowStar(StmtNo stmt1, StmtNo stmt2)
{
    auto res = FollowTable::followStarMap.find(stmt1);
    if (res != FollowTable::followStarMap.end()) {
        if (res->second.count(stmt2) == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

StmtNo FollowTable::getFollowedBy(StmtNo stmt2)
{
    auto res = FollowTable::reverseFollowMap.find(stmt2);
    if (res != FollowTable::reverseFollowMap.end()) {
        return res->second;
    }
    else {
        return INVALID_STMT_NO;
    }
}

StmtNo FollowTable::getFollow(StmtNo stmt1)
{
    auto res = FollowTable::followMap.find(stmt1);
    if (res != FollowTable::followMap.end()) {
        return res->second;
    }
    else {
        return INVALID_STMT_NO;
    }
}

ListOfStmtNos FollowTable::getFollowedStarBy(StmtNo stmt2)
{
    auto res = FollowTable::reverseFollowStarMap.find(stmt2);
    if (res != FollowTable::reverseFollowStarMap.end()) {
        return res->second;
    }
    else {
        return ListOfStmtNos();
    }
}

ListOfStmtNos FollowTable::getFollowStar(StmtNo stmt1)
{
    auto res = FollowTable::followStarMap.find(stmt1);
    if (res != FollowTable::followStarMap.end()) {
        return res->second;
    }
    else {
        return ListOfStmtNos();
    }
}

const std::unordered_map<StmtNo, StmtNo>& FollowTable::getFollowMap()
{
    return followMap;
}

const std::unordered_map<StmtNo, ListOfStmtNos>& FollowTable::getFollowStarMap()
{
    return followStarMap;
}

void FollowTable::clear()
{
    followMap.clear();
    followStarMap.clear();
    reverseFollowStarMap.clear();
    reverseFollowMap.clear();
}
