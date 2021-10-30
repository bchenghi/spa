#include "ParentTable.h"

#define INVALID_STMT_NO 0

ParentTable* ParentTable::parentTablePtr = nullptr;

bool ParentTable::addParent(StmtNo stmt1, ListOfStmtNos stmtList)
{
    bool res = getInstance()->addOneToMany(PARENT_MAP, stmt1, stmtList);
    for (auto iter = stmtList.begin(); iter != stmtList.end(); ++iter) {
        StmtNo stmt2 = *iter;
        if (!getInstance()->isOneToOneRevEmpty(PARENT_REV_MAP, stmt2)) {
            return false;
        }
        res &= getInstance()->addOneToOneRev(PARENT_REV_MAP, stmt2, stmt1);
    }
    return res;
}

bool ParentTable::addChildrenStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->addOneToMany(PARENT_STAR_MAP, stmt, stmtList);
}

bool ParentTable::addParentStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->addOneToManyRev(PARENT_STAR_REV_MAP, stmt, stmtList);
}

bool ParentTable::isParent(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->isOneToMany(PARENT_MAP, stmt1, stmt2);
}

bool ParentTable::isParentStar(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->isOneToMany(PARENT_STAR_MAP, stmt1, stmt2);
}

StmtNo ParentTable::getParent(StmtNo stmt2)
{
    if (getInstance()->isOneToOneRevEmpty(PARENT_REV_MAP, stmt2)) {
        return INVALID_STMT_NO;
    }
    return getInstance()->getOneToOneRev(PARENT_REV_MAP, stmt2);
}

ListOfStmtNos ParentTable::getChildren(StmtNo stmt1)
{
    return getInstance()->getOneToMany(PARENT_MAP, stmt1);
}

ListOfStmtNos ParentTable::getParentStar(StmtNo stmt2)
{
    return getInstance()->getOneToManyRev(PARENT_STAR_REV_MAP, stmt2);
}

ListOfStmtNos ParentTable::getChildrenStar(StmtNo stmt1)
{
    return getInstance()->getOneToMany(PARENT_STAR_MAP, stmt1);
}

const std::unordered_map<StmtNo, ListOfStmtNos>& ParentTable::getParentMap()
{
    return getInstance()->getOneToManyMap(PARENT_MAP);
}

const std::unordered_map<StmtNo, StmtNo>& ParentTable::getParentReverseMap()
{
    return getInstance()->getOneToOneRevMap(PARENT_REV_MAP);
}

const std::unordered_map<StmtNo, ListOfStmtNos>& ParentTable::getParentStarMap()
{
    return getInstance()->getOneToManyMap(PARENT_STAR_MAP);
}

void ParentTable::clear()
{
    getInstance()->clearAll();
}
