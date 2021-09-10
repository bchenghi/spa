#ifndef GUARD_PARENT_TABLE_H
#define GUARD_PARENT_TABLE_H

#include <unordered_map>
#include <unordered_set>

using std::unordered_map;
using std::unordered_set;

typedef int STMT_NO;
typedef unordered_set<int> LIST_OF_STMT_NO;

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

private:
    static unordered_map<STMT_NO, LIST_OF_STMT_NO> parentMap;
    static unordered_map<STMT_NO, STMT_NO> reverseParentMap;
    static unordered_map<STMT_NO, LIST_OF_STMT_NO> parentStarMap;
    static unordered_map<STMT_NO, LIST_OF_STMT_NO> reverseParentStarMap;
};

#endif // GUARD_PARENT_TABLE_H