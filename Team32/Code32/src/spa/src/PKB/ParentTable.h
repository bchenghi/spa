#ifndef GUARD_PARENT_TABLE_H
#define GUARD_PARENT_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class ParentTable {
public:
    static bool addParent(STMT_NO stmt1, LIST_OF_STMT_NO stmtList);
    static bool addChildrenStar(STMT_NO stmt, LIST_OF_STMT_NO stmtList);
    static bool addParentStar(STMT_NO stmt, LIST_OF_STMT_NO stmtList);
    static bool isParent(STMT_NO stmt1, STMT_NO stmt2);
    static bool isParentStar(STMT_NO stmt1, STMT_NO stmt2);
    static STMT_NO getParent(STMT_NO stmt2);
    static LIST_OF_STMT_NO getChildren(STMT_NO stmt1);
    static LIST_OF_STMT_NO getParentStar(STMT_NO stmt2);
    static LIST_OF_STMT_NO getChildrenStar(STMT_NO stmt1);
    static const std::unordered_map<STMT_NO , LIST_OF_STMT_NO>& getParentMap();
    static const std::unordered_map<STMT_NO, STMT_NO>& getParentReverseMap();
    static const std::unordered_map<STMT_NO , LIST_OF_STMT_NO>& getParentStarMap();
    static void clear();
private:
    static std::unordered_map<STMT_NO, LIST_OF_STMT_NO> parentMap;
    static std::unordered_map<STMT_NO, STMT_NO> reverseParentMap;
    static std::unordered_map<STMT_NO, LIST_OF_STMT_NO> parentStarMap;
    static std::unordered_map<STMT_NO, LIST_OF_STMT_NO> reverseParentStarMap;
};

#endif // GUARD_PARENT_TABLE_H
