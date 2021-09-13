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
using std::vector;

namespace pql {
    class PkbAbstractor {

    public:
        virtual list<pair<StmtNum, StmtNum>> getDataFromFollows(StmtNum, DesignEntity, StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        virtual list<pair<StmtNum, StmtNum>> getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity);
        virtual list<pair<StmtNum, StmtNum>> getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        virtual list<pair<Value , std::unordered_set<VAR_NAME>>> getDataFromUses(Value, DesignEntity, VarName);
        virtual list<pair<Value , std::unordered_set<VAR_NAME>>> getDataFromModifies(Value, DesignEntity, VarName);

        virtual list<pair<StmtNum, VarName>> getPattern(StmtNum, Value, SubTree);

        virtual LIST_OF_STMT_NO getAllAssignStmts();
        virtual LIST_OF_STMT_NO getAllCallStmts();
        virtual vector<string> getAllConstants();
        virtual LIST_OF_STMT_NO getAllIfStmts();
        virtual LIST_OF_STMT_NO getAllWhileStmts();
        virtual LIST_OF_STMT_NO getAllPrintStmts();
        virtual LIST_OF_STMT_NO getAllReadStmts();
        virtual LIST_OF_VAR_NAME getAllVarNames();
        virtual LIST_OF_PROC_NAME getAllProcNames();
        virtual StmtNum getLargestStmtNum();
    };
}

#endif // GUARD_PKB_ABSTRACTOR_H
