#include "pql/PkbAbstractor/PkbAbstractor.h"

using pql::DesignEntity;
using pql::PkbAbstractor;

namespace clausetest {
    class PkbAbstractorStub : public PkbAbstractor {

    public:
        list<pair<StmtNum, StmtNum>> resultStmtPair = {};
        list<pair<Value , std::unordered_set<VarName>>> resultValueVarSet = {};
        list<pair<StmtNum, VarName>> resultStmtVar = {};
        ListOfStmtNos resultStmtList = {};
        vector<string> resultStrList = {};
        ListOfVarNames varLst = {};
        ListOfProcNames procLst = {};
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

        virtual list<pair<Value , std::unordered_set<VarName>>> getDataFromUses(const Value&, DesignEntity, const VarName&) {
            return resultValueVarSet;
        }
        virtual list<pair<Value , std::unordered_set<VarName>>> getDataFromModifies(const Value&, DesignEntity, const VarName&) {
            return resultValueVarSet;
        }

        virtual list<pair<StmtNum, VarName>> getPattern(StmtNum, const Value&, PostFixExpression, bool) {
            return resultStmtVar;
        }

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
