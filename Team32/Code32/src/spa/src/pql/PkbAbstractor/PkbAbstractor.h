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
        virtual list<pair<StmtNum, StmtNum>> getDataFromFollows(StmtNum, DesignEntity, StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        virtual list<pair<Value, std::unordered_set<VarName>>> getDataFromUses(const Value&, DesignEntity, const VarName&);
        virtual list<pair<Value, std::unordered_set<VarName>>> getDataFromModifies(const Value&, DesignEntity, const VarName&);

        virtual list<pair<Value, Value>> getDataFromCalls(const Value&, const Value&);
        virtual list<pair<Value, Value>> getDataFromCallsStar(const Value&, const Value&);

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
    };
}

#endif // GUARD_PKB_ABSTRACTOR_H
