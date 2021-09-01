#include "PkbAbstractor.h"
#include "../src/QueryProcessor/DesignEntity.h"

#include <string>
#include <vector>
// include pkb

using namespace std;



void PkbAbstractor::getVarTable() {

}

list<pair<StmtNum, StmtNum>> PkbAbstractor::getDataFromFollows(
        DesignEntity designEntitySelect,
        StmtNum stmtNo1,
        DesignEntity designEntityLHS,
        StmtNum stmtNo2,
        DesignEntity designEntityRHS
) {
    FollowsTable followsTable = this->followsTable;
    list<pair<StmtNum, StmtNum>> results;

    if (stmtNo1 != -1 && stmtNo2 == -1) {
        // Case: (NUM, ENTITY)
        StmtNum stmtNoAft = followsTable.getStmtFollows(stmtNo1);
        DesignEntity designEntityOfStmtAft = this->typeToStmtNoTable.getTypeOfStmt(stmtNoAft);

        if (designEntityRHS == DesignEntity::Stmt || designEntityRHS == designEntityOfStmtAft) {
            results.push_back(make_pair(stmtNo1, stmtNoAft));
        } else {
            results.push_back(make_pair(stmtNo1, -1));
        }
    } else if (stmtNo1 != -1 && stmtNo2 == -1) {
        // Case: (NUM, NUM)
        bool isFollows = followsTable.isFollows(stmtNo1, stmtNo2);
        if (isFollows) {

        }


    } else if (stmtNo2 != -1) {
        // Case: (ENTITY, NUM)
        StmtNum stmtNoBef = followsTable.getStmtFollowedBy(stmtNo2);
        DesignEntity designEntityOfStmtBef = this->typeToStmtNoTable.getTypeOfStmt(stmtNoBef);

        if (designEntityLHS == DesignEntity::Stmt || designEntityLHS == designEntityOfStmtBef) {
            results.push_back(stmtNoBef);
        } else {
            results.push_back(1);
        }
    } else {
        // Case: (ENTITY, ENTITY)
        if (designEntitySelect == designEntityLHS) {
            // find all stmt nums of first entity, then check if the stmt aft is the second entity
            list<StmtNum> stmtNumsOfLHSEntity = this->typeToStmtNoTable.getStmtWithType(designEntityLHS);
            list<StmtNum>::iterator it;

            for (it = stmtNumsOfLHSEntity.begin(); it != stmtNumsOfLHSEntity.end(); ++it) {
                StmtNum stmtNumAft = *it + 1;
                DesignEntity designEntityAft = this->typeToStmtNoTable.getTypeOfStmt(stmtNumAft);
                if (designEntityAft == designEntityRHS) {
                    results.push_back(*it);
                }
            }
        } else {
            // find all stmt nums of second entity, then check if the stmt bef is the first entity
            list<StmtNum> stmtNumsOfRHSEntity = this->typeToStmtNoTable.getStmtWithType(designEntityRHS);
            list<StmtNum>::iterator it;

            for (it = stmtNumsOfRHSEntity.begin(); it != stmtNumsOfRHSEntity.end(); ++it) {
                StmtNum stmtNumBef = *it - 1;
                DesignEntity designEntityBef = this->typeToStmtNoTable.getTypeOfStmt(stmtNumBef);
                if (designEntityBef == designEntityLHS) {
                    results.push_back(*it);
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

