#include "PKB/FollowTable.h"

//using PKB::FollowTable;

namespace PkbAbsTest {
    class FollowTableStub : public FollowTable {

    public:
        ListOfStmtNos resultListOfStmtNum;
        StmtNo resultStmtNum;

        virtual StmtNo getFollowedBy(StmtNo stmt2) {
            return resultStmtNum;
        }

        virtual StmtNo getFollow(StmtNo stmt1) {
            return resultStmtNum;
        }

        virtual ListOfStmtNos getFollowedStarBy(StmtNo stmt2) {
            return resultListOfStmtNum;
        }

        virtual ListOfStmtNos getFollowStar(StmtNo stmt1) {
            return resultListOfStmtNum;
        }
        

    };
}
