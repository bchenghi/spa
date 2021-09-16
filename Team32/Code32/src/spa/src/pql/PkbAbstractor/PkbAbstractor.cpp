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

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);

    if (isNumEntityFormat) {
        // Case: follows(NUM, ENTITY)
        StmtNum stmtNumAft = FollowTable::getFollow(stmtNum1);
        DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(stmtNumAft);

        if (designEntity2 == DesignEntity::Stmt || designEntity2 == designEntityOfStmtAft) {
            results.push_back(make_pair(stmtNum1, stmtNumAft));
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
        DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(stmtNumBef);

        if (designEntity1 == DesignEntity::Stmt || designEntity1 == designEntityOfStmtBef) {
            results.push_back(make_pair(stmtNumBef, stmtNum2));
        }
    } else if (isEntityWildcardFormat) {
        // Case: (ENTITY, _)
        // get all entity stmt nums, check if there is something aft
        LIST_OF_STMT_NO listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        LIST_OF_STMT_NO::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            StmtNum stmtNumAft = FollowTable::getFollow(*itEntityStmtNums);

            if (stmtNumAft != INVALID_STMT_NO) {
                results.push_back(make_pair(*itEntityStmtNums, stmtNumAft));
            }
        }
    } else if (isWildcardEntityFormat) {
        //Case: (_, ENTITY)
        // get all entity stmt nums, check if there is something before
        LIST_OF_STMT_NO listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity2); //list of 1, 2, 3
        LIST_OF_STMT_NO::iterator itEntityStmtNums;
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
        LIST_OF_STMT_NO stmtNumsOfLHSEntity = TypeToStmtNumTable::getStmtWithType(designEntity1);
        LIST_OF_STMT_NO::iterator it;
        for (it = stmtNumsOfLHSEntity.begin(); it != stmtNumsOfLHSEntity.end(); ++it) {
            StmtNum stmtNumAft = FollowTable::getFollow(*it);
            DesignEntity designEntityAft = TypeToStmtNumTable::getTypeOfStmt(stmtNumAft);
            if (designEntityAft == designEntity2) {
                results.push_back(make_pair(*it, stmtNumAft));
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

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);

    if (isNumEntityFormat) {
        // Case: (NUM, ENTITY)
        LIST_OF_STMT_NO listOfStmtNumAft = FollowTable::getFollowStar(stmtNum1);
        LIST_OF_STMT_NO::iterator it;
        for (it = listOfStmtNumAft.begin(); it != listOfStmtNumAft.end(); ++it) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*it);
            if (designEntity2 == DesignEntity::Stmt || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(stmtNum1, *it));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: (NUM, _)
        LIST_OF_STMT_NO listOfStmtNumAft = FollowTable::getFollowStar(stmtNum1);
        LIST_OF_STMT_NO::iterator it;
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
        LIST_OF_STMT_NO listOfStmtNumBef = FollowTable::getFollowedStarBy(stmtNum2);
        LIST_OF_STMT_NO::iterator it;
        for (it = listOfStmtNumBef.begin(); it != listOfStmtNumBef.end(); ++it) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(*it);
            if (designEntity1 == DesignEntity::Stmt || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*it, stmtNum2));
            }
        }
    } else if (isEntityWildcardFormat) {
        // Case (ENTITY, _)
        LIST_OF_STMT_NO listOfStmtNumOfEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
        LIST_OF_STMT_NO::iterator itEntity1;
        for (itEntity1 = listOfStmtNumOfEntity1.begin(); itEntity1 != listOfStmtNumOfEntity1.end(); ++itEntity1) {
            LIST_OF_STMT_NO listOfStmtAft = FollowTable::getFollowStar(*itEntity1);
            LIST_OF_STMT_NO::iterator itStmtAft;
            for (itStmtAft = listOfStmtAft.begin(); itStmtAft != listOfStmtAft.end(); ++itStmtAft) {
                results.push_back(make_pair(*itEntity1, *itStmtAft));
            }
        }
    } else if (isWildcardNumFormat) {
        // Case: (_, NUM)
        LIST_OF_STMT_NO listOfStmtNumBef = FollowTable::getFollowedStarBy(stmtNum2);
        LIST_OF_STMT_NO::iterator it;
        for (it = listOfStmtNumBef.begin(); it != listOfStmtNumBef.end(); ++it) {
            results.push_back(make_pair(*it, stmtNum2));
        }
    } else if (isWildcardEntityFormat) {
        // Case: (_, ENTITY)
        LIST_OF_STMT_NO listOfStmtNumOfEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        LIST_OF_STMT_NO::iterator itEntity2;
        for (itEntity2 = listOfStmtNumOfEntity2.begin(); itEntity2 != listOfStmtNumOfEntity2.end(); ++itEntity2) {
            LIST_OF_STMT_NO listOfStmtBef = FollowTable::getFollowStar(*itEntity2);
            LIST_OF_STMT_NO::iterator itStmtBef;
            for (itStmtBef = listOfStmtBef.begin(); itStmtBef != listOfStmtBef.end(); ++itStmtBef) {
                results.push_back(make_pair(*itStmtBef, *itEntity2));
            }
        }
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        LIST_OF_STMT_NO listOfStmtNumOfEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
        LIST_OF_STMT_NO::iterator itEntity1;
        for (itEntity1 = listOfStmtNumOfEntity1.begin(); itEntity1 != listOfStmtNumOfEntity1.end(); ++itEntity1) {
            LIST_OF_STMT_NO listOfStmtAft = FollowTable::getFollowStar(*itEntity1);
            LIST_OF_STMT_NO::iterator itEntity2;
            for (itEntity2 = listOfStmtAft.begin(); itEntity2 != listOfStmtAft.end(); ++itEntity2) {
                DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*itEntity2);
                if (designEntity2 == DesignEntity::Stmt || designEntity2 == designEntityOfStmtAft) {
                    results.push_back(make_pair(*itEntity1, *itEntity2));
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        // Case: (_,_)
        // iterate through all stmt nums and get their followsStar
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            LIST_OF_STMT_NO listOfFollowStmts = FollowTable::getFollowStar(i);
            LIST_OF_STMT_NO::iterator itFollowStmts;

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

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);

    if (isNumEntityFormat) {
        // Case: (NUM, ENTITY)
        LIST_OF_STMT_NO listOfChildren = ParentTable::getChildren(stmtNum1);
        LIST_OF_STMT_NO::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            DesignEntity designEntityOfChild = TypeToStmtNumTable::getTypeOfStmt(*itChildren);
            if (designEntity2 == DesignEntity::Stmt || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildren));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: (NUM, _)
        LIST_OF_STMT_NO listOfChildren = ParentTable::getChildren(stmtNum1);
        LIST_OF_STMT_NO::iterator itChildren;
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
            if (designEntity1 == DesignEntity::Stmt || designEntityOfParent == designEntity1) {
                results.push_back(make_pair(parent, stmtNum2));
            }
        }
    } else if (isEntityWildcardFormat) {
        // Case: (ENTITY, _)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            LIST_OF_STMT_NO listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            LIST_OF_STMT_NO::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                LIST_OF_STMT_NO listOfChildren = ParentTable::getChildren(*itEntity1);
                LIST_OF_STMT_NO::iterator itChildren;
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
        LIST_OF_STMT_NO listOfDesignEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        LIST_OF_STMT_NO::iterator itEntity2;

        for (itEntity2 = listOfDesignEntity2.begin(); itEntity2 != listOfDesignEntity2.end(); ++itEntity2) {
            StmtNum parent = ParentTable::getParent(*itEntity2);
            if (parent != INVALID_STMT_NO) {
                results.push_back(make_pair(parent, *itEntity2));
            }
        }
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            LIST_OF_STMT_NO listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            LIST_OF_STMT_NO::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                LIST_OF_STMT_NO listOfChildren = ParentTable::getChildren(*itEntity1);
                LIST_OF_STMT_NO::iterator itChildren;
                for (itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
                    DesignEntity designEntityChild = TypeToStmtNumTable::getTypeOfStmt(*itChildren);
                    if (designEntity2 == DesignEntity::Stmt || designEntityChild == designEntity2) {
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

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isNumWildcardFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);

    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityWildcardFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

    bool isWildcardNumFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isWildcardEntityFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isWildcardWildcardFormat = (stmtNum1 == -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 == DesignEntity::None);

    if (isNumEntityFormat) {
        // Case: (NUM, ENTITY)
        LIST_OF_STMT_NO listOfChildrenStar = ParentTable::getChildrenStar(stmtNum1);
        LIST_OF_STMT_NO::iterator itChildrenStar;

        for(itChildrenStar = listOfChildrenStar.begin(); itChildrenStar != listOfChildrenStar.end(); ++itChildrenStar) {
            DesignEntity designEntityOfChild = TypeToStmtNumTable::getTypeOfStmt(*itChildrenStar);
            if (designEntity2 == DesignEntity::Stmt || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildrenStar));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: (Num, _)
        LIST_OF_STMT_NO listOfChildren = ParentTable::getChildrenStar(stmtNum1);
        LIST_OF_STMT_NO::iterator itChildren;
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
        LIST_OF_STMT_NO listOfParents = ParentTable::getParentStar(stmtNum2);
        LIST_OF_STMT_NO::iterator itParents;
        for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
            results.push_back(make_pair(*itParents, stmtNum2));
        }
    } else if (isEntityNumFormat) {
        // Case: (ENTITY, NUM)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            LIST_OF_STMT_NO listOfParentsStar = ParentTable::getParentStar(stmtNum2);
            LIST_OF_STMT_NO:: iterator itParents;

            for (itParents = listOfParentsStar.begin(); itParents != listOfParentsStar.end(); ++itParents) {
                DesignEntity designEntityOfParent = TypeToStmtNumTable::getTypeOfStmt(*itParents);
                if (designEntity1 == DesignEntity::Stmt || designEntityOfParent == designEntity1) {
                    results.push_back(make_pair(*itParents, stmtNum2));
                }
            }
        }
    } else if (isEntityWildcardFormat) {
        // Case: (ENTITY, _)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            LIST_OF_STMT_NO listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            LIST_OF_STMT_NO::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                LIST_OF_STMT_NO listOfChildren = ParentTable::getChildrenStar(*itEntity1);
                LIST_OF_STMT_NO::iterator itChildren;
                for (itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
                    results.push_back(make_pair(*itEntity1, *itChildren));
                }
            }
        }
    } else if (isWildcardEntityFormat) {
        // Case: (_, ENTITY)
        LIST_OF_STMT_NO listOfDesignEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        LIST_OF_STMT_NO::iterator itEntity2;

        for (itEntity2 = listOfDesignEntity2.begin(); itEntity2 != listOfDesignEntity2.end(); ++itEntity2) {
            LIST_OF_STMT_NO listOfParents = ParentTable::getParentStar(*itEntity2);
            LIST_OF_STMT_NO::iterator itParents;

            for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
                results.push_back(make_pair(*itParents, *itEntity2));
            }
        }
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            LIST_OF_STMT_NO listOfDesignEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
            LIST_OF_STMT_NO::iterator itEntity1;

            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                LIST_OF_STMT_NO listOfChildrenStar = ParentTable::getChildrenStar(*itEntity1);
                LIST_OF_STMT_NO::iterator itChildrenStar;
                for (itChildrenStar = listOfChildrenStar.begin(); itChildrenStar != listOfChildrenStar.end(); ++itChildrenStar) {
                    DesignEntity designEntityChild = TypeToStmtNumTable::getTypeOfStmt(*itChildrenStar);
                    if (designEntity2 == DesignEntity::Stmt || designEntityChild == designEntity2) {
                        results.push_back(make_pair(*itEntity1, *itChildrenStar));
                    }
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        // Case: (_,_)
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
        for (int i = 1; i < largestStmtNum; i++) {
            LIST_OF_STMT_NO listOfParents = ParentTable::getParentStar(i);
            LIST_OF_STMT_NO::iterator itParents;
            for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
                results.push_back(make_pair(*itParents, i));
            }
        }
    }
    return results;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractor::getDataFromUses(Value value, DesignEntity designEntity, VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (value == "" && designEntity != DesignEntity::None) {
        // Case: (DE, varName)
        result = PkbAbstractorHelper::usesDesignEntityHelper(designEntity, varName);
    } else if (PkbAbstractorHelper::isNum(value) && designEntity == DesignEntity::None) {
        // Case: (StmtNum, varName)
        StmtNum stmtNum = stoi(value);
        result = PkbAbstractorHelper::usesStmtNumHelper(stmtNum, varName);
    } else if (value != "" && designEntity == DesignEntity::None){
        // Case: (procName, varName)
        result = PkbAbstractorHelper::usesProcNameHelper(value, varName);
    }
    return result;
}

