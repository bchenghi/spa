#include "FollowTable.h"

#define INVALID_STMT_NO 0

FollowTable* FollowTable::follow_table_ptr = nullptr;

bool FollowTable::addFollow(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->add_one_to_one(FOLLOW_MAP, stmt1, stmt2)
        && getInstance()->add_one_to_one_rev(FOLLOW_REV_MAP, stmt2, stmt1);
}

bool FollowTable::addFollowStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->add_one_to_many(FOLLOW_STAR_MAP, stmt, stmtList);
}

bool FollowTable::addFollowStarBy(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->add_one_to_many_rev(FOLLOW_STAR_REV_MAP, stmt, stmtList);
}

bool FollowTable::isFollow(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->is_one_to_one(FOLLOW_MAP, stmt1, stmt2);
}

bool FollowTable::isFollowStar(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->is_one_to_many(FOLLOW_STAR_MAP, stmt1, stmt2);
}

StmtNo FollowTable::getFollowedBy(StmtNo stmt2)
{
    if (getInstance()->is_one_to_one_rev_empty(FOLLOW_REV_MAP,stmt2)) {
        return INVALID_STMT_NO;
    }
    return getInstance()->get_one_to_one_rev(FOLLOW_REV_MAP, stmt2);
}

StmtNo FollowTable::getFollow(StmtNo stmt1)
{
    if (getInstance()->is_one_to_one_empty(FOLLOW_MAP, stmt1)) {
        return INVALID_STMT_NO;
    }
    return getInstance()->get_one_to_one(FOLLOW_MAP, stmt1);
}

ListOfStmtNos FollowTable::getFollowedStarBy(StmtNo stmt2)
{
    return getInstance()->get_one_to_many_rev(FOLLOW_STAR_REV_MAP, stmt2);
}

ListOfStmtNos FollowTable::getFollowStar(StmtNo stmt1)
{
    return getInstance()->get_one_to_many(FOLLOW_STAR_MAP, stmt1);
}

const std::unordered_map<StmtNo, StmtNo>& FollowTable::getFollowMap()
{
    return getInstance()->get_one_to_one_map(FOLLOW_MAP);
}

const std::unordered_map<StmtNo, ListOfStmtNos>& FollowTable::getFollowStarMap()
{
    return getInstance()->get_one_to_many_map(FOLLOW_STAR_MAP);
}

void FollowTable::clear()
{
    getInstance()->clearAll();
}
