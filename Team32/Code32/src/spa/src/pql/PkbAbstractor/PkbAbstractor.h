#ifndef GUARD_PKB_ABSTRACTOR_H
#define GUARD_PKB_ABSTRACTOR_H

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>

#include "../src/pql/DesignEntity.h"

#include "../src/PKB/FollowTable.h"
#include "../src/PKB/ParentTable.h"
#include "../src/PKB/ModifyTable.h"
#include "../src/PKB/UseTable.h"
#include "../src/PKB/ProcTable.h"
#include "../src/PKB/VarTable.h"
#include "../src/PKB/TypeToStmtNumTable.h"


typedef int StmtNum;
typedef std::string VarName;
typedef std::string ProcName;
typedef std::string Value;
typedef std::string SubTree;

using std::string;
using std::list;
using std::pair;

namespace pql {
    class PkbAbstractor {

    public:
        static list<pair<StmtNum, StmtNum>> getDataFromFollows(StmtNum, DesignEntity, StmtNum, DesignEntity);
        static list<pair<StmtNum, StmtNum>> getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        static list<pair<StmtNum, StmtNum>> getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity);
        static list<pair<StmtNum, StmtNum>> getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        static list<pair<Value , unordered_set<VAR_NAME>>> getDataFromUses(Value, DesignEntity, VarName);
        static list<pair<Value , unordered_set<VAR_NAME>>> getDataFromModifies(Value, DesignEntity, VarName);

        static list<pair<StmtNum, VarName>> getPattern(StmtNum, Value, SubTree);

        static LIST_OF_STMT_NO getAllAssignStmts();
        static LIST_OF_STMT_NO getAllCallStmts();
        static LIST_OF_STMT_NO getAllConstants();
        static LIST_OF_STMT_NO getAllIfStmts();
        static LIST_OF_STMT_NO getAllWhileStmts();
        static LIST_OF_STMT_NO getAllPrintStmts();
        static LIST_OF_STMT_NO getAllReadStmts();
        static LIST_OF_VAR_NAME getAllVarNames();
        static LIST_OF_PROC_NAME getAllProcNames();
        static StmtNum getLargestStmtNum();
    };
}

#endif // GUARD_PKB_ABSTRACTOR_H