list<pair<string, unordered_set<VAR_NAME>>> pql::PkbAbstractor::getDataFromModifies(Value value, DesignEntity designEntity, VarName varName) {
    list<pair<string, unordered_set<VAR_NAME>>> result;

    if (value == "" && designEntity != DesignEntity::None) {
        // Case: (DE, varName)
        result = PkbAbstractorHelper::modifiesDesignEntityHelper(designEntity, varName);
    } else if (PkbAbstractorHelper::isNum(value) && designEntity == DesignEntity::None) {
        // Case: (StmtNum, varName)
        StmtNum stmtNum = stoi(value);
        result = PkbAbstractorHelper::modifiesStmtNumHelper(stmtNum, varName);
    } else if (value != "" && designEntity == DesignEntity::None) {
        // Case: (procName, varName)
        result = PkbAbstractorHelper::modifiesProcNameHelper(value, varName);
    }
    return result;
}

list<pair<StmtNum, VarName>> pql::PkbAbstractor::getPattern(StmtNum assignStmtNum, Value value, postFixStr postFixStr) {
    list<pair<StmtNum, VarName>> result;

    bool isCheckAllAssignStmts = assignStmtNum == -1;
    bool postFixStrIsWildcard = postFixStr == "";

    if (isCheckAllAssignStmts) {
        // check all assign stmts
        LIST_OF_STMT_NO listOfAssignStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
        LIST_OF_STMT_NO::iterator itAssign;

        if (value == "" || value == "_") {
            // case: a(v, "count + 1"), a("_", "count + 1"), a(v, _)
            for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
                // check if rhs contains postFixStr
                if (AssignPostFixTable::isSubString(assignStmtNum, postFixStr) || postFixStrIsWildcard) {
                    VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
                    result.push_back(make_pair(assignStmtNum, varName));
                }
            }
        } else {
            // case: a("count", "count + 1"), a("count", _)
            // check if lhs and rhs match
            for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
                VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
                if (value == varName && (AssignPostFixTable::isSubString(assignStmtNum, postFixStr) || postFixStrIsWildcard)) {
                    result.push_back(make_pair(assignStmtNum, varName));
                }
            }
        }
    } else {
        // just check that assign stmt
        if (value == "" || value == "_") {
            // case: a(v, "count + 1"), a("_", "count + 1"), a(v, _)
            if (AssignPostFixTable::isSubString(assignStmtNum, postFixStr) || postFixStrIsWildcard) {
                VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
                result.push_back(make_pair(assignStmtNum, varName));
            }
        } else {
            // case: a("count", "count + 1"), a("count", _)
            VarName varName = *(ModifyTable::getStmtModify(assignStmtNum).begin());
            if (value == varName && (AssignPostFixTable::isSubString(assignStmtNum, postFixStr) || postFixStrIsWildcard)) {
                result.push_back(make_pair(assignStmtNum, varName));
            }
        }
    }
    return result;
}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllAssignStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllCallStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::Call);
}

vector<string> pql::PkbAbstractor::getAllConstants() {
    LIST_OF_CONSTANT listOfConstants = ConstantTable::getAllConstant();
    LIST_OF_CONSTANT::iterator itConstants;
    vector<string> constantsVector;
    for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
        string s = to_string(*itConstants);
        constantsVector.push_back(s);
    }
    return constantsVector;
}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllIfStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::If);
}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllWhileStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::While);
}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllPrintStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::Print);
}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllReadStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::Read);
}

LIST_OF_VAR_NAME pql::PkbAbstractor::getAllVarNames() {
    return VarTable::getAllVarName();
}

LIST_OF_PROC_NAME pql::PkbAbstractor::getAllProcNames() {
    return ProcTable::getAllProcedure();
}

StmtNum pql::PkbAbstractor::getLargestStmtNum() {
    return TypeToStmtNumTable::getLargestStmt();
}




