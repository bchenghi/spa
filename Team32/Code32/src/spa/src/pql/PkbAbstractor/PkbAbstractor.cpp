#include "PkbAbstractor.h"
#include "PkbAbstractorHelper.h"
#include "UsesAbstractorHelper.h"
#include "ModifiesAbstractorHelper.h"
#include "PatternAbstractorHelper.h"
#include "WithAbstractorHelper.h"
#include "NextAbstractorHelper.h"
#include "AffectsAbstractorHelper.h"

#define INVALID_STMT_NO 0

#include <string>
#include <vector>

using namespace std;

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollows(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;

    bool isFollows = FollowTable::isFollow(stmtNum1, stmtNum2);
    if (isFollows) {
        results.push_back(make_pair(stmtNum1, stmtNum2));
    }

    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollows(DesignEntity designEntity1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }

    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildCardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
        StmtNum stmtNumBef = FollowTable::getFollowedBy(stmtNum2);
        if (stmtNumBef != INVALID_STMT_NO) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(stmtNumBef);
            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(stmtNumBef, stmtNum2));
            }
        }
    } else if (isWildCardNumFormat) {
        StmtNum stmtNumBef = FollowTable::getFollowedBy(stmtNum2);
        if (stmtNumBef != INVALID_STMT_NO) {
            results.push_back(make_pair(stmtNumBef, stmtNum2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollows(StmtNum stmtNum1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        StmtNum stmtNumAft = FollowTable::getFollow(stmtNum1);

        if (stmtNumAft != INVALID_STMT_NO) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(stmtNumAft);

            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(stmtNum1, stmtNumAft));
            }
        }
    } else if (isNumWildcardFormat) {
        StmtNum stmtNumAft = FollowTable::getFollow(stmtNum1);
        if (stmtNumAft != INVALID_STMT_NO) {
            results.push_back(make_pair(stmtNum1, stmtNumAft));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollows(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
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
    } else if (isEntityWildcardFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            StmtNum stmtNumAft = FollowTable::getFollow(*itEntityStmtNums);

            if (stmtNumAft != INVALID_STMT_NO) {
                results.push_back(make_pair(*itEntityStmtNums, stmtNumAft));
            }
        }
    } else if (isWildcardEntityFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            StmtNum stmtNumBef = FollowTable::getFollowedBy(*itEntityStmtNums);

            if (stmtNumBef != INVALID_STMT_NO) {
                results.push_back(make_pair(stmtNumBef, *itEntityStmtNums));
            }
        }
    } else if (isWildcardWildcardFormat) {
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

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollowsStar(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;

    bool isFollowsStar = FollowTable::isFollowStar(stmtNum1, stmtNum2);
    if (isFollowsStar) {
        results.push_back(make_pair(stmtNum1, stmtNum2));
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollowsStar(DesignEntity designEntity1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }

    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildcardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
        ListOfStmtNos listOfStmtNumBef = FollowTable::getFollowedStarBy(stmtNum2);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumBef.begin(); it != listOfStmtNumBef.end(); ++it) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(*it);
            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*it, stmtNum2));
            }
        }
    } else if (isWildcardNumFormat) {
        ListOfStmtNos listOfStmtNumBef = FollowTable::getFollowedStarBy(stmtNum2);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumBef.begin(); it != listOfStmtNumBef.end(); ++it) {
            results.push_back(make_pair(*it, stmtNum2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollowsStar(StmtNum stmtNum1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        ListOfStmtNos listOfStmtNumAft = FollowTable::getFollowStar(stmtNum1);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumAft.begin(); it != listOfStmtNumAft.end(); ++it) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*it);
            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(stmtNum1, *it));
            }
        }
    } else if (isNumWildcardFormat) {
        ListOfStmtNos listOfStmtNumAft = FollowTable::getFollowStar(stmtNum1);
        ListOfStmtNos::iterator it;
        for (it = listOfStmtNumAft.begin(); it != listOfStmtNumAft.end(); ++it) {
            results.push_back(make_pair(stmtNum1, *it));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getFollowsStar(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
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
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            ListOfStmtNos listOfFollowStmts = FollowTable::getFollowStar(i);
            ListOfStmtNos::iterator itFollowStmts;

            for (itFollowStmts = listOfFollowStmts.begin(); itFollowStmts != listOfFollowStmts.end(); ++itFollowStmts) {
                results.push_back(make_pair(i, *itFollowStmts));
            }
        }
    } else if (isEntityWildcardFormat) {
        ListOfStmtNos listOfStmtNumOfEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntity1;
        for (itEntity1 = listOfStmtNumOfEntity1.begin(); itEntity1 != listOfStmtNumOfEntity1.end(); ++itEntity1) {
            ListOfStmtNos listOfStmtAft = FollowTable::getFollowStar(*itEntity1);
            ListOfStmtNos::iterator itStmtAft;
            for (itStmtAft = listOfStmtAft.begin(); itStmtAft != listOfStmtAft.end(); ++itStmtAft) {
                results.push_back(make_pair(*itEntity1, *itStmtAft));
            }
        }
    } else if (isWildcardEntityFormat) {
        ListOfStmtNos listOfStmtNumOfEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntity2;
        for (itEntity2 = listOfStmtNumOfEntity2.begin(); itEntity2 != listOfStmtNumOfEntity2.end(); ++itEntity2) {
            ListOfStmtNos listOfStmtBef = FollowTable::getFollowedStarBy(*itEntity2);
            ListOfStmtNos::iterator itStmtBef;
            for (itStmtBef = listOfStmtBef.begin(); itStmtBef != listOfStmtBef.end(); ++itStmtBef) {
                results.push_back(make_pair(*itStmtBef, *itEntity2));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParents(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;

    bool isParent = ParentTable::isParent(stmtNum1, stmtNum2);
    if (isParent) {
        results.push_back(make_pair(stmtNum1, stmtNum2));
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParents(DesignEntity designEntity1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }

    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildcardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
        StmtNum parent = ParentTable::getParent(stmtNum2);
        if (parent != INVALID_STMT_NO) {
            DesignEntity designEntityOfParent = TypeToStmtNumTable::getTypeOfStmt(parent);
            if (designEntity1 == DesignEntity::STMT || designEntityOfParent == designEntity1) {
                results.push_back(make_pair(parent, stmtNum2));
            }
        }
    } else if (isWildcardNumFormat) {
        StmtNum parent = ParentTable::getParent(stmtNum2);
        if (parent != INVALID_STMT_NO) {
            results.push_back(make_pair(parent, stmtNum2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParents(StmtNum stmtNum1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        ListOfStmtNos listOfChildren = ParentTable::getChildren(stmtNum1);
        ListOfStmtNos::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            DesignEntity designEntityOfChild = TypeToStmtNumTable::getTypeOfStmt(*itChildren);
            if (designEntity2 == DesignEntity::STMT || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildren));
            }
        }
    } else if (isNumWildcardFormat) {
        ListOfStmtNos listOfChildren = ParentTable::getChildren(stmtNum1);
        ListOfStmtNos::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            results.push_back(make_pair(stmtNum1, *itChildren));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParents(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
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
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
        for (int i = 1; i < largestStmtNum; i++) {
            StmtNum parent = ParentTable::getParent(i);
            if (parent != INVALID_STMT_NO) {
                results.push_back(make_pair(parent, i));
            }
        }
    } else if (isEntityWildcardFormat) {
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
    } else if (isWildcardEntityFormat) {
        ListOfStmtNos listOfDesignEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntity2;

        for (itEntity2 = listOfDesignEntity2.begin(); itEntity2 != listOfDesignEntity2.end(); ++itEntity2) {
            StmtNum parent = ParentTable::getParent(*itEntity2);
            if (parent != INVALID_STMT_NO) {
                results.push_back(make_pair(parent, *itEntity2));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParentsStar(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;
    bool isParentStar = ParentTable::isParentStar(stmtNum1, stmtNum2);
    if (isParentStar) {
        results.push_back(make_pair(stmtNum1, stmtNum2));
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParentsStar(DesignEntity designEntity1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }

    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildcardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
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
    } else if (isWildcardNumFormat) {
        ListOfStmtNos listOfParents = ParentTable::getParentStar(stmtNum2);
        ListOfStmtNos::iterator itParents;
        for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
            results.push_back(make_pair(*itParents, stmtNum2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParentsStar(StmtNum stmtNum1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        ListOfStmtNos listOfChildrenStar = ParentTable::getChildrenStar(stmtNum1);
        ListOfStmtNos::iterator itChildrenStar;

        for(itChildrenStar = listOfChildrenStar.begin(); itChildrenStar != listOfChildrenStar.end(); ++itChildrenStar) {
            DesignEntity designEntityOfChild = TypeToStmtNumTable::getTypeOfStmt(*itChildrenStar);
            if (designEntity2 == DesignEntity::STMT || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildrenStar));
            }
        }
    } else if (isNumWildcardFormat) {
        ListOfStmtNos listOfChildren = ParentTable::getChildrenStar(stmtNum1);
        ListOfStmtNos::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            results.push_back(make_pair(stmtNum1, *itChildren));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getParentsStar(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
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
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
        for (int i = 1; i < largestStmtNum; i++) {
            ListOfStmtNos listOfParents = ParentTable::getParentStar(i);
            ListOfStmtNos::iterator itParents;
            for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
                results.push_back(make_pair(*itParents, i));
            }
        }
    } else if (isEntityWildcardFormat) {
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
        ListOfStmtNos listOfDesignEntity2 = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntity2;

        for (itEntity2 = listOfDesignEntity2.begin(); itEntity2 != listOfDesignEntity2.end(); ++itEntity2) {
            ListOfStmtNos listOfParents = ParentTable::getParentStar(*itEntity2);
            ListOfStmtNos::iterator itParents;

            for (itParents = listOfParents.begin(); itParents != listOfParents.end(); ++itParents) {
                results.push_back(make_pair(*itParents, *itEntity2));
            }
        }
    }
    return results;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractor::getUses(const Value& value, DesignEntity designEntity, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (value.empty() && designEntity != DesignEntity::NONE) {
        result = UsesAbstractorHelper::usesDesignEntityHelper(designEntity, varName);
    } else if (PkbAbstractorHelper::isNum(value) && designEntity == DesignEntity::NONE) {
        StmtNum stmtNum = stoi(value);
        result = UsesAbstractorHelper::usesStmtNumHelper(stmtNum, varName);
    } else if (!value.empty() && designEntity == DesignEntity::NONE){
        result = UsesAbstractorHelper::usesProcNameHelper(value, varName);
    }
    return result;
}

list<pair<string, unordered_set<VarName>>> pql::PkbAbstractor::getModifies(const Value& value, DesignEntity designEntity, const VarName& varName) {
    list<pair<string, unordered_set<VarName>>> result;

    if (value.empty() && designEntity != DesignEntity::NONE) {
        result = ModifiesAbstractorHelper::modifiesDesignEntityHelper(designEntity, varName);
    } else if (PkbAbstractorHelper::isNum(value) && designEntity == DesignEntity::NONE) {
        StmtNum stmtNum = stoi(value);
        result = ModifiesAbstractorHelper::modifiesStmtNumHelper(stmtNum, varName);
    } else if (!value.empty() && designEntity == DesignEntity::NONE) {
        result = ModifiesAbstractorHelper::modifiesProcNameHelper(value, varName);
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getCalls(const Value& value1, const Value& value2) {
    list<pair<Value, Value>> result;

    bool isSynWildCard = (value1 == "" && value2 == "_");
    bool isSynProcName = (value1 == "" && (value2 != "" && value2 != "_"));
    bool isSynSyn = (value1 == "" && value2 == "");

    bool isProcNameWildCard = ((value1 != "" && value1 != "_") && value2 == "_");
    bool isProcNameSyn = ((value1 != "" && value1 != "_") && value2 == "");
    bool isProcNameProcName = ((value1 != "" && value1 != "_") && (value2 != "" && value2 != "_"));

    bool isWildCardSyn = (value1 == "_" && value2 == "");
    bool isWildCardProcName = (value1 == "_" && (value2 != "" && value2 != "_"));
    bool isWildCardWildCard = (value1 == "_" && value2 == "_");

    if (isSynWildCard) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            if (!listOfProcNamesCalled.empty()) {
                result.push_back(make_pair(*itProcNames, "_"));
            }
        }
    } else if (isSynProcName) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            if (find(begin(listOfProcNamesCalled), end(listOfProcNamesCalled), value2) != end(listOfProcNamesCalled)) {
                result.push_back(make_pair(*itProcNames, value2));
            }
        }
    } else if (isSynSyn) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            ListOfProcNames::iterator itProcNamesCalled;

            for(itProcNamesCalled = listOfProcNamesCalled.begin(); itProcNamesCalled != listOfProcNamesCalled.end(); ++itProcNamesCalled) {
                result.push_back(make_pair(*itProcNames, *itProcNamesCalled));
            }
        }
    } else if (isProcNameWildCard) {
        ListOfProcNames listOfProcNamesCalled = CallTable::getCall(value1);
        if (!listOfProcNamesCalled.empty()) {
            result.push_back(make_pair(value1, "_"));
        }
    } else if (isProcNameSyn) {
        ListOfProcNames listOfProcNamesCalled = CallTable::getCall(value1);
        ListOfProcNames::iterator itProcNamesCalled;

        for(itProcNamesCalled = listOfProcNamesCalled.begin(); itProcNamesCalled != listOfProcNamesCalled.end(); ++itProcNamesCalled) {
            result.push_back(make_pair(value1, *itProcNamesCalled));
        }
    } else if (isProcNameProcName) {
        ListOfProcNames listOfProcNamesCalled = CallTable::getCall(value1);

        if (find(begin(listOfProcNamesCalled), end(listOfProcNamesCalled), value2) != end(listOfProcNamesCalled)) {
            result.push_back(make_pair(value1, value2));
        }
    } else if (isWildCardSyn) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalledBy = CallTable::getCalledBy(*itProcNames);
            if (!listOfProcNamesCalledBy.empty()) {
                result.push_back(make_pair("_", *itProcNames));
            }
        }
    } else if (isWildCardProcName) {
        ListOfProcNames listOfProcNamesCalledBy = CallTable::getCalledBy(value2);
        if (!listOfProcNamesCalledBy.empty()) {
            result.push_back(make_pair("_", value2));
        }
    } else if (isWildCardWildCard) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalled = CallTable::getCall(*itProcNames);
            if (!listOfProcNamesCalled.empty()) {
                result.push_back(make_pair("_", "_"));
                break;
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getCallsStar(const Value& value1, const Value& value2) {
    list<pair<Value, Value>> result;

    bool isSynWildCard = (value1 == "" && value2 == "_");
    bool isSynProcName = (value1 == "" && (value2 != "" && value2 != "_"));
    bool isSynSyn = (value1 == "" && value2 == "");

    bool isProcNameWildCard = ((value1 != "" && value1 != "_") && value2 == "_");
    bool isProcNameSyn = ((value1 != "" && value1 != "_") && value2 == "");
    bool isProcNameProcName = ((value1 != "" && value1 != "_") && (value2 != "" && value2 != "_"));

    bool isWildCardSyn = (value1 == "_" && value2 == "");
    bool isWildCardProcName = (value1 == "_" && (value2 != "" && value2 != "_"));
    bool isWildCardWildCard = (value1 == "_" && value2 == "_");

    if (isSynWildCard) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            if (!listOfProcNamesCalledStar.empty()) {
                result.push_back(make_pair(*itProcNames, "_"));
            }
        }
    } else if (isSynProcName) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            if (find(begin(listOfProcNamesCalledStar), end(listOfProcNamesCalledStar), value2) != end(listOfProcNamesCalledStar)) {
                result.push_back(make_pair(*itProcNames, value2));
            }
        }
    } else if (isSynSyn) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            ListOfProcNames::iterator itProcNamesCalledStar;

            for(itProcNamesCalledStar = listOfProcNamesCalledStar.begin(); itProcNamesCalledStar != listOfProcNamesCalledStar.end(); ++itProcNamesCalledStar) {
                result.push_back(make_pair(*itProcNames, *itProcNamesCalledStar));
            }
        }
    } else if (isProcNameWildCard) {
        ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(value1);
        if (!listOfProcNamesCalledStar.empty()) {
            result.push_back(make_pair(value1, "_"));
        }
    } else if (isProcNameSyn) {
        ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(value1);
        ListOfProcNames::iterator itProcNamesCalledStar;

        for(itProcNamesCalledStar = listOfProcNamesCalledStar.begin(); itProcNamesCalledStar != listOfProcNamesCalledStar.end(); ++itProcNamesCalledStar) {
            result.push_back(make_pair(value1, *itProcNamesCalledStar));
        }
    } else if (isProcNameProcName) {
        ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(value1);

        if (find(begin(listOfProcNamesCalledStar), end(listOfProcNamesCalledStar), value2) != end(listOfProcNamesCalledStar)) {
            result.push_back(make_pair(value1, value2));
        }
    } else if (isWildCardSyn) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalledStarBy = CallTable::getCalledStarBy(*itProcNames);
            if (!listOfProcNamesCalledStarBy.empty()) {
                result.push_back(make_pair("_", *itProcNames));
            }
        }
    } else if (isWildCardProcName) {
        ListOfProcNames listOfProcNamesCalledStarBy = CallTable::getCalledStarBy(value2);
        if (!listOfProcNamesCalledStarBy.empty()) {
            result.push_back(make_pair("_", value2));
        }
    } else if (isWildCardWildCard) {
        ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
        ListOfProcNames::iterator itProcNames;

        for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
            ListOfProcNames listOfProcNamesCalledStar = CallTable::getCallStar(*itProcNames);
            if (!listOfProcNamesCalledStar.empty()) {
                result.push_back(make_pair("_", "_"));
                break;
            }
        }
    }
    return result;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNext(ProgLine progLine1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    bool isNext = NextTable::isNext(progLine1, progLine2);
    if (isNext) {
        results.push_back(make_pair(progLine1, progLine2));
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNext(DesignEntity designEntity1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }

    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildcardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
        ListOfProgLines listOfProgLineBef = NextTable::getPrev(progLine2);
        ListOfProgLines::iterator itProcLineBef;

        for (itProcLineBef = listOfProgLineBef.begin(); itProcLineBef != listOfProgLineBef.end(); ++itProcLineBef) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(*itProcLineBef);

            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*itProcLineBef, progLine2));
            }
        }
    } else if (isWildcardNumFormat) {
        ListOfProgLines listOfProgLineBef = NextTable::getPrev(progLine2);
        ListOfProgLines::iterator itProcLineBef;

        for (itProcLineBef = listOfProgLineBef.begin(); itProcLineBef != listOfProgLineBef.end(); ++itProcLineBef) {
            results.push_back(make_pair(*itProcLineBef, progLine2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNext(ProgLine progLine1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        ListOfProgLines listOfProgLineAft = NextTable::getNext(progLine1);
        ListOfProgLines::iterator itProcLineAft;

        for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAft);

            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(progLine1, *itProcLineAft));
            }
        }
    } else if (isNumWildcardFormat) {
        ListOfProgLines listOfProgLineAft = NextTable::getNext(progLine1);
        ListOfProgLines::iterator itProcLineAft;

        for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
            results.push_back(make_pair(progLine1, *itProcLineAft));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNext(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
        ListOfStmtNos listOfLHSEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityLHSStmtNums;

        for (itEntityLHSStmtNums = listOfLHSEntityStmtNums.begin(); itEntityLHSStmtNums != listOfLHSEntityStmtNums.end(); ++itEntityLHSStmtNums) {
            ListOfProgLines listOfProgLineAft = NextTable::getNext(*itEntityLHSStmtNums);
            ListOfProgLines::iterator itProcLineAft;

            for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
                DesignEntity designEntityAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAft);

                if (designEntity2 == DesignEntity::STMT || designEntityAft == designEntity2) {
                    results.push_back(make_pair(*itEntityLHSStmtNums, *itProcLineAft));
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            ListOfProgLines listOfProgLineAft = NextTable::getNext(i);
            ListOfProgLines::iterator itProcLineAft;

            for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
                results.push_back(make_pair(i, *itProcLineAft));
            }
        }
    } else if (isEntityWildcardFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineAft = NextTable::getNext(*itEntityStmtNums);
            ListOfProgLines::iterator itProcLineAft;

            for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
                results.push_back(make_pair(*itEntityStmtNums, *itProcLineAft));
            }
        }
    } else if (isWildcardEntityFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineBef = NextTable::getPrev(*itEntityStmtNums);
            ListOfProgLines::iterator itProcLineBef;

            for (itProcLineBef = listOfProgLineBef.begin(); itProcLineBef != listOfProgLineBef.end(); ++itProcLineBef) {
                results.push_back(make_pair(*itProcLineBef, *itEntityStmtNums));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextStar(ProgLine progLine1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextStarGraph = pql::PkbAbstractorHelper::getGraph("nextStar");
    if (nextStarGraph.empty()) {
        nextStarGraph = pql::NextAbstractorHelper::createNextStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextStar", nextStarGraph);
    }
    ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextStar(progLine1, nextStarGraph);
    if (listOfProgLineAftStar.find(progLine2) != listOfProgLineAftStar.end()) {
        results.push_back(make_pair(progLine1, progLine2));
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextStar(DesignEntity designEntity1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextStarGraph = pql::PkbAbstractorHelper::getGraph("nextStar");
    if (nextStarGraph.empty()) {
        nextStarGraph = pql::NextAbstractorHelper::createNextStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextStar", nextStarGraph);
    }

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildcardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
        ListOfProgLines listOfProgLineBefStar = pql::NextAbstractorHelper::getPrevStar(progLine2, nextStarGraph);
        ListOfProgLines::iterator itProcLineBefStar;

        for (itProcLineBefStar = listOfProgLineBefStar.begin(); itProcLineBefStar != listOfProgLineBefStar.end(); ++itProcLineBefStar) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(*itProcLineBefStar);

            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*itProcLineBefStar, progLine2));
            }
        }
    } else if (isWildcardNumFormat) {
        ListOfProgLines listOfProgLineBefStar = pql::NextAbstractorHelper::getPrevStar(progLine2, nextStarGraph);
        ListOfProgLines::iterator itProcLineBefStar;

        for (itProcLineBefStar = listOfProgLineBefStar.begin(); itProcLineBefStar != listOfProgLineBefStar.end(); ++itProcLineBefStar) {
            results.push_back(make_pair(*itProcLineBefStar, progLine2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextStar(ProgLine progLine1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextStarGraph = pql::PkbAbstractorHelper::getGraph("nextStar");
    if (nextStarGraph.empty()) {
        nextStarGraph = pql::NextAbstractorHelper::createNextStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextStar", nextStarGraph);
    }

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextStar(progLine1, nextStarGraph);
        ListOfProgLines::iterator itProcLineAftStar;

        for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAftStar);

            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(progLine1, *itProcLineAftStar));
            }
        }
    } else if (isNumWildcardFormat) {
        ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextStar(progLine1, nextStarGraph);
        ListOfProgLines::iterator itProcLineAftStar;

        for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
            results.push_back(make_pair(progLine1, *itProcLineAftStar));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextStar(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextStarGraph = pql::PkbAbstractorHelper::getGraph("nextStar");
    if (nextStarGraph.empty()) {
        nextStarGraph = pql::NextAbstractorHelper::createNextStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextStar", nextStarGraph);
    }

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
        ListOfStmtNos listOfLHSEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityLHSStmtNums;

        for (itEntityLHSStmtNums = listOfLHSEntityStmtNums.begin(); itEntityLHSStmtNums != listOfLHSEntityStmtNums.end(); ++itEntityLHSStmtNums) {
            ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextStar(*itEntityLHSStmtNums, nextStarGraph);
            ListOfProgLines::iterator itProcLineAftStar;

            for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
                DesignEntity designEntityAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAftStar);

                if (designEntity2 == DesignEntity::STMT || designEntityAft == designEntity2) {
                    results.push_back(make_pair(*itEntityLHSStmtNums, *itProcLineAftStar));
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextStar(i, nextStarGraph);
            ListOfProgLines::iterator itProcLineAftStar;

            for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
                results.push_back(make_pair(i, *itProcLineAftStar));
            }
        }
    } else if (isEntityWildcardFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityStmtNums;

        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextStar(*itEntityStmtNums, nextStarGraph);
            ListOfProgLines::iterator itProcLineAftStar;

            for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
                results.push_back(make_pair(*itEntityStmtNums, *itProcLineAftStar));
            }
        }
    } else if (isWildcardEntityFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineBefStar = pql::NextAbstractorHelper::getPrevStar(*itEntityStmtNums, nextStarGraph);
            ListOfProgLines::iterator itProcLineBefStar;

            for (itProcLineBefStar = listOfProgLineBefStar.begin(); itProcLineBefStar != listOfProgLineBefStar.end(); ++itProcLineBefStar) {
                results.push_back(make_pair(*itProcLineBefStar, *itEntityStmtNums));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getAffects(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> result;

    bool isNumNum = stmtNum1 != 0 && stmtNum2 != 0;
    bool isNumEntity = stmtNum1 != 0 && stmtNum2 == 0;
    bool isEntityNum = stmtNum1 == 0 && stmtNum2 != 0;
    bool isEntityEntity = stmtNum1 == 0 && stmtNum2 == 0;

    if (isNumNum) {
        bool isAffects = AffectsAbstractorHelper::isAffects(stmtNum1, stmtNum2);

        if (isAffects) {
            result.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isNumEntity) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            bool isAffects = AffectsAbstractorHelper::isAffects(stmtNum1, *itAssign);

            if (isAffects) {
                result.push_back(make_pair(stmtNum1, *itAssign));
            }
        }
    } else if (isEntityNum) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            bool isAffects = AffectsAbstractorHelper::isAffects(*itAssign, stmtNum2);

            if (isAffects) {
                result.push_back(make_pair(*itAssign, stmtNum2));
            }
        }
    } else if (isEntityEntity) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            ListOfStmtNos::iterator itAssign2;

            for (itAssign2 = listOfAssignStmts.begin(); itAssign2 != listOfAssignStmts.end(); ++itAssign2) {
                bool isAffects = AffectsAbstractorHelper::isAffects(*itAssign, *itAssign2);

                if (isAffects) {
                    result.push_back(make_pair(*itAssign, *itAssign2));
                }
            }
        }
    }
    return result;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getAffectsStar(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> result;

    bool isNumNum = stmtNum1 != 0 && stmtNum2 != 0;
    bool isNumEntity = stmtNum1 != 0 && stmtNum2 == 0;
    bool isEntityNum = stmtNum1 == 0 && stmtNum2 != 0;
    bool isEntityEntity = stmtNum1 == 0 && stmtNum2 == 0;

    Graph affectsStarGraph = PkbAbstractorHelper::getGraph("affectsStar");
    if (affectsStarGraph.empty()) {
        affectsStarGraph = AffectsAbstractorHelper::createAffectsStarGraph();
        PkbAbstractorHelper::addGraph("affectsStar", affectsStarGraph);
    }

    if (isNumNum) {
        ListOfStmtNos listOfAffectsStar = AffectsAbstractorHelper::getAffectsStar(stmtNum1, affectsStarGraph);
        if (listOfAffectsStar.find(stmtNum2) != listOfAffectsStar.end()) {
            result.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isNumEntity) {
        ListOfStmtNos listOfAffectsStar = AffectsAbstractorHelper::getAffectsStar(stmtNum1, affectsStarGraph);
        ListOfStmtNos::iterator itAffectsStar;

        for (itAffectsStar = listOfAffectsStar.begin(); itAffectsStar != listOfAffectsStar.end(); ++itAffectsStar) {
            result.push_back(make_pair(stmtNum1, *itAffectsStar));
        }
    } else if (isEntityNum) {
        ListOfStmtNos listOfAffectedStar = AffectsAbstractorHelper::getAffectedByStar(stmtNum2, affectsStarGraph);
        ListOfStmtNos::iterator itAffectedStar;

        for (itAffectedStar = listOfAffectedStar.begin(); itAffectedStar != listOfAffectedStar.end(); ++itAffectedStar) {
            result.push_back(make_pair(*itAffectedStar, stmtNum2));
        }
    } else if (isEntityEntity) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;
        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            ListOfStmtNos listOfAffectsStar = AffectsAbstractorHelper::getAffectsStar(*itAssign, affectsStarGraph);
            ListOfStmtNos::iterator itAffectsStar;

            if (!listOfAffectsStar.empty()) {
                for (itAffectsStar = listOfAffectsStar.begin(); itAffectsStar != listOfAffectsStar.end(); ++itAffectsStar) {
                    result.push_back(make_pair(*itAssign, *itAffectsStar));
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getWith(DesignEntity designEntity1, AttributeType attrType1, DesignEntity designEntity2, AttributeType attrType2) {
    list<pair<Value, Value>> result;
    result = pql::WithAbstractorHelper::getWithNoneValues(designEntity1, attrType1, designEntity2, attrType2);
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getWith(const Value& value1, DesignEntity designEntity2, AttributeType attrType2) {
    list<pair<Value, Value>> result;
    result = pql::WithAbstractorHelper::getWithOneValueLeft(designEntity2, attrType2, value1);
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getWith(DesignEntity designEntity1, AttributeType attrType1, const Value& value2) {
    list<pair<Value, Value>> result;
    result = pql::WithAbstractorHelper::getWithOneValueRight(designEntity1, attrType1, value2);
    return result;
}

list<pair<Value, Value>> pql::PkbAbstractor::getWith(const Value& value1, const Value& value2) {
    list<pair<Value, Value>> result;
    result = pql::WithAbstractorHelper::getWithBothValues(value1, value2);
    return result;
}

list<pair<StmtNum, VarName>> pql::PkbAbstractor::getAssignPatternSubMatch(StmtNum assignStmtNum, const Value &value, PostFixExpression postFixExpression) {
    list<pair<StmtNum, VarName>> result;

    bool isCheckAllAssignStmts = assignStmtNum == 0;
    bool postFixStrIsWildcard = postFixExpression.empty();

    if (isCheckAllAssignStmts) {
        result = pql::PatternAbstractorHelper::getAssignPatternAllStmtsSubMatch(value, postFixExpression);
    } else {
        result = pql::PatternAbstractorHelper::getAssignPatternSpecificStmtSubMatch(assignStmtNum, value, postFixExpression);
    }
    return result;
}

list<pair<StmtNum, VarName>> pql::PkbAbstractor::getAssignPatternFullMatch(StmtNum assignStmtNum, const Value &value, PostFixExpression postFixExpression) {
    list<pair<StmtNum, VarName>> result;

    bool isCheckAllAssignStmts = assignStmtNum == 0;
    bool postFixStrIsWildcard = postFixExpression.empty();

    if (isCheckAllAssignStmts) {
        result = pql::PatternAbstractorHelper::getAssignPatternAllStmtsFullMatch(value, postFixExpression);
    } else {
        result = pql::PatternAbstractorHelper::getAssignPatternSpecificStmtFullMatch(assignStmtNum, value, postFixExpression);
    }
    return result;
}


list<pair<StmtNum, std::unordered_set<VarName>>> pql::PkbAbstractor::getWhilePattern(StmtNum whileStmtNum, const Value& value) {
    list<pair<StmtNum, std::unordered_set<VarName>>> result;
    bool isCheckAllWhileStmts = whileStmtNum == 0;

    if (isCheckAllWhileStmts) {
        result = pql::PatternAbstractorHelper::getWhilePatternAllStmts(value);
    } else {
        result = pql::PatternAbstractorHelper::getWhilePatternSpecificStmt(whileStmtNum, value);
    }
    return result;
}

list<pair<StmtNum, std::unordered_set<VarName>>> pql::PkbAbstractor::getIfPattern(StmtNum ifStmtNum, const Value& value) {
    list<pair<StmtNum, std::unordered_set<VarName>>> result;
    bool isCheckAllIfStmts = ifStmtNum == 0;

    if (isCheckAllIfStmts) {
        result = pql::PatternAbstractorHelper::getIfPatternAllStmts(value);
    } else {
        result = pql::PatternAbstractorHelper::getIfPatternSpecificStmt(ifStmtNum, value);
    }
    return result;
}

Value pql::PkbAbstractor::getAttributeVal(StmtNum stmtNum, DesignEntity designEntity, AttributeType attributeType) {
    Value value;
    if (designEntity == DesignEntity::CALL && attributeType == AttributeType::PROCEDURE_NAME) {
        value = CallStmtTable::getProcCalled(stmtNum);
    }
    if (designEntity == DesignEntity::READ && attributeType == AttributeType::VARIABLE_NAME) {
        value = *(ModifyTable::getStmtModify(stmtNum).begin());
    }
    if (designEntity == DesignEntity::PRINT && attributeType == AttributeType::VARIABLE_NAME) {
        value = *(UseTable::getStmtUse(stmtNum).begin());
    }
    return value;
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

void pql::PkbAbstractor::clear() {
    pql::PkbAbstractorHelper::clearGraphs();
}


list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBip(ProgLine progLine1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    bool isNext = NextBipTable::isNext(progLine1, progLine2);
    if (isNext) {
        results.push_back(make_pair(progLine1, progLine2));
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBip(DesignEntity designEntity1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }

    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildcardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
        ListOfProgLines listOfProgLineBef = NextBipTable::getPrev(progLine2);
        ListOfProgLines::iterator itProcLineBef;

        for (itProcLineBef = listOfProgLineBef.begin(); itProcLineBef != listOfProgLineBef.end(); ++itProcLineBef) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(*itProcLineBef);

            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*itProcLineBef, progLine2));
            }
        }
    } else if (isWildcardNumFormat) {
        ListOfProgLines listOfProgLineBef = NextBipTable::getPrev(progLine2);
        ListOfProgLines::iterator itProcLineBef;

        for (itProcLineBef = listOfProgLineBef.begin(); itProcLineBef != listOfProgLineBef.end(); ++itProcLineBef) {
            results.push_back(make_pair(*itProcLineBef, progLine2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBip(ProgLine progLine1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        ListOfProgLines listOfProgLineAft = NextBipTable::getNext(progLine1);
        ListOfProgLines::iterator itProcLineAft;

        for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAft);

            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(progLine1, *itProcLineAft));
            }
        }
    } else if (isNumWildcardFormat) {
        // Case: next(NUM, _)
        ListOfProgLines listOfProgLineAft = NextBipTable::getNext(progLine1);
        ListOfProgLines::iterator itProcLineAft;

        for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
            results.push_back(make_pair(progLine1, *itProcLineAft));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBip(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
        ListOfStmtNos listOfLHSEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityLHSStmtNums;

        for (itEntityLHSStmtNums = listOfLHSEntityStmtNums.begin(); itEntityLHSStmtNums != listOfLHSEntityStmtNums.end(); ++itEntityLHSStmtNums) {
            ListOfProgLines listOfProgLineAft = NextBipTable::getNext(*itEntityLHSStmtNums);
            ListOfProgLines::iterator itProcLineAft;

            for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
                DesignEntity designEntityAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAft);

                if (designEntity2 == DesignEntity::STMT || designEntityAft == designEntity2) {
                    results.push_back(make_pair(*itEntityLHSStmtNums, *itProcLineAft));
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            ListOfProgLines listOfProgLineAft = NextTable::getNext(i);
            ListOfProgLines::iterator itProcLineAft;

            for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
                results.push_back(make_pair(i, *itProcLineAft));
            }
        }
    } else if (isEntityWildcardFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineAft = NextTable::getNext(*itEntityStmtNums);
            ListOfProgLines::iterator itProcLineAft;

            for (itProcLineAft = listOfProgLineAft.begin(); itProcLineAft != listOfProgLineAft.end(); ++itProcLineAft) {
                results.push_back(make_pair(*itEntityStmtNums, *itProcLineAft));
            }
        }
    } else if (isWildcardEntityFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineBef = NextTable::getPrev(*itEntityStmtNums);
            ListOfProgLines::iterator itProcLineBef;

            for (itProcLineBef = listOfProgLineBef.begin(); itProcLineBef != listOfProgLineBef.end(); ++itProcLineBef) {
                results.push_back(make_pair(*itProcLineBef, *itEntityStmtNums));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBipStar(ProgLine progLine1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextBipStarGraph = pql::PkbAbstractorHelper::getGraph("nextBipStar");
    if (nextBipStarGraph.empty()) {
        nextBipStarGraph = pql::NextAbstractorHelper::createNextBipStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextBipStar", nextBipStarGraph);
    }

    ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextBipStar(progLine1, nextBipStarGraph);
    if (listOfProgLineAftStar.find(progLine2) != listOfProgLineAftStar.end()) {
        results.push_back(make_pair(progLine1, progLine2));
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBipStar(DesignEntity designEntity1, ProgLine progLine2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextBipStarGraph = pql::PkbAbstractorHelper::getGraph("nextBipStar");
    if (nextBipStarGraph.empty()) {
        nextBipStarGraph = pql::NextAbstractorHelper::createNextBipStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextBipStar", nextBipStarGraph);
    }

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    bool isEntityNumFormat = (designEntity1 != DesignEntity::NONE);
    bool isWildcardNumFormat = (designEntity1 == DesignEntity::NONE);

    if (isEntityNumFormat) {
        ListOfProgLines listOfProgLineBefStar = pql::NextAbstractorHelper::getPrevBipStar(progLine2, nextBipStarGraph);
        ListOfProgLines::iterator itProcLineBefStar;

        for (itProcLineBefStar = listOfProgLineBefStar.begin(); itProcLineBefStar != listOfProgLineBefStar.end(); ++itProcLineBefStar) {
            DesignEntity designEntityOfStmtBef = TypeToStmtNumTable::getTypeOfStmt(*itProcLineBefStar);

            if (designEntity1 == DesignEntity::STMT || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*itProcLineBefStar, progLine2));
            }
        }
    } else if (isWildcardNumFormat) {
        ListOfProgLines listOfProgLineBefStar = pql::NextAbstractorHelper::getPrevBipStar(progLine2, nextBipStarGraph);
        ListOfProgLines::iterator itProcLineBefStar;

        for (itProcLineBefStar = listOfProgLineBefStar.begin(); itProcLineBefStar != listOfProgLineBefStar.end(); ++itProcLineBefStar) {
            results.push_back(make_pair(*itProcLineBefStar, progLine2));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBipStar(ProgLine progLine1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextBipStarGraph = pql::PkbAbstractorHelper::getGraph("nextBipStar");
    if (nextBipStarGraph.empty()) {
        nextBipStarGraph = pql::NextAbstractorHelper::createNextBipStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextBipStar", nextBipStarGraph);
    }

    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isNumEntityFormat = (designEntity2 != DesignEntity::NONE);
    bool isNumWildcardFormat = (designEntity2 == DesignEntity::NONE);

    if (isNumEntityFormat) {
        ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextBipStar(progLine1, nextBipStarGraph);
        ListOfProgLines::iterator itProcLineAftStar;

        for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
            DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAftStar);

            if (designEntity2 == DesignEntity::STMT || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(progLine1, *itProcLineAftStar));
            }
        }
    } else if (isNumWildcardFormat) {
        ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextBipStar(progLine1, nextBipStarGraph);
        ListOfProgLines::iterator itProcLineAftStar;

        for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
            results.push_back(make_pair(progLine1, *itProcLineAftStar));
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getNextBipStar(DesignEntity designEntity1, DesignEntity designEntity2) {
    list<pair<StmtNum, StmtNum>> results;

    Graph nextBipStarGraph = pql::PkbAbstractorHelper::getGraph("nextBipStar");
    if (nextBipStarGraph.empty()) {
        nextBipStarGraph = pql::NextAbstractorHelper::createNextBipStarGraph();
        pql::PkbAbstractorHelper::addGraph("nextBipStar", nextBipStarGraph);
    }

    if (designEntity1 == DesignEntity::PROGRAM_LINE) {
        designEntity1 = DesignEntity::STMT;
    }
    if (designEntity2 == DesignEntity::PROGRAM_LINE) {
        designEntity2 = DesignEntity::STMT;
    }

    bool isEntityEntityFormat = (designEntity1 != DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isEntityWildcardFormat = (designEntity1 != DesignEntity::NONE && designEntity2 == DesignEntity::NONE);
    bool isWildcardEntityFormat = (designEntity1 == DesignEntity::NONE && designEntity2 != DesignEntity::NONE);
    bool isWildcardWildcardFormat = (designEntity1 == DesignEntity::NONE && designEntity2 == DesignEntity::NONE);

    if (isEntityEntityFormat) {
        ListOfStmtNos listOfLHSEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityLHSStmtNums;

        for (itEntityLHSStmtNums = listOfLHSEntityStmtNums.begin(); itEntityLHSStmtNums != listOfLHSEntityStmtNums.end(); ++itEntityLHSStmtNums) {
            ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextBipStar(*itEntityLHSStmtNums, nextBipStarGraph);
            ListOfProgLines::iterator itProcLineAftStar;

            for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
                DesignEntity designEntityAft = TypeToStmtNumTable::getTypeOfStmt(*itProcLineAftStar);

                if (designEntity2 == DesignEntity::STMT || designEntityAft == designEntity2) {
                    results.push_back(make_pair(*itEntityLHSStmtNums, *itProcLineAftStar));
                }
            }
        }
    } else if (isWildcardWildcardFormat) {
        StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

        for (int i = 1; i < largestStmtNum; i++) {
            ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextBipStar(i, nextBipStarGraph);
            ListOfProgLines::iterator itProcLineAftStar;

            for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
                results.push_back(make_pair(i, *itProcLineAftStar));
            }
        }
    } else if (isEntityWildcardFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity1);
        ListOfStmtNos::iterator itEntityStmtNums;

        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineAftStar = pql::NextAbstractorHelper::getNextBipStar(*itEntityStmtNums, nextBipStarGraph);
            ListOfProgLines::iterator itProcLineAftStar;

            for (itProcLineAftStar = listOfProgLineAftStar.begin(); itProcLineAftStar != listOfProgLineAftStar.end(); ++itProcLineAftStar) {
                results.push_back(make_pair(*itEntityStmtNums, *itProcLineAftStar));
            }
        }
    } else if (isWildcardEntityFormat) {
        ListOfStmtNos listOfEntityStmtNums = TypeToStmtNumTable::getStmtWithType(designEntity2);
        ListOfStmtNos::iterator itEntityStmtNums;
        for (itEntityStmtNums = listOfEntityStmtNums.begin(); itEntityStmtNums != listOfEntityStmtNums.end(); ++itEntityStmtNums) {
            ListOfProgLines listOfProgLineBefStar = pql::NextAbstractorHelper::getPrevBipStar(*itEntityStmtNums, nextBipStarGraph);
            ListOfProgLines::iterator itProcLineBefStar;

            for (itProcLineBefStar = listOfProgLineBefStar.begin(); itProcLineBefStar != listOfProgLineBefStar.end(); ++itProcLineBefStar) {
                results.push_back(make_pair(*itProcLineBefStar, *itEntityStmtNums));
            }
        }
    }
    return results;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getAffectsBip(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> result;

    bool isNumNum = stmtNum1 != 0 && stmtNum2 != 0;
    bool isNumEntity = stmtNum1 != 0 && stmtNum2 == 0;
    bool isEntityNum = stmtNum1 == 0 && stmtNum2 != 0;
    bool isEntityEntity = stmtNum1 == 0 && stmtNum2 == 0;
    if (isNumNum) {
        // Affects(2, 4)
        bool isAffects = AffectsAbstractorHelper::isAffectsBip(stmtNum1, stmtNum2);

        if (isAffects) {
            result.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isNumEntity) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            bool isAffects = AffectsAbstractorHelper::isAffectsBip(stmtNum1, *itAssign);

            if (isAffects) {
                result.push_back(make_pair(stmtNum1, *itAssign));
            }
        }
    } else if (isEntityNum) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            bool isAffects = AffectsAbstractorHelper::isAffectsBip(*itAssign, stmtNum2);

            if (isAffects) {
                result.push_back(make_pair(*itAssign, stmtNum2));
            }
        }
    } else if (isEntityEntity) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;

        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            ListOfStmtNos::iterator itAssign2;

            for (itAssign2 = listOfAssignStmts.begin(); itAssign2 != listOfAssignStmts.end(); ++itAssign2) {
                bool isAffects = AffectsAbstractorHelper::isAffectsBip(*itAssign, *itAssign2);

                if (isAffects) {
                    result.push_back(make_pair(*itAssign, *itAssign2));
                }
            }
        }
    }
    return result;
}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getAffectsBipStar(StmtNum stmtNum1, StmtNum stmtNum2) {
    list<pair<StmtNum, StmtNum>> result;

    bool isNumNum = stmtNum1 != 0 && stmtNum2 != 0;
    bool isNumEntity = stmtNum1 != 0 && stmtNum2 == 0;
    bool isEntityNum = stmtNum1 == 0 && stmtNum2 != 0;
    bool isEntityEntity = stmtNum1 == 0 && stmtNum2 == 0;

    Graph affectsStarGraph = pql::PkbAbstractorHelper::getGraph("affectsBipStar");
    if (affectsStarGraph.empty()) {
        affectsStarGraph = pql::AffectsAbstractorHelper::createAffectsBipStarGraph();
        pql::PkbAbstractorHelper::addGraph("affectsBipStar", affectsStarGraph);
    }

    if (isNumNum) {
        ListOfStmtNos listOfAffectsStar = pql::AffectsAbstractorHelper::getAffectsBipStar(stmtNum1, affectsStarGraph);
        if (listOfAffectsStar.find(stmtNum2) != listOfAffectsStar.end()) {
            result.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isNumEntity) {
        ListOfStmtNos listOfAffectsStar = pql::AffectsAbstractorHelper::getAffectsBipStar(stmtNum1, affectsStarGraph);
        ListOfStmtNos::iterator itAffectsStar;

        for (itAffectsStar = listOfAffectsStar.begin(); itAffectsStar != listOfAffectsStar.end(); ++itAffectsStar) {
            result.push_back(make_pair(stmtNum1, *itAffectsStar));
        }
    } else if (isEntityNum) {
        ListOfStmtNos listOfAffectedStar = pql::AffectsAbstractorHelper::getAffectedBipByStar(stmtNum2, affectsStarGraph);
        ListOfStmtNos::iterator itAffectedStar;

        for (itAffectedStar = listOfAffectedStar.begin(); itAffectedStar != listOfAffectedStar.end(); ++itAffectedStar) {
            result.push_back(make_pair(*itAffectedStar, stmtNum2));
        }
    } else if (isEntityEntity) {
        ListOfStmtNos listOfAssignStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
        ListOfStmtNos::iterator itAssign;
        for (itAssign = listOfAssignStmts.begin(); itAssign != listOfAssignStmts.end(); ++itAssign) {
            ListOfStmtNos listOfAffectsStar = pql::AffectsAbstractorHelper::getAffectsBipStar(*itAssign, affectsStarGraph);
            ListOfStmtNos::iterator itAffectsStar;

            if (!listOfAffectsStar.empty()) {
                for (itAffectsStar = listOfAffectsStar.begin(); itAffectsStar != listOfAffectsStar.end(); ++itAffectsStar) {
                    result.push_back(make_pair(*itAssign, *itAffectsStar));
                }
            }
        }
    }
    return result;
}
