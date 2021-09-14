#include <PKB/FollowTable.h>

//using PKB::FollowTable;

namespace PkbAbsTest {
    class FollowTableStub : public FollowTable {

    public:
        LIST_OF_STMT_NO resultListOfStmtNum;
        STMT_NO resultStmtNum;

        virtual STMT_NO getFollowedBy(STMT_NO stmt2) {
            return resultStmtNum;
        }

        virtual STMT_NO getFollow(STMT_NO stmt1) {
            return resultStmtNum;
        }

        virtual LIST_OF_STMT_NO getFollowedStarBy(STMT_NO stmt2) {
            return resultListOfStmtNum;
        }

        virtual LIST_OF_STMT_NO getFollowStar(STMT_NO stmt1) {
            return resultListOfStmtNum;
        }
        

    };
}