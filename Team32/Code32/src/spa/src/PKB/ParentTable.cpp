#include "ParentTable.h"

#define INVALID_STMT_NO 0

std::unordered_map<StmtNo, ListOfStmtNos> ParentTable::parentMap;
std::unordered_map<StmtNo, StmtNo> ParentTable::reverseParentMap;
std::unordered_map<StmtNo, ListOfStmtNos> ParentTable::parentStarMap;
std::unordered_map<StmtNo, ListOfStmtNos> ParentTable::reverseParentStarMap;


bool ParentTable::addParent(StmtNo stmt1, ListOfStmtNos stmtList)
{
    auto res = ParentTable::parentMap.find(stmt1);
    if (res != ParentTable::parentMap.end()) {
        //I am not sure the expected behavior here when already a stmtList exist.
        //Append to the stmtList? or Return a false.
        throw "Undefined.";
    }
    else {
        ParentTable::parentMap[stmt1] = stmtList;
        for (auto iter = stmtList.begin(); iter != stmtList.end(); ++iter) {
            size_t stmtNum = *iter;
            auto res_ = ParentTable::reverseParentMap.find(stmtNum);
            if (res_ != ParentTable::reverseParentMap.end()) {
                if (res_->second == stmt1) {
                    continue;
                } else {
                    return false;
                }
            }
            else {
                ParentTable::reverseParentMap[stmtNum] = stmt1;
            }
        }
        return true;
    }
}

bool ParentTable::addChildrenStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    auto res = ParentTable::parentStarMap.find(stmt);
    if (res != ParentTable::parentStarMap.end()) {
        //I am not sure the expected behavior here when already a stmtList exist.
        //Append to the stmtList? or Return a false.
        throw "Undefined.";
    }
    else {
        ParentTable::parentStarMap[stmt] = stmtList;
        return true;
    }
}

bool ParentTable::addParentStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    auto res = ParentTable::reverseParentStarMap.find(stmt);
    if (res != ParentTable::reverseParentStarMap.end()) {
        //I am not sure the expected behavior here when already a stmtList exist.
        //Append to the stmtList? or Return a false.
        throw "Undefined.";
    }
    else {
        ParentTable::reverseParentStarMap[stmt] = stmtList;
        return true;
    }
}

bool ParentTable::isParent(StmtNo stmt1, StmtNo stmt2)
{
    auto res = ParentTable::parentMap.find(stmt1);
    if (res != ParentTable::parentMap.end()) {
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

bool ParentTable::isParentStar(StmtNo stmt1, StmtNo stmt2)
{
    auto res = ParentTable::parentStarMap.find(stmt1);
    if (res != ParentTable::parentStarMap.end()) {
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

StmtNo ParentTable::getParent(StmtNo stmt2)
{
    auto res = ParentTable::reverseParentMap.find(stmt2);
    if (res != ParentTable::reverseParentMap.end()) {
        return res->second;
    }
    else {
        return INVALID_STMT_NO;
    }
}

ListOfStmtNos ParentTable::getChildren(StmtNo stmt1)
{
    auto res = ParentTable::parentMap.find(stmt1);
    if (res != ParentTable::parentMap.end()) {
        return res->second;
    }
    else {
        return ListOfStmtNos();
    }
}

ListOfStmtNos ParentTable::getParentStar(StmtNo stmt2)
{
    auto res = ParentTable::reverseParentStarMap.find(stmt2);
    if (res != ParentTable::reverseParentStarMap.end()) {
        return res->second;
    }
    else {
        return ListOfStmtNos();
    }
}

ListOfStmtNos ParentTable::getChildrenStar(StmtNo stmt1)
{
    auto res = ParentTable::parentStarMap.find(stmt1);
    if (res != ParentTable::parentStarMap.end()) {
        return res->second;
    }
    else {
        return ListOfStmtNos();
    }
}

const std::unordered_map<StmtNo, ListOfStmtNos>& ParentTable::getParentMap()
{
    return parentMap;
}

const std::unordered_map<StmtNo, StmtNo>& ParentTable::getParentReverseMap()
{
    return reverseParentMap;
}

const std::unordered_map<StmtNo, ListOfStmtNos>& ParentTable::getParentStarMap()
{
    return parentStarMap;
}

void ParentTable::clear()
{
    parentMap.clear();
    reverseParentMap.clear();
    parentStarMap.clear();
    reverseParentStarMap.clear();
}
