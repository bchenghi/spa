#include "pql/PkbAbstractor/PkbAbstractor.h"
#include "pql/AttributeType.h"

using pql::AttributeType;
using pql::DesignEntity;
using pql::PkbAbstractor;

namespace clausetest {
    class PkbAbstractorStub : public PkbAbstractor {

    public:
        list<pair<StmtNum, StmtNum>> resultStmtPair = {};
        list<pair<Value , std::unordered_set<VarName>>> resultValueVarSet = {};
        list<pair<StmtNum, std::unordered_set<VarName>>> resultStmtNumVarSet = {};
        list<pair<StmtNum, VarName>> resultStmtVar = {};
        list<pair<Value, Value>> resultValPair = {};
        ListOfStmtNos resultStmtList = {};
        vector<string> resultStrList = {};
        ListOfVarNames varLst = {};
        ListOfProcNames procLst = {};
        StmtNum largestStmtNum = 0;

        virtual list<pair<StmtNum, StmtNum>> getFollows(StmtNum, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getFollows(DesignEntity, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getFollows(StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getFollows(DesignEntity, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(StmtNum, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(DesignEntity, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(DesignEntity, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParents(StmtNum, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParents(DesignEntity, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParents(StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParents(DesignEntity, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParentsStar(StmtNum, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParentsStar(DesignEntity, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParentsStar(StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getParentsStar(DesignEntity, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<Value , std::unordered_set<VarName>>> getUses(const Value&, DesignEntity, const VarName&) {
            return resultValueVarSet;
        }
        
        virtual list<pair<Value , std::unordered_set<VarName>>> getModifies(const Value&, DesignEntity, const VarName&) {
            return resultValueVarSet;
        }

        virtual list<pair<Value, Value>> getCalls(const Value&, const Value&) {
            return resultValPair;
        }

        virtual list<pair<Value, Value>> getCallsStar(const Value&, const Value&) {
            return resultValPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNext(StmtNum, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNext(DesignEntity, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNext(StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNext(DesignEntity, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNextStar(StmtNum, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNextStar(DesignEntity, StmtNum) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNextStar(StmtNum, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<StmtNum, StmtNum>> getNextStar(DesignEntity, DesignEntity) {
            return resultStmtPair;
        }

        virtual list<pair<Value, Value>> getWith(DesignEntity, AttributeType, DesignEntity, AttributeType) {
            return resultValPair;
        }

        virtual list<pair<Value, Value>> getWith(DesignEntity, AttributeType, const Value&) {
            return resultValPair;
        }

        virtual list<pair<Value, Value>> getWith(const Value&, DesignEntity, AttributeType) {
            return resultValPair;
        }

        virtual list<pair<Value, Value>> getWith(const Value&, const Value&) {
            return resultValPair;
        }

        virtual list<pair<StmtNum, VarName>> getAssignPatternSubMatch(StmtNum , const Value&, PostFixExpression) {
            return resultStmtVar;
        }

        virtual list<pair<StmtNum, VarName>> getAssignPatternFullMatch(StmtNum, const Value&, PostFixExpression) {
            return resultStmtVar;
        }

        virtual list<pair<StmtNum, std::unordered_set<VarName>>> getIfPattern(StmtNum, const Value&) {
            return resultStmtNumVarSet;
        }

        virtual list<pair<StmtNum, std::unordered_set<VarName>>> getWhilePattern(StmtNum, const Value&) {
            return resultStmtNumVarSet;
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
