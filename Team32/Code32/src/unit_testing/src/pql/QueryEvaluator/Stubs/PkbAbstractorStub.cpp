#include "pql/PkbAbstractor/PkbAbstractor.h"

using pql::PkbAbstractor;

namespace qetest {
    class PkbAbstractorStub : public PkbAbstractor {
    public:
        ListOfStmtNos resultStmtList = {};
        vector<string> resultStrList = {};
        ListOfVarNames varLst = {};
        ListOfProcNames procLst = {};
        StmtNum largestStmtNum = 0;
        virtual ListOfStmtNos getAllAssignStmts() {
            return resultStmtList;
        }
        virtual ListOfStmtNos getAllCallStmts() {
            return resultStmtList;
        }
        virtual vector<string> getAllConstants() {
            return resultStrList;
        }
        virtual ListOfStmtNos getAllIfStmts() {
            return resultStmtList;
        }
        virtual ListOfStmtNos getAllWhileStmts() {
            return resultStmtList;
        }
        virtual ListOfStmtNos getAllPrintStmts() {
            return resultStmtList;
        }
        virtual ListOfStmtNos getAllReadStmts() {
            return resultStmtList;
        }
        virtual ListOfVarNames getAllVarNames() {
            return varLst;
        }
        virtual ListOfProcNames getAllProcNames() {
            return procLst;
        }
        virtual StmtNum getLargestStmtNum() {
            return largestStmtNum;
        }
    };
}
