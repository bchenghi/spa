#ifndef GUARD_PARENT_TABLE_H
#define GUARD_PARENT_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class ParentTable : public Table<StmtNo, StmtNo> {
public:
    static ParentTable* getInstance() {
        if (parent_table_ptr == nullptr) {
            parent_table_ptr = new ParentTable;
        }
        return parent_table_ptr;
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
    //static std::unordered_map<StmtNo, ListOfStmtNos> parentMap;
    //static std::unordered_map<StmtNo, StmtNo> reverseParentMap;
    //static std::unordered_map<StmtNo, ListOfStmtNos> parentStarMap;
    //static std::unordered_map<StmtNo, ListOfStmtNos> reverseParentStarMap;

    static ParentTable* parent_table_ptr;
    static inline const size_t PARENT_MAP = 1;
    static inline const size_t PARENT_REV_MAP = 22;
    static inline const size_t PARENT_STAR_MAP = 3;
    static inline const size_t PARENT_STAR_REV_MAP = 4;

    ParentTable() {
        one_to_many_map[PARENT_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
        one_to_one_rev_map[PARENT_REV_MAP] = std::unordered_map<StmtNo, StmtNo>();
        one_to_many_map[PARENT_STAR_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
        one_to_many_rev_map[PARENT_STAR_REV_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
    }
};

#endif // GUARD_PARENT_TABLE_H
