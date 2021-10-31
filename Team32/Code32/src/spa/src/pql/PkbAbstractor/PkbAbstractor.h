#ifndef GUARD_PKB_ABSTRACTOR_H
#define GUARD_PKB_ABSTRACTOR_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>

#include "../src/pql/DesignEntity.h"
#include "../src/pql/AttributeType.h"

#include "../src/PKB/AssignPostFixTable.h"
#include "../src/PKB/FollowTable.h"
#include "../src/PKB/ParentTable.h"
#include "../src/PKB/ModifyTable.h"
#include "../src/PKB/UseTable.h"
#include "../src/PKB/ProcTable.h"
#include "../src/PKB/VarTable.h"
#include "../src/PKB/TypeToStmtNumTable.h"
#include "../src/PKB/ConstantTable.h"
#include "../src/PKB/IfControlTable.h"
#include "../src/PKB/WhileControlTable.h"
#include "../src/PKB/CallTable.h"
#include "../src/PKB/CallStmtTable.h"
#include "../src/PKB/NextTable.h"
#include "../src/PKB/CFGTable.h"
#include "../src/PKB/CFGBipTable.h"
#include "../src/PKB/NextBipTable.h"

typedef size_t StmtNum;
typedef std::string VarName;
typedef std::string ProcName;
typedef std::string Value;
typedef std::vector<std::string> PostFixExpression;

using std::string;
using std::list;
using std::pair;
using std::vector;

namespace pql {
    class PkbAbstractor {

    public:
        virtual list<pair<StmtNum, StmtNum>> getFollows(StmtNum, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getFollows(DesignEntity, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getFollows(StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getFollows(DesignEntity, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(StmtNum, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(DesignEntity, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getFollowsStar(DesignEntity, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getParents(StmtNum, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getParents(DesignEntity, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getParents(StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getParents(DesignEntity, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getParentsStar(StmtNum, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getParentsStar(DesignEntity, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getParentsStar(StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getParentsStar(DesignEntity, DesignEntity);

        virtual list<pair<Value, std::unordered_set<VarName>>> getDataFromUses(const Value&, DesignEntity, const VarName&);
        virtual list<pair<Value, std::unordered_set<VarName>>> getDataFromModifies(const Value&, DesignEntity, const VarName&);

        virtual list<pair<Value, Value>> getDataFromCalls(const Value&, const Value&);
        virtual list<pair<Value, Value>> getDataFromCallsStar(const Value&, const Value&);

        virtual list<pair<StmtNum, StmtNum>> getNext(ProgLine, ProgLine);
        virtual list<pair<StmtNum, StmtNum>> getNext(DesignEntity, ProgLine);
        virtual list<pair<StmtNum, StmtNum>> getNext(ProgLine, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getNext(DesignEntity, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getNextStar(StmtNum, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getNextStar(DesignEntity, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getNextStar(StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getNextStar(DesignEntity, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getDataFromAffects(StmtNum, StmtNum);
        virtual list<pair<StmtNum, StmtNum>> getDataFromAffectsStar(StmtNum, StmtNum);


        virtual list<pair<StmtNum, StmtNum>> getNextBip(ProgLine, ProgLine);
        virtual list<pair<StmtNum, StmtNum>> getNextBip(DesignEntity, ProgLine);
        virtual list<pair<StmtNum, StmtNum>> getNextBip(ProgLine, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getNextBip(DesignEntity, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getNextBipStar(ProgLine, ProgLine);
        virtual list<pair<StmtNum, StmtNum>> getNextBipStar(DesignEntity, ProgLine);
        virtual list<pair<StmtNum, StmtNum>> getNextBipStar(ProgLine, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getNextBipStar(DesignEntity, DesignEntity);
//
        virtual list<pair<StmtNum, StmtNum>> getDataFromAffectsBip(StmtNum, StmtNum);
//        virtual list<pair<StmtNum, StmtNum>> getDataFromAffectsBipStar(StmtNum, StmtNum);

        virtual list<pair<StmtNum, VarName>> getAssignPattern(StmtNum assignStmtNum, const Value &value, PostFixExpression postFixExpression, bool hasUnderscores);

        virtual list<pair<StmtNum, std::unordered_set<VarName>>> getWhilePattern(StmtNum, const Value&);
        virtual list<pair<StmtNum, std::unordered_set<VarName>>> getIfPattern(StmtNum, const Value&);

        virtual list<pair<Value, Value>> getDataFromWith(const Value&, DesignEntity, AttributeType, const Value&, DesignEntity, AttributeType);

        virtual Value getAttributeVal(StmtNum, DesignEntity, AttributeType);

        virtual ListOfStmtNos getAllAssignStmts();
        virtual ListOfStmtNos getAllCallStmts();
        virtual vector<string> getAllConstants();
        virtual ListOfStmtNos getAllIfStmts();
        virtual ListOfStmtNos getAllWhileStmts();
        virtual ListOfStmtNos getAllPrintStmts();
        virtual ListOfStmtNos getAllReadStmts();
        virtual ListOfVarNames getAllVarNames();
        virtual ListOfProcNames getAllProcNames();
        virtual StmtNum getLargestStmtNum();
        virtual void clear();
    };
}

#endif // GUARD_PKB_ABSTRACTOR_H
