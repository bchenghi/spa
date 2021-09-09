#ifndef GUARD_FOLLOW_TABLE_H
#define GUARD_FOLLOW_TABLE_H

#include <unordered_map>
#include <unordered_set>

using std::unordered_map;
using std::unordered_set;

typedef int STMT_NO;
typedef unordered_set<int> LIST_OF_STMT_NO;

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

private:
    static unordered_map<STMT_NO, STMT_NO> followMap;
    static unordered_map<STMT_NO, STMT_NO> reverseFollowMap;
    static unordered_map<STMT_NO, LIST_OF_STMT_NO> followStarMap;
    static unordered_map<STMT_NO, LIST_OF_STMT_NO> reverseFollowStarMap;
};

#endif // GUARD_FOLLOW_TABLE_H