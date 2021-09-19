#ifndef GUARD_FOLLOW_TABLE_H
#define GUARD_FOLLOW_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class FollowTable {
public:
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
    static std::unordered_map<StmtNo, StmtNo> followMap;
    static std::unordered_map<StmtNo, StmtNo> reverseFollowMap;
    static std::unordered_map<StmtNo, ListOfStmtNos> followStarMap;
    static std::unordered_map<StmtNo, ListOfStmtNos> reverseFollowStarMap;
};

#endif // GUARD_FOLLOW_TABLE_H
