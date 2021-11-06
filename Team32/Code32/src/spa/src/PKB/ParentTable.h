#ifndef GUARD_PARENT_TABLE_H
#define GUARD_PARENT_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class ParentTable : public Table<StmtNo, StmtNo> {
public:
    static ParentTable* getInstance() {
        if (parentTablePtr == nullptr) {
            parentTablePtr = new ParentTable;
        }
        return parentTablePtr;
    }
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
    static ParentTable* parentTablePtr;
    static inline const size_t PARENT_MAP = 1;
    static inline const size_t PARENT_REV_MAP = 2;
    static inline const size_t PARENT_STAR_MAP = 3;
    static inline const size_t PARENT_STAR_REV_MAP = 4;

    ParentTable() {
        oneToManyMap[PARENT_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
        oneToOneRevMap[PARENT_REV_MAP] = std::unordered_map<StmtNo, StmtNo>();
        oneToManyMap[PARENT_STAR_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
        oneToManyRevMap[PARENT_STAR_REV_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
    }
};

#endif
