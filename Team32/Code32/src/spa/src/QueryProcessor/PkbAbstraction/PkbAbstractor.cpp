#include "PkbAbstractor.h"
#include "../src/QueryProcessor/DesignEntity.h"

#include <string>
#include <vector>
// include pkb

using namespace std;



void PkbAbstractor::getVarTable() {

}

std::list<string> PkbAbstractor::getDataFromFollows(
        StmtNo stmtNo1,
        DesignEntity designEntity1,
        StmtNo stmtNo2,
        DesignEntity designEntity2
) {
    FollowsTable followsTable = this->followsTable;
    list<string> result;

    if (stmtNo1 != -1) {
        // first arg is a stmt num
        switch (designEntity2) {
            case DesignEntity::kStmt:
                followsTable.getStmtFollows(stmtNo1)



//            kAssign,
//            kIf,
//            kPrint,
//            kProcedure,
//            kRead,
//            kStmt,
//            kWhile
        }
    }


    return result;
}



