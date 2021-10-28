#ifndef GUARD_FOLLOW_TABLE_H
#define GUARD_FOLLOW_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class FollowTable : public Table<StmtNo, StmtNo> {
public:
    static FollowTable* getInstance() {
        if (follow_table_ptr == nullptr) {
            follow_table_ptr = new FollowTable;
        }
        return follow_table_ptr;
    }
    static bool addFollow(StmtNo stmt1, StmtNo stmt2);
    static bool addFollowStar(StmtNo stmt, ListOfStmtNos stmtList);
    static bool addFollowStarBy(StmtNo stmt, ListOfStmtNos stmtList);
    static bool isFollow(StmtNo stmt1, StmtNo stmt2);
    static bool isFollowStar(StmtNo stmt1, StmtNo stmt2);
    static StmtNo getFollowedBy(StmtNo stmt2);
    static StmtNo getFollow(StmtNo stmt1);
    static ListOfStmtNos getFollowedStarBy(StmtNo stmt2);
    static ListOfStmtNos getFollowStar(StmtNo stmt1);
    static const std::unordered_map<StmtNo, StmtNo>& getFollowMap();
    static const std::unordered_map<StmtNo, ListOfStmtNos>& getFollowStarMap();
    static void clear();
private:
    //static std::unordered_map<StmtNo, StmtNo> followMap;
    //static std::unordered_map<StmtNo, StmtNo> reverseFollowMap;
    //static std::unordered_map<StmtNo, ListOfStmtNos> followStarMap;
    //static std::unordered_map<StmtNo, ListOfStmtNos> reverseFollowStarMap;

    static FollowTable* follow_table_ptr;
    static inline const size_t FOLLOW_MAP = 1;
    static inline const size_t FOLLOW_REV_MAP = 20;
    static inline const size_t FOLLOW_STAR_MAP = 3;
    static inline const size_t FOLLOW_STAR_REV_MAP = 4;

    FollowTable() {
        one_to_one_map[FOLLOW_MAP] = std::unordered_map<StmtNo, StmtNo>();
        one_to_one_rev_map[FOLLOW_REV_MAP] = std::unordered_map<StmtNo, StmtNo>();
        one_to_many_map[FOLLOW_STAR_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
        one_to_many_rev_map[FOLLOW_STAR_REV_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
    }
};

#endif // GUARD_FOLLOW_TABLE_H
