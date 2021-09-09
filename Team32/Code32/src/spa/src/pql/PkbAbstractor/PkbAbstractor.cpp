#include "PkbAbstractor.h"
#include "PkbAbstractorHelper.h"

#include "../src/PKB/FollowTable.h"
#include "../src/PKB/ParentTable.h"
#include "../src/PKB/ModifyTable.h"
#include "../src/PKB/UseTable.h"
#include "../src/PKB/ProcTable.h"
#include "../src/PKB/VarTable.h"
#include "../src/PKB/TypeToStmtNumTable.h"

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
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

    if (isNumEntityFormat) {
        // Case: follows(NUM, ENTITY)
        StmtNum stmtNumAft = FollowTable::getFollow(stmtNum1);
        DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(stmtNumAft);

        if (designEntity2 == DesignEntity::Stmt || designEntity2 == designEntityOfStmtAft) {
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
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

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
    } else if (isEntityEntityFormat) {
        // Case: (ENTITY, ENTITY)
        LIST_OF_STMT_NO listOfStmtNumOfEntity1 = TypeToStmtNumTable::getStmtWithType(designEntity1);
        LIST_OF_STMT_NO::iterator itEntity1;
        for (itEntity1 = listOfStmtNumOfEntity1.begin(); itEntity1 != listOfStmtNumOfEntity1.end(); ++itEntity1) {
            LIST_OF_STMT_NO listOfStmtAft = FollowTable::getFollowStar(*itEntity1);
            LIST_OF_STMT_NO::iterator itEntity2;
            for (itEntity2 = listOfStmtNumOfEntity1.begin(); itEntity2 != listOfStmtNumOfEntity1.end(); ++itEntity2) {
                DesignEntity designEntityOfStmtAft = TypeToStmtNumTable::getTypeOfStmt(*itEntity2);
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

    bool isNumEntityFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

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
    } else if (isNumNumFormat) {
        // Case: (NUM, NUM)
        bool isParent = ParentTable::isParent(stmtNum1, stmtNum2);
        if (isParent) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
        }
    } else if (isEntityNumFormat) {
        // Case: (ENTITY, NUM)
        StmtNum parent = ParentTable::getParent(stmtNum2);
        if (parent != -1) {
            DesignEntity designEntityOfParent = TypeToStmtNumTable::getTypeOfStmt(parent);
            if (designEntity1 == DesignEntity::Stmt || designEntityOfParent == designEntity1) {
                results.push_back(make_pair(parent, stmtNum2));
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
    bool isNumNumFormat = (stmtNum1 != -1 && designEntity1 == DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityNumFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 != -1 && designEntity2 == DesignEntity::None);
    bool isEntityEntityFormat = (stmtNum1 == -1 && designEntity1 != DesignEntity::None && stmtNum2 == -1 && designEntity2 != DesignEntity::None);

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
    } else if (isNumNumFormat) {
        // Case: (NUM, NUM)
        bool isParentStar = ParentTable::isParentStar(stmtNum1, stmtNum2);
        if (isParentStar) {
            results.push_back(make_pair(stmtNum1, stmtNum2));
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

//list<pair<StmtNum, VarName>> pql::PkbAbstractor::getPattern(StmtNum assignStmtNum, Value value, SubTree subTree) {
//    list<pair<StmtNum, VarName>> result;
//
//    bool isCheckAllAssignStmts = assignStmtNum == -1;
//
//    if (isCheckAllAssignStmts) {
//        // check all assign stmts
//        list<StmtNum> listOfAssignStmt = TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
//        list<StmtNum>::iterator itAssign;
//
//        if (value == "" || value == "_") {
//            // case: a(v, "count + 1"), a("_", "count + 1"), a(v, _)
//            for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
//                // check if rhs contains subTree
//                if (assignAstTable.containsSubtree(assignStmtNum, subTree) {
//                    VarName varName = modifiesTable.stmtModifies(assignStmtNum).front();
//                    result.push_back(make_pair(assignStmtNum, varName));
//                }
//            }
//        } else {
//            // case: a("count", "count + 1"), a("count", _)
//            // check if lhs and rhs match
//            for (itAssign = listOfAssignStmt.begin(); itAssign != listOfAssignStmt.end(); ++itAssign) {
//                VarName varName = modifiesTable.stmtModifies(assignStmtNum).front();
//                if (value == varName && assignAstTable.containsSubtree(assignStmtNum, subTree)) {
//                    result.push_back(make_pair(assignStmtNum, varName));
//                }
//            }
//        }
//    } else {
//        // just check that assign stmt
//        if (value == "" || value == "_") {
//            // case: a(v, "count + 1"), a("_", "count + 1"), a(v, _)
//            if (assignAstTable.containsSubtree(assignStmtNum, subTree)) {
//                VarName varName = modifiesTable.stmtModifies(assignStmtNum).front();
//                result.push_back(make_pair(assignStmtNum, varName));
//            }
//        } else {
//            // case: a("count", "count + 1"), a("count", _)
//            VarName varName = modifiesTable.stmtModifies(assignStmtNum).front();
//            if (value == varName && assignAstTable.containsSubtree(assignStmtNum, subTree)) {
//                result.push_back(make_pair(assignStmtNum, varName));
//            }
//        }
//    }
//    return result;
//}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllAssignStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::Assign);
}

LIST_OF_STMT_NO pql::PkbAbstractor::getAllCallStmts() {
    return TypeToStmtNumTable::getStmtWithType(DesignEntity::Call);
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




