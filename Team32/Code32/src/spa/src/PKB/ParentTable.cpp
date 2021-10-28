#include "ParentTable.h"

#define INVALID_STMT_NO 0

ParentTable* ParentTable::parent_table_ptr = nullptr;

bool ParentTable::addParent(StmtNo stmt1, ListOfStmtNos stmtList)
{
    bool res = getInstance()->add_one_to_many(PARENT_MAP, stmt1, stmtList);
    for (auto iter = stmtList.begin(); iter != stmtList.end(); ++iter) {
        StmtNo stmt2 = *iter;
        if (!getInstance()->is_one_to_one_rev_empty(PARENT_REV_MAP, stmt2)) {
            return false;
        }
        res &= getInstance()->add_one_to_one_rev(PARENT_REV_MAP, stmt2, stmt1);
    }
    return res;
}

bool ParentTable::addChildrenStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->add_one_to_many(PARENT_STAR_MAP, stmt, stmtList);
}

bool ParentTable::addParentStar(StmtNo stmt, ListOfStmtNos stmtList)
{
    return getInstance()->add_one_to_many_rev(PARENT_STAR_REV_MAP, stmt, stmtList);
}

bool ParentTable::isParent(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->is_one_to_many(PARENT_MAP, stmt1, stmt2);
}

bool ParentTable::isParentStar(StmtNo stmt1, StmtNo stmt2)
{
    return getInstance()->is_one_to_many(PARENT_STAR_MAP, stmt1, stmt2);
}

StmtNo ParentTable::getParent(StmtNo stmt2)
{
    if (getInstance()->is_one_to_one_rev_empty(PARENT_REV_MAP, stmt2)) {
        return INVALID_STMT_NO;
    }
    return getInstance()->get_one_to_one_rev(PARENT_REV_MAP, stmt2);
}

ListOfStmtNos ParentTable::getChildren(StmtNo stmt1)
{
    return getInstance()->get_one_to_many(PARENT_MAP, stmt1);
}

ListOfStmtNos ParentTable::getParentStar(StmtNo stmt2)
{
    return getInstance()->get_one_to_many_rev(PARENT_STAR_REV_MAP, stmt2);
}

ListOfStmtNos ParentTable::getChildrenStar(StmtNo stmt1)
{
    return getInstance()->get_one_to_many(PARENT_STAR_MAP, stmt1);
}

const std::unordered_map<StmtNo, ListOfStmtNos>& ParentTable::getParentMap()
{
    return getInstance()->get_one_to_many_map(PARENT_MAP);
}

const std::unordered_map<StmtNo, StmtNo>& ParentTable::getParentReverseMap()
{
    return getInstance()->get_one_to_one_rev_map(PARENT_REV_MAP);
}

const std::unordered_map<StmtNo, ListOfStmtNos>& ParentTable::getParentStarMap()
{
    return getInstance()->get_one_to_many_map(PARENT_STAR_MAP);
}

void ParentTable::clear()
{
    getInstance()->clearAll();
}
