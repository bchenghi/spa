#include "PkbAbstractor.h"
#include "../src/pql/DesignEntity.h"

#include <string>
#include <vector>
// include pkb

using namespace std;

void pql::PkbAbstractor::getVarTable() {

}

list<pair<StmtNum, StmtNum>> pql::PkbAbstractor::getDataFromFollows(
        StmtNum stmtNum1,
        DesignEntity designEntity1,
        StmtNum stmtNum2,
        DesignEntity designEntity2
) {
    list<pair<StmtNum, StmtNum>> results;

    if (stmtNum1 != -1 && stmtNum2 == -1) {
        // Case: (NUM, ENTITY)
        StmtNum stmtNumAft = followsTable.getStmtFollows(stmtNum1);
        DesignEntity designEntityOfStmtAft = typeToStmtNoTable.getTypeOfStmt(stmtNumAft);

        if (designEntity2 == DesignEntity::Stmt || designEntity2 == designEntityOfStmtAft) {
            results.push_back(make_pair(stmtNum1, stmtNumAft));
        }
    } else if (stmtNum1 != -1 && stmtNum2 != -1) {
        // Case: (NUM, NUM)
        bool isFollows = followsTable.isFollows(stmtNum1, stmtNum2);
        if (isFollows) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (stmtNum1 == -1 && stmtNum2 != -1) {
        // Case: (ENTITY, NUM)
        StmtNum stmtNumBef = followsTable.getStmtFollowedBy(stmtNum2);
        DesignEntity designEntityOfStmtBef = typeToStmtNoTable.getTypeOfStmt(stmtNumBef);

        if (designEntity1 == DesignEntity::Stmt || designEntity1 == designEntityOfStmtBef) {
            results.push_back(make_pair(stmtNumBef, stmtNum2));
        }
    } else {
        // Case: (ENTITY, ENTITY)
        list<StmtNum> stmtNumsOfLHSEntity = typeToStmtNoTable.getStmtWithType(designEntity1);
        list<StmtNum>::iterator it;
        for (it = stmtNumsOfLHSEntity.begin(); it != stmtNumsOfLHSEntity.end(); ++it) {
            StmtNum stmtNumAft = followsTable.getStmtFollows(*it);
            DesignEntity designEntityAft = typeToStmtNoTable.getTypeOfStmt(stmtNumAft);
            if (designEntityAft == designEntity2) {
                results.push_back(make_pair(*it, stmtNumAft));
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

    if (stmtNum1 != -1 && stmtNum2 == -1) {
        // Case: (NUM, ENTITY)
        list<StmtNum> listOfStmtNumAft = followsTable.getStmtFollowsStar(stmtNum1);
        list<StmtNum>::iterator it;
        for (it = listOfStmtNumAft.begin(); it != listOfStmtNumAft.end(); ++it) {
            DesignEntity designEntityOfStmtAft = typeToStmtNoTable.getTypeOfStmt(*it);
            if (designEntity2 == DesignEntity::Stmt || designEntity2 == designEntityOfStmtAft) {
                results.push_back(make_pair(stmtNum1, *it));
            }
        }
    } else if (stmtNum1 != -1 && stmtNum2 != -1) {
        // Case: (NUM, NUM)
        bool isFollowsStar = followsTable.isFollowsStar(stmtNum1, stmtNum2);
        if (isFollowsStar) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (stmtNum1 == -1 && stmtNum2 != -1) {
        // Case: (ENTITY, NUM)
        list<StmtNum> listOfStmtNumBef = followsTable.getStmtFollowedStarBy(stmtNum2);
        list<StmtNum>::iterator it;
        for (it = listOfStmtNumBef.begin(); it != listOfStmtNumBef.end(); ++it) {
            DesignEntity designEntityOfStmtBef = typeToStmtNoTable.getTypeOfStmt(*it);
            if (designEntity1 == DesignEntity::Stmt || designEntity1 == designEntityOfStmtBef) {
                results.push_back(make_pair(*it, stmtNum2));
            }
        }
    } else {
        // Case: (ENTITY, ENTITY)
        list<StmtNum> listOfStmtNumOfEntity1 = typeToStmtNoTable.getStmtWithType(designEntity1);
        list<StmtNum>::iterator itEntity1;
        for (itEntity1 = listOfStmtNumOfEntity1.begin(); itEntity1 != listOfStmtNumOfEntity1.end(); ++itEntity1) {
            list<StmtNum> listOfStmtAft = followsTable.getStmtFollow(*itEntity1);
            list<StmtNum>::iterator itEntity2;
            for (itEntity2 = listOfStmtNumOfEntity1.begin(); itEntity2 != listOfStmtNumOfEntity1.end(); ++itEntity2) {
                DesignEntity designEntityOfStmtAft = typeToStmtNoTable.getTypeOfStmt(*itEntity2);
                if (designEntity2 == DesignEntity::Stmt || designEntity2 == designEntityOfStmtAft) {
                    results.push_back(make_pair(*itEntity1, *itEntity2));
                }
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

    if (stmtNum1 != -1 && stmtNum2 == -1) {
        // Case: (NUM, ENTITY)
        list<StmtNum> listOfChildren = parentsTable.getChildren(stmtNum1);
        list<StmtNum>::iterator itChildren;
        for(itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
            DesignEntity designEntityOfChild = typeToStmtNoTable.getTypeOfStmt(*itChildren);
            if (designEntity2 == DesignEntity::Stmt || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildren));
            }
        }
    } else if (stmtNum1 != -1 && stmtNum2 != -1) {
        // Case: (NUM, NUM)
        bool isParent = parentsTable.isParent(stmtNum1, stmtNum2);
        if (isParent) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (stmtNum1 == -1 && stmtNum2 != -1) {
        // Case: (ENTITY, NUM)
        StmtNum parent = parentsTable.getParent(stmtNum2);
        if (parent != -1) {
            DesignEntity designEntityOfParent = typeToStmtNoTable.getTypeOfStmt(parent);
            if (designEntity1 == DesignEntity::Stmt || designEntityOfParent == designEntity1) {
                results.push_back(make_pair(parent, stmtNum2));
            }
        }
    } else {
        // Case: (ENTITY, ENTITY)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            list<StmtNum> listOfDesignEntity1 = typeToStmtNoTable.getStmtWithType(designEntity1);
            list<StmtNum>::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                list<StmtNum> listOfChildren = parentsTable.getChildren(*itEntity1);
                list<StmtNum>::iterator itChildren;
                for (itChildren = listOfChildren.begin(); itChildren != listOfChildren.end(); ++itChildren) {
                    DesignEntity designEntityChild = typeToStmtNoTable.getTypeOfStmt(*itChildren);
                    if (designEntity2 == DesignEntity::Stmt || designEntityChild == designEntity2) {
                        results.push_back(make_pair(*itEntity1, *itChildren));
                    }
                }
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

    if (stmtNum1 != -1 && stmtNum2 == -1) {
        // Case: (NUM, ENTITY)
        list<StmtNum> listOfChildrenStar = parentsTable.getChildrenStar(stmtNum1);
        list<StmtNum>::iterator itChildrenStar;

        for(itChildrenStar = listOfChildrenStar.begin(); itChildrenStar != listOfChildrenStar.end(); ++itChildrenStar) {
            DesignEntity designEntityOfChild = typeToStmtNoTable.getTypeOfStmt(*itChildrenStar);
            if (designEntity2 == DesignEntity::Stmt || designEntityOfChild == designEntity2) {
                results.push_back(make_pair(stmtNum1, *itChildrenStar));
            }
        }
    } else if (stmtNum1 != -1 && stmtNum2 != -1) {
        // Case: (NUM, NUM)
        bool isParentStar = parentsTable.isParentStar(stmtNum1, stmtNum2);
        if (isParentStar) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (stmtNum1 == -1 && stmtNum2 != -1) {
        // Case: (ENTITY, NUM)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            list<StmtNum> listOfParentsStar = parentsTable.getParentsStar(stmtNum2);
            list<StmtNum>:: iterator itParents;
            for (itParents = listOfParentsStar.begin(); itParents != listOfParentsStar.end(); ++itParents) {
                DesignEntity designEntityOfParent = typeToStmtNoTable.getTypeOfStmt(*itParents);
                if (designEntity1 == DesignEntity::Stmt || designEntityOfParent == designEntity1) {
                    results.push_back(make_pair(*itParents, stmtNum2));
                }
            }
        }
    } else {
        // Case: (ENTITY, ENTITY)
        if (designEntity1 == DesignEntity::Stmt || designEntity1 == DesignEntity::While || designEntity1 == DesignEntity::If) {
            list<StmtNum> listOfDesignEntity1 = typeToStmtNoTable.getStmtWithType(designEntity1);
            list<StmtNum>::iterator itEntity1;
            for (itEntity1 = listOfDesignEntity1.begin(); itEntity1 != listOfDesignEntity1.end(); ++itEntity1) {
                list<StmtNum> listOfChildrenStar = parentsTable.getChildrenStar(*itEntity1);
                list<StmtNum>::iterator itChildrenStar;
                for (itChildrenStar = listOfChildrenStar.begin(); itChildrenStar != listOfChildrenStar.end(); ++itChildrenStar) {
                    DesignEntity designEntityChild = typeToStmtNoTable.getTypeOfStmt(*itChildrenStar);
                    if (designEntity2 == DesignEntity::Stmt || designEntityChild == designEntity2) {
                        results.push_back(make_pair(*itEntity1, *itChildrenStar));
                    }
                }
            }
        }
    }
    return results;
}





//                Assign,
//                Call,
//                If,
//                Print,
//                Read,
//                Stmt,
//                While
//                wildcard

