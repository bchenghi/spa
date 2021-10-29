#include "FollowTable.h"

#define INVALID_STMT_NO 0

FollowTable* FollowTable::followTablePtr = nullptr;

bool FollowTable::addFollow(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->addOneToOne(FOLLOW_MAP, stmt1, stmt2)
        && getInstance()->addOneToOneRev(FOLLOW_REV_MAP, stmt2, stmt1);
}

bool FollowTable::addFollowStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->addOneToMany(FOLLOW_STAR_MAP, stmt, stmtList);
}

bool FollowTable::addFollowStarBy(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->addOneToManyRev(FOLLOW_STAR_REV_MAP, stmt, stmtList);
}

bool FollowTable::isFollow(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->isOneToOne(FOLLOW_MAP, stmt1, stmt2);
}

bool FollowTable::isFollowStar(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->isOneToMany(FOLLOW_STAR_MAP, stmt1, stmt2);
}

StmtNo FollowTable::getFollowedBy(StmtNo stmt2)
{
    if (getInstance()->isOneToOneRevEmpty(FOLLOW_REV_MAP, stmt2)) {
        return INVALID_STMT_NO;
    }
    return getInstance()->getOneToOneRev(FOLLOW_REV_MAP, stmt2);
}

StmtNo FollowTable::getFollow(StmtNo stmt1)
{
    if (getInstance()->isOneToOneEmpty(FOLLOW_MAP, stmt1)) {
        return INVALID_STMT_NO;
    }
    return getInstance()->getOneToOne(FOLLOW_MAP, stmt1);
}

ListOfStmtNos FollowTable::getFollowedStarBy(StmtNo stmt2)
{
    return getInstance()->getOneToManyRev(FOLLOW_STAR_REV_MAP, stmt2);
}

ListOfStmtNos FollowTable::getFollowStar(StmtNo stmt1)
{
    return getInstance()->getOneToMany(FOLLOW_STAR_MAP, stmt1);
}

const std::unordered_map<StmtNo, StmtNo>& FollowTable::getFollowMap()
{
    return getInstance()->getOneToOneMap(FOLLOW_MAP);
}

const std::unordered_map<StmtNo, ListOfStmtNos>& FollowTable::getFollowStarMap()
{
    return getInstance()->getOneToManyMap(FOLLOW_STAR_MAP);
}

void FollowTable::clear()
{
    getInstance()->clearAll();
}
