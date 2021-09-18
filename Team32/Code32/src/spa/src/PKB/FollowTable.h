#ifndef GUARD_FOLLOW_TABLE_H
#define GUARD_FOLLOW_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class FollowTable {
public:
    static bool addFollow(STMT_NO stmt1, STMT_NO stmt2);
    static bool addFollowStar(STMT_NO stmt, LIST_OF_STMT_NO stmtList);
    static bool addFollowStarBy(STMT_NO stmt, LIST_OF_STMT_NO stmtList);
    static bool isFollow(STMT_NO stmt1, STMT_NO stmt2);
    static bool isFollowStar(STMT_NO stmt1, STMT_NO stmt2);
    static STMT_NO getFollowedBy(STMT_NO stmt2);
    static STMT_NO getFollow(STMT_NO stmt1);
    static LIST_OF_STMT_NO getFollowedStarBy(STMT_NO stmt2);
    static LIST_OF_STMT_NO getFollowStar(STMT_NO stmt1);
    static const std::unordered_map<STMT_NO, STMT_NO>& getFollowMap();
    static const std::unordered_map<STMT_NO, LIST_OF_STMT_NO>& getFollowStarMap();
    static void clear();
private:
    static std::unordered_map<STMT_NO, STMT_NO> followMap;
    static std::unordered_map<STMT_NO, STMT_NO> reverseFollowMap;
    static std::unordered_map<STMT_NO, LIST_OF_STMT_NO> followStarMap;
    static std::unordered_map<STMT_NO, LIST_OF_STMT_NO> reverseFollowStarMap;
};

#endif // GUARD_FOLLOW_TABLE_H
