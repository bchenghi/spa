#ifndef GUARD_FOLLOW_TABLE_H
#define GUARD_FOLLOW_TABLE_H

#include "TypePreDefine.h"
#include "Table.h"

class FollowTable : public Table<StmtNo, StmtNo> {
public:
    static FollowTable* getInstance() {
        if (followTablePtr == nullptr) {
            followTablePtr = new FollowTable;
        }
        return followTablePtr;
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
    static FollowTable* followTablePtr;
    static inline const size_t FOLLOW_MAP = 1;
    static inline const size_t FOLLOW_REV_MAP = 2;
    static inline const size_t FOLLOW_STAR_MAP = 3;
    static inline const size_t FOLLOW_STAR_REV_MAP = 4;

    FollowTable() {
        oneToOneMap[FOLLOW_MAP] = std::unordered_map<StmtNo, StmtNo>();
        oneToOneRevMap[FOLLOW_REV_MAP] = std::unordered_map<StmtNo, StmtNo>();
        oneToManyMap[FOLLOW_STAR_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
        oneToManyRevMap[FOLLOW_STAR_REV_MAP] = std::unordered_map<StmtNo, ListOfStmtNos>();
    }
};

#endif
