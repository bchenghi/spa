#include "PkbAbstractor.h"
#include "PkbAbstractorHelper.h"

#define INVALID_STMT_NO 0

#include <string>
#include <vector>

using namespace std;

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getDataFromFollows(
        StmtNum stmtNum1,
        DesignEntity designEntity1,
        StmtNum stmtNum2,
        DesignEntity designEntity2
) {
    list<pair<StmtNum, StmtNum>> results;

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        // Case: follows(NUM, ENTITY)
        StmtNum stmtNumAft = FollowTable::getFollow(stmtNum1);

        if (stmtNumAft != INVALID_STMT_NO) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(stmtNumAft);

            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(stmtNum1, stmtNumAft));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: follows(NUM, _)
        StmtNum stmtNumAft = FollowTable::getFollow(stmtNum1);
        if (stmtNumAft != INVALID_STMT_NO) {
            results.push_back(make_pair(stmtNum1, stmtNumAft));
        }
    } else if (isNumNumFormat) {
        // Case: (NUM, NUM)
        bool isFollows = FollowTable::isFollow(stmtNum1, stmtNum2);
        if (isFollows) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isEntityNumFormat) {
        // Case: (ENTITY, NUM)
        StmtNum stmtNumBef = FollowTable::getFollowedBy(stmtNum2);
        if (stmtNumBef != INVALID_STMT_NO) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(stmtNumBef);
            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(stmtNumBef, stmtNum2));
            }
        }
    } else if (isEntityWildcardFormat) {
        // Case: (ENTITY, _)
        // get all entity stmt nums, check if there is something aft
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            StmtNum stmtNumAft = FollowTable::getFollow(*itEntityStmtNums);

            if (stmtNumAft != INVALID_STMT_NO) {
                results.push_back(make_pair(*itEntityStmtNums, stmtNumAft));
            }
        }
    } else if (isWildcardEntityFormat) {
        //Case: (_, ENTITY)
        // get all entity stmt nums, check if there is something before
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity2); //list of 1, 2, 3
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            StmtNum stmtNumBef = FollowTable::getFollowedBy(*itEntityStmtNums);

            if (stmtNumBef != INVALID_STMT_NO) {
                results.push_back(make_pair(stmtNumBef, *itEntityStmtNums));
            }
        }
    } else if (isWildcardNumFormat) {
        // Case: (_, num)
        StmtNum stmtNumBef = FollowTable::getFollowedBy(stmtNum2);
        if (stmtNumBef != INVALID_STMT_NO) {
            results.push_back(make_pair(stmtNumBef, stmtNum2));
        }
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        ListOfStmtNos stmtNumsOfLHSEntity = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator it;
        for (it = stmtNumsOfLHSEntity.begin(); it != stmtNumsOfLHSEntity.end(); ++it) {
            StmtNum stmtNumAft = FollowTable::getFollow(*it);
            if (stmtNumAft != INVALID_STMT_NO) {
                DesignEntity designEntityAft = TypeToStmtNumTable::getTypeOfStmt(stmtNumAft);
                if (designEntity2 == DesignEntity::STMT || designEntityAft == designEntity2) {
                    results.push_back(make_pair(*it, stmtNumAft));
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        // Case: (_,_)
        // iterate through all stmt nums and get their follows
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            StmtNum followStmt = FollowTable::getFollow(i);
            if (followStmt != INVALID_STMT_NO) {
                results.push_back(make_pair(i, followStmt));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getDataFromFollowsStar(
        StmtNum stmtNum1,
        DesignEntity designEntity1,
        StmtNum stmtNum2,
        DesignEntity designEntity2
) {
    list<pair<StmtNum, StmtNum>> results;

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        // Case: (NUM, ENTITY)
        ListOfStmtNos listOfStmtNumAft = FollowTable::getFollowStar(stmtNum1);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumAft.begin(); it != listOfStmtNumAft.end(); ++it) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*it);
            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(stmtNum1, *it));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: (NUM, _)
        ListOfStmtNos listOfStmtNumAft = FollowTable::getFollowStar(stmtNum1);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumAft.begin(); it != listOfStmtNumAft.end(); ++it) {
            results.push_back(make_pair(stmtNum1, *it));
        }
    } else if (isNumNumFormat) {
        // Case: (NUM, NUM)
        bool isFollowsStar = FollowTable::isFollowStar(stmtNum1, stmtNum2);
        if (isFollowsStar) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isEntityNumFormat) {
        // Case: (ENTITY, NUM)
        ListOfStmtNos listOfStmtNumBef = FollowTable::getFollowedStarBy(stmtNum2);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumBef.begin(); it != listOfStmtNumBef.end(); ++it) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(*it);
            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*it, stmtNum2));
            }
        }
    } else if (isEntityWildcardFormat) {
        // Case (ENTITY, _)
        ListOfStmtNos listOfStmtNumOfEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntity1;
        for (itEntity1 = listOfStmtNumOfEntity1.begin(); itEntity1 != listOfStmtNumOfEntity1.end(); ++itEntity1) {
            ListOfStmtNos listOfStmtAft = FollowTable::getFollowStar(*itEntity1);
            ListOfStmtNos::iterator itStmtAft;
            for (itStmtAft = listOfStmtAft.begin(); itStmtAft != listOfStmtAft.end(); ++itStmtAft) {
                results.push_back(make_pair(*itEntity1, *itStmtAft));
            }
        }
    } else if (isWildcardNumFormat) {
        // Case: (_, NUM)
        ListOfStmtNos listOfStmtNumBef = FollowTable::getFollowedStarBy(stmtNum2);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumBef.begin(); it != listOfStmtNumBef.end(); ++it) {
            results.push_back(make_pair(*it, stmtNum2));
        }
    } else if (isWildcardEntityFormat) {
        // Case: (_, ENTITY)
        ListOfStmtNos listOfStmtNumOfEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntity2;
        for (itEntity2 = listOfStmtNumOfEntity2.begin(); itEntity2 != listOfStmtNumOfEntity2.end(); ++itEntity2) {
            ListOfStmtNos listOfStmtBef = FollowTable::getFollowedStarBy(*itEntity2);
            ListOfStmtNos::iterator itStmtBef;
            for (itStmtBef = listOfStmtBef.begin(); itStmtBef != listOfStmtBef.end(); ++itStmtBef) {
                results.push_back(make_pair(*itStmtBef, *itEntity2));
            }
        }
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        ListOfStmtNos listOfStmtNumOfEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntity1;
        for (itEntity1 = listOfStmtNumOfEntity1.begin(); itEntity1 != listOfStmtNumOfEntity1.end(); ++itEntity1) {
            ListOfStmtNos listOfStmtAft = FollowTable::getFollowStar(*itEntity1);
            ListOfStmtNos::iterator itEntity2;
            for (itEntity2 = listOfStmtAft.begin(); itEntity2 != listOfStmtAft.end(); ++itEntity2) {
                DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*itEntity2);
                if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                    results.push_back(make_pair(*itEntity1, *itEntity2));
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        // Case: (_,_)
        // iterate through all stmt nums and get their followsStar
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            ListOfStmtNos listOfFollowStmts = FollowTable::getFollowStar(i);
            ListOfStmtNos::iterator itFollowStmts;

            for (itFollowStmts = listOfFollowStmts.begin(); itFollowStmts != listOfFollowStmts.end(); ++itFollowStmts) {
                results.push_back(make_pair(i, *itFollowStmts));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getDataFromParents(
        StmtNum stmtNum1,
        DesignEntity designEntity1,
        StmtNum stmtNum2,
        DesignEntity designEntity2
) {
    list<pair<StmtNum, StmtNum>> results;

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        // Case: (NUM, ENTITY)
        ListOfStmtNos listOfChildren = ParentTable::getChildren(stmtNum1);
        ListOfStmtNos::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            DesignEntity designEntityOfChild = TypeToStmtNumTable::getTypeOfStmt(*itChildren);
            if (designEntity2 == DesignEntity::STMT || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildren));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: (NUM, _)
        ListOfStmtNos listOfChildren = ParentTable::getChildren(stmtNum1);
        ListOfStmtNos::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            results.push_back(make_pair(stmtNum1, *itChildren));
        }
    } else if (isNumNumFormat) {
        // Case: (NUM, NUM)
        bool isParent = ParentTable::isParent(stmtNum1, stmtNum2);
        if (isParent) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isEntityNumFormat) {
        // Case: (ENTITY, NUM)
        StmtNum parent = ParentTable::getParent(stmtNum2);
        if (parent != INVALID_STMT_NO) {
            DesignEntity designEntityOfParent = TypeToStmtNumTable::getTypeOfStmt(parent);
            if (designEntity1 == DesignEntity::STMT || designEntityOfParent == designEntity1) {
                results.push_back(make_pair(parent, stmtNum2));
            }
        }
    } else if (isEntityWildcardFormat) {
        // Case: (ENTITY, _)
        if (designEntity1 == DesignEntity::STMT || designEntity1 == DesignEntity::WHILE || designEntity1 == DesignEntity::IF) {
            ListOfStmtNos listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            ListOfStmtNos::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                ListOfStmtNos listOfChildren = ParentTable::getChildren(*itEntity1);
                ListOfStmtNos::iterator itChildren;
                for (itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
                    results.push_back(make_pair(*itEntity1, *itChildren));
                }
            }
        }
    } else if (isWildcardNumFormat) {
        // Case: (_, NUM)
        StmtNum parent = ParentTable::getParent(stmtNum2);
        if (parent != INVALID_STMT_NO) {
            results.push_back(make_pair(parent, stmtNum2));
        }
    } else if (isWildcardEntityFormat) {
        // Case: (_, ENTITY)
        ListOfStmtNos listOfDesignEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntity2;

        for (itEntity2 = listOfDesignEntity2.begin(); itEntity2 != listOfDesignEntity2.end(); ++itEntity2) {
            StmtNum parent = ParentTable::getParent(*itEntity2);
            if (parent != INVALID_STMT_NO) {
                results.push_back(make_pair(parent, *itEntity2));
            }
        }
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        if (designEntity1 == DesignEntity::STMT || designEntity1 == DesignEntity::WHILE || designEntity1 == DesignEntity::IF) {
            ListOfStmtNos listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            ListOfStmtNos::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                ListOfStmtNos listOfChildren = ParentTable::getChildren(*itEntity1);
                ListOfStmtNos::iterator itChildren;
                for (itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
                    DesignEntity designEntityChild = TypeToStmtNumTable::getTypeOfStmt(*itChildren);
                    if (designEntity2 == DesignEntity::STMT || designEntityChild == designEntity2) {
                        results.push_back(make_pair(*itEntity1, *itChildren));
                    }
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        // Case: (_,_)
        // loop through all parents
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
        for (int i = 1; i < largestStmtNum; i++) {
            StmtNum parent = ParentTable::getParent(i);
            if (parent != INVALID_STMT_NO) {
                results.push_back(make_pair(parent, i));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getDataFromParentsStar(
        StmtNum stmtNum1,
        DesignEntity designEntity1,
        StmtNum stmtNum2,
        DesignEntity designEntity2
) {
    list<pair<StmtNum, StmtNum>> results;

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 != -1 && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::NONE && stmtNum2 == -1 && designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        // Case: (NUM, ENTITY)
        ListOfStmtNos listOfChildrenStar = ParentTable::getChildrenStar(stmtNum1);
        ListOfStmtNos::iterator itChildrenStar;

        for(itChildrenStar = listOfChildrenStar.begin(); itChildrenStar != listOfChildrenStar.end(); ++itChildrenStar) {
            DesignEntity designEntityOfChild = TypeToStmtNumTable::getTypeOfStmt(*itChildrenStar);
            if (designEntity2 == DesignEntity::STMT || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildrenStar));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: (Num, _)
        ListOfStmtNos listOfChildren = ParentTable::getChildrenStar(stmtNum1);
        ListOfStmtNos::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            results.push_back(make_pair(stmtNum1, *itChildren));
        }
    } else if (isNumNumFormat) {
        // Case: (NUM, NUM)
        bool isParentStar = ParentTable::isParentStar(stmtNum1, stmtNum2);
        if (isParentStar) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isWildcardNumFormat) {
        // Case: (_, NUM)
        ListOfStmtNos listOfParents = ParentTable::getParentStar(stmtNum2);
        ListOfStmtNos::iterator itParents;
        for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
            results.push_back(make_pair(*itParents, stmtNum2));
        }
    } else if (isEntityNumFormat) {
        // Case: (ENTITY, NUM)
        if (designEntity1 == DesignEntity::STMT || designEntity1 == DesignEntity::WHILE || designEntity1 == DesignEntity::IF) {
            ListOfStmtNos listOfParentsStar = ParentTable::getParentStar(stmtNum2);
            ListOfStmtNos:: iterator itParents;

            for (itParents = listOfParentsStar.begin(); itParents != listOfParentsStar.end(); ++itParents) {
                DesignEntity designEntityOfParent = TypeToStmtNumTable::getTypeOfStmt(*itParents);
                if (designEntity1 == DesignEntity::STMT || designEntityOfParent == designEntity1) {
                    results.push_back(make_pair(*itParents, stmtNum2));
                }
            }
        }
    } else if (isEntityWildcardFormat) {
        // Case: (ENTITY, _)
        if (designEntity1 == DesignEntity::STMT || designEntity1 == DesignEntity::WHILE || designEntity1 == DesignEntity::IF) {
            ListOfStmtNos listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            ListOfStmtNos::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                ListOfStmtNos listOfChildren = ParentTable::getChildrenStar(*itEntity1);
                ListOfStmtNos::iterator itChildren;
                for (itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
                    results.push_back(make_pair(*itEntity1, *itChildren));
                }
            }
        }
    } else if (isWildcardEntityFormat) {
        // Case: (_, ENTITY)
        ListOfStmtNos listOfDesignEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntity2;

        for (itEntity2 = listOfDesignEntity2.begin(); itEntity2 != listOfDesignEntity2.end(); ++itEntity2) {
            ListOfStmtNos listOfParents = ParentTable::getParentStar(*itEntity2);
            ListOfStmtNos::iterator itParents;

            for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
                results.push_back(make_pair(*itParents, *itEntity2));
            }
        }
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        if (designEntity1 == DesignEntity::STMT || designEntity1 == DesignEntity::WHILE || designEntity1 == DesignEntity::IF) {
            ListOfStmtNos listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            ListOfStmtNos::iterator itEntity1;

            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                ListOfStmtNos listOfChildrenStar = ParentTable::getChildrenStar(*itEntity1);
                ListOfStmtNos::iterator itChildrenStar;
                for (itChildrenStar = listOfChildrenStar.begin(); itChildrenStar != listOfChildrenStar.end(); ++itChildrenStar) {
                    DesignEntity designEntityChild = TypeToStmtNumTable::getTypeOfStmt(*itChildrenStar);
                    if (designEntity2 == DesignEntity::STMT || designEntityChild == designEntity2) {
                        results.push_back(make_pair(*itEntity1, *itChildrenStar));
                    }
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        // Case: (_,_)
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
        for (int i = 1; i < largestStmtNum; i++) {
            ListOfStmtNos listOfParents = ParentTable::getParentStar(i);
            ListOfStmtNos::iterator itParents;
            for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
                results.push_back(make_pair(*itParents, i));
            }
        }
    }
    return results;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractor::getDataFromUses(const Value& value, DesignEntity designEntity, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (value.empty() && designEntity != DesignEntity::NONE) {
        // Case: (DE, varName)
        result = PkbAbstractorHelper::usesDesignEntityHelper(designEntity, varName);
    } else if (PkbAbstractorHelper::isNum(value) && designEntity == DesignEntity::NONE) {
        // Case: (StmtNum, varName)
        StmtNum stmtNum = stoi(value);
        result = PkbAbstractorHelper::usesStmtNumHelper(stmtNum, varName);
    } else if (!value.empty() && designEntity == DesignEntity::NONE){
        // Case: (procName, varName)
        result = PkbAbstractorHelper::usesProcNameHelper(value, varName);
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractor::getDataFromModifies(const Value& value, DesignEntity designEntity, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (value.empty() && designEntity != DesignEntity::NONE) {
        // Case: (DE, varName)
        result = PkbAbstractorHelper::modifiesDesignEntityHelper(designEntity, varName);
    } else if (PkbAbstractorHelper::isNum(value) && designEntity == DesignEntity::NONE) {
        // Case: (StmtNum, varName)
        StmtNum stmtNum = stoi(value);
        result = PkbAbstractorHelper::modifiesStmtNumHelper(stmtNum, varName);
    } else if (!value.empty() && designEntity == DesignEntity::NONE) {
        // Case: (procName, varName)
        result = PkbAbstractorHelper::modifiesProcNameHelper(value, varName);
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getDataFromCalls(const Value& value1, const Value& value2) {
    list<pair<Value, Value>> result;

    bool isSynWildCard = (value1 == "" && value2 == "_");
    bool isSynProcName = (value1 == "" && value2 != "");
    bool isSynSyn = (value1 == "" && value2 == "");

    bool isProcNameWildCard = (value1 != "" && value2 == "_");
    bool isProcNameSyn = (value1 != "" && value2 == "");
    bool isProcNameProcName = (value1 != "" && value2 != "");

    bool isWildCardSyn = (value1 == "_" && value2 == "");
    bool isWildCardProcName = (value1 == "_" && value2 != "");
    bool isWildCardWildCard = (value1 == "_" && value2 == "_");

    if (isSynWildCard) {
        // Calls(p, _)

        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            if (!listOfProcNamesCalled.empty()) {
                result.push_back(make_pair(*itProcNames, "_"));
            }
        }
    } else if (isSynProcName) {
        // Calls(p, "Third")
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            if (find(begin(listOfProcNamesCalled), end(listOfProcNamesCalled), value2) != end(listOfProcNamesCalled)) {
                result.push_back(make_pair(*itProcNames, value2));
            }
        }
    } else if (isSynSyn) {
        // Calls(p, q)
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            ListOfProcNames::iterator itProcNamesCalled;

            for(itProcNamesCalled = listOfProcNamesCalled.begin(); itProcNamesCalled != listOfProcNamesCalled.end(); ++itProcNamesCalled) {
                result.push_back(make_pair(*itProcNames, *itProcNamesCalled));
            }
        }
    } else if (isProcNameWildCard) {
        // Calls("First", _)
        ListOfProcNames listOfProcNamesCalled = CallTable::getCall(value1);
        if (!listOfProcNamesCalled.empty()) {
            result.push_back(make_pair(value1, "_"));
        }
    } else if (isProcNameSyn) {
        // Calls("First", q)
        ListOfProcNames listOfProcNamesCalled = CallTable::getCall(value1);
        ListOfProcNames::iterator itProcNamesCalled;

        for(itProcNamesCalled = listOfProcNamesCalled.begin(); itProcNamesCalled != listOfProcNamesCalled.end(); ++itProcNamesCalled) {
            result.push_back(make_pair(value1, *itProcNamesCalled));
        }
    } else if (isProcNameProcName) {
        // Calls("First", "Second")
        ListOfProcNames listOfProcNamesCalled = CallTable::getCall(value1);

        if (find(begin(listOfProcNamesCalled), end(listOfProcNamesCalled), value2) != end(listOfProcNamesCalled)) {
            result.push_back(make_pair(value1, value2));
        }
    } else if (isWildCardSyn) {
        // Calls(_, q)
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalledBy = CallTable::getCalledBy(*itProcNames);
            if (!listOfProcNamesCalledBy.empty()) {
                result.push_back(make_pair("_", *itProcNames));
            }
        }
    } else if (isWildCardProcName) {
        // Calls(_, "Second")
        ListOfProcNames listOfProcNamesCalledBy = CallTable::getCalledBy(value2);
        if (!listOfProcNamesCalledBy.empty()) {
            result.push_back(make_pair("_", value2));
        }
    } else if (isWildCardWildCard) {
        // Calls(_, _)
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            if (!listOfProcNamesCalled.empty()) {
                result.push_back(make_pair("_", "_"));
                break;
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getDataFromCallsStar(const Value& value1, const Value& value2) {
    list<pair<Value, Value>> result;

    bool isSynWildCard = (value1 == "" && value2 == "_");
    bool isSynProcName = (value1 == "" && value2 != "");
    bool isSynSyn = (value1 == "" && value2 == "");

    bool isProcNameWildCard = (value1 != "" && value2 == "_");
    bool isProcNameSyn = (value1 != "" && value2 == "");
    bool isProcNameProcName = (value1 != "" && value2 != "");

    bool isWildCardSyn = (value1 == "_" && value2 == "");
    bool isWildCardProcName = (value1 == "_" && value2 != "");
    bool isWildCardWildCard = (value1 == "_" && value2 == "_");

    if (isSynWildCard) {
        // Calls*(p, _)

        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            if (!listOfProcNamesCalledStar.empty()) {
                result.push_back(make_pair(*itProcNames, "_"));
            }
        }
    } else if (isSynProcName) {
        // Calls*(p, "Third")
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            if (find(begin(listOfProcNamesCalledStar), end(listOfProcNamesCalledStar), value2) != end(listOfProcNamesCalledStar)) {
                result.push_back(make_pair(*itProcNames, value2));
            }
        }
    } else if (isSynSyn) {
        // Calls*(p, q)
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            ListOfProcNames::iterator itProcNamesCalledStar;

            for(itProcNamesCalledStar = listOfProcNamesCalledStar.begin(); itProcNamesCalledStar != listOfProcNamesCalledStar.end(); ++itProcNamesCalledStar) {
                result.push_back(make_pair(*itProcNames, *itProcNamesCalledStar));
            }
        }
    } else if (isProcNameWildCard) {
        // Calls*("First", _)
        ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(value1);
        if (!listOfProcNamesCalledStar.empty()) {
            result.push_back(make_pair(value1, "_"));
        }
    } else if (isProcNameSyn) {
        // Calls*("First", q)
        ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(value1);
        ListOfProcNames::iterator itProcNamesCalledStar;

        for(itProcNamesCalledStar = listOfProcNamesCalledStar.begin(); itProcNamesCalledStar != listOfProcNamesCalledStar.end(); ++itProcNamesCalledStar) {
            result.push_back(make_pair(value1, *itProcNamesCalledStar));
        }
    } else if (isProcNameProcName) {
        // Calls*("First", "Second")
        ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(value1);

        if (find(begin(listOfProcNamesCalledStar), end(listOfProcNamesCalledStar), value2) != end(listOfProcNamesCalledStar)) {
            result.push_back(make_pair(value1, value2));
        }
    } else if (isWildCardSyn) {
        // Calls*(_, q)
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalledStarBy = CallTable::getCalledStarBy(*itProcNames);
            if (!listOfProcNamesCalledStarBy.empty()) {
                result.push_back(make_pair("_", *itProcNames));
            }
        }
    } else if (isWildCardProcName) {
        // Calls*(_, "Second")
        ListOfProcNames listOfProcNamesCalledStarBy = CallTable::getCalledStarBy(value2);
        if (!listOfProcNamesCalledStarBy.empty()) {
            result.push_back(make_pair("_", value2));
        }
    } else if (isWildCardWildCard) {
        // Calls*(_, _)
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            // for all procNames
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            if (!listOfProcNamesCalledStar.empty()) {
                result.push_back(make_pair("_", "_"));
                break;
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getDataFromWith
                        (const Value& value1, DesignEntity designEntity1, AttributeType attrType1,
                         const Value& value2, DesignEntity designEntity2, AttributeType attrType2) {

    list<pair<Value, Value>> result;

    bool isNoneValues = (value1 == "" && value2 == "");
    bool isValueOnLeft = (value1 != "" && value2 == "");
    bool isValueOnRight = (value1 == "" && value2 != "");
    bool isBothValues = (value1 != "" && value2 != "");

    if (isNoneValues) {
        result = pql::PkbAbstractorHelper::getWithNoneValues(designEntity1, attrType1, designEntity2, attrType2);
    } else if (isValueOnLeft) {
        result = pql::PkbAbstractorHelper::getWithOneValue(designEntity2, attrType2, value1);
    } else if (isValueOnRight) {
        result = pql::PkbAbstractorHelper::getWithOneValue(designEntity1, attrType1, value2);
    } else if (isBothValues) {
        result = pql::PkbAbstractorHelper::getWithBothValues(value1, value2);
    }
    return result;
}

list<pair<StmtNum, VarName>> pql::PkbAbstractor::getAssignPattern(StmtNum assignStmtNum, const Value& value, PostFixExpression postFixExpression, bool hasUnderscores) {
    list<pair<StmtNum, VarName>> result;

    bool isCheckAllAssignStmts = assignStmtNum == -1;
    bool postFixStrIsWildcard = postFixExpression.empty();

    if (isCheckAllAssignStmts) {
        // check all assign stmts
        result = pql::PkbAbstractorHelper::getAssignPatternAllStmts(value, postFixExpression, hasUnderscores);
    } else {
        // just check that assign stmt
        result = pql::PkbAbstractorHelper::getAssignPatternSpecificStmt(assignStmtNum, value, postFixExpression, hasUnderscores);
    }
    return result;
}

list<pair<StmtNum, std::unordered_set<VarName>>> pql::PkbAbstractor::getWhilePattern(StmtNum whileStmtNum, const Value& value) {
    list<pair<StmtNum, std::unordered_set<VarName>>> result;
    bool isCheckAllWhileStmts = whileStmtNum == -1;

    if (isCheckAllWhileStmts) {
        // check all while stmts
        result = pql::PkbAbstractorHelper::getWhilePatternAllStmts(value);
    } else {
        // just check that while stmt
        result = pql::PkbAbstractorHelper::getWhilePatternSpecificStmt(whileStmtNum, value);
    }
    return result;
}

list<pair<StmtNum, std::unordered_set<VarName>>> pql::PkbAbstractor::getIfPattern(StmtNum ifStmtNum, const Value& value) {
    list<pair<StmtNum, std::unordered_set<VarName>>> result;
    bool isCheckAllIfStmts = ifStmtNum == -1;

    if (isCheckAllIfStmts) {
        // check all if stmts
        result = pql::PkbAbstractorHelper::getIfPatternAllStmts(value);
    } else {
        // just check that if stmt
        result = pql::PkbAbstractorHelper::getIfPatternSpecificStmt(ifStmtNum, value);
    }
    return result;
}

ListOfStmtNos pql::PkbAbstractor::getAllAssignStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
}

ListOfStmtNos pql::PkbAbstractor::getAllCallStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
}

vector<string> pql::PkbAbstractor::getAllConstants() {
    ListOfConstants listOfConstants = ConstantTable::getAllConstant();
    ListOfConstants::iterator itConstants;
    vector<string> constantsVector;
    for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
        string s = to_string(*itConstants);
        constantsVector.push_back(s);
    }
    return constantsVector;
}

ListOfStmtNos pql::PkbAbstractor::getAllIfStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
}

ListOfStmtNos pql::PkbAbstractor::getAllWhileStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
}

ListOfStmtNos pql::PkbAbstractor::getAllPrintStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
}

ListOfStmtNos pql::PkbAbstractor::getAllReadStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
}

ListOfVarNames pql::PkbAbstractor::getAllVarNames() {
    return VarTable::getAllVarName();
}

ListOfProcNames pql::PkbAbstractor::getAllProcNames() {
    return ProcTable::getAllProcedure();
}

StmtNum pql::PkbAbstractor::getLargestStmtNum() {
    return TypeToStmtNumTable::getLargestStmt();
}




