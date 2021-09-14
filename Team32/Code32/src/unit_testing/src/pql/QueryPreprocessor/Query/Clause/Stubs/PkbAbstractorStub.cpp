#include <pql/PkbAbstractor/PkbAbstractor.h>

using pql::DesignEntity;
using pql::PkbAbstractor;

namespace clausetest {
    class PkbAbstractorStub : public PkbAbstractor {

    public:
        list<pair<StmtNum, StmtNum>> resultStmtPair = {};
        list<pair<Value , std::unordered_set<VAR_NAME>>> resultValueVarSet = {};
        list<pair<StmtNum, VarName>> resultStmtVar = {};
        LIST_OF_STMT_NO resultStmtList = {};
        vector<string> resultStrList = {};
        LIST_OF_VAR_NAME varLst = {};
        LIST_OF_PROC_NAME procLst = {};
        StmtNum largestStmtNum = 0;
        virtual list<pair<StmtNum, StmtNum>> getDataFromFollows(StmtNum, DesignEntity, StmtNum, DesignEntity) {
            return resultStmtPair;
        }
        virtual list<pair<StmtNum, StmtNum>> getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<Value , std::unordered_set<VAR_NAME>>> getDataFromUses(Value, DesignEntity, VarName) {
            return resultValueVarSet;
        }
        virtual list<pair<Value , std::unordered_set<VAR_NAME>>> getDataFromModifies(Value, DesignEntity, VarName) {
            return resultValueVarSet;
        }

        virtual list<pair<StmtNum, VarName>> getPattern(StmtNum, Value, postFixStr) {
            return resultStmtVar;
        }

        virtual LIST_OF_STMT_NO getAllAssignStmts() {
            return resultStmtList;
        }
        virtual LIST_OF_STMT_NO getAllCallStmts() {
            return resultStmtList;
        }
        virtual vector<string> getAllConstants() {
            return resultStrList;
        }
        virtual LIST_OF_STMT_NO getAllIfStmts() {
            return resultStmtList;
        }
        virtual LIST_OF_STMT_NO getAllWhileStmts() {
            return resultStmtList;
        }
        virtual LIST_OF_STMT_NO getAllPrintStmts() {
            return resultStmtList;
        }
        virtual LIST_OF_STMT_NO getAllReadStmts() {
            return resultStmtList;
        }
        virtual LIST_OF_VAR_NAME getAllVarNames() {
            return varLst;
        }
        virtual LIST_OF_PROC_NAME getAllProcNames() {
            return procLst;
        }
        virtual StmtNum getLargestStmtNum() {
            return largestStmtNum;
        }
    };
}
