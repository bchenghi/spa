#ifndef GUARD_PARENT_TABLE_H
#define GUARD_PARENT_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class ParentTable {
public:
    static bool addParent(StmtNo stmt1, ListOfStmtNos stmtList);
    static bool addChildrenStar(StmtNo stmt, ListOfStmtNos stmtList);
    static bool addParentStar(StmtNo stmt, ListOfStmtNos stmtList);
    static bool isParent(StmtNo stmt1, StmtNo stmt2);
    static bool isParentStar(StmtNo stmt1, StmtNo stmt2);
    static StmtNo getParent(StmtNo stmt2);
    static ListOfStmtNos getChildren(StmtNo stmt1);
    static ListOfStmtNos getParentStar(StmtNo stmt2);
    static ListOfStmtNos getChildrenStar(StmtNo stmt1);
    static const std::unordered_map<StmtNo , ListOfStmtNos>& getParentMap();
    static const std::unordered_map<StmtNo, StmtNo>& getParentReverseMap();
    static const std::unordered_map<StmtNo , ListOfStmtNos>& getParentStarMap();
    static void clear();
private:
    static std::unordered_map<StmtNo, ListOfStmtNos> parentMap;
    static std::unordered_map<StmtNo, StmtNo> reverseParentMap;
    static std::unordered_map<StmtNo, ListOfStmtNos> parentStarMap;
    static std::unordered_map<StmtNo, ListOfStmtNos> reverseParentStarMap;
};

#endif // GUARD_PARENT_TABLE_H
