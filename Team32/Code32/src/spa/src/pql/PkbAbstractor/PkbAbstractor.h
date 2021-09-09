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

//        static VarTable varTable;
//        static ProcTable procTable;
//        static FollowsTable followsTable;
//        static ParentsTable parentsTable;
//        static UsesTable usesTable;
//        static ModifiesTable modifiesTable;
//        static AssignAstTable assignAstTable;
//        static TypeToStmtNo typeToStmtNoTable;
//
//        PkbAbstractor(Pkb* pkb) {
//            varTable = pkb.getVarTable();
//            procTable = pkb.getProcTable();
//            followsTable = pkb.getFollowsTable();
//            parentsTable = pkb.getParentsTable();
//            usesTable = pkb.getUsesTable();
//            modifiesTable = pkb.getModifiesTable();
//            assignAstTable = pkb.getAssignAstTable();
//            typeToStmtNoTable = pkb.getTypeToStmtNoTable();
//        }

        static list<pair<StmtNum, StmtNum>> getDataFromFollows(StmtNum, DesignEntity, StmtNum, DesignEntity);
        list<pair<StmtNum, StmtNum>> getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        list<pair<StmtNum, StmtNum>> getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity);
        list<pair<StmtNum, StmtNum>> getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        list<pair<Value , list<VarName>>> getDataFromUses(Value, DesignEntity, VarName);
        list<pair<Value , list<VarName>>> getDataFromModifies(Value, DesignEntity, VarName);

        list<pair<StmtNum, VarName>> getPattern(StmtNum, Value, SubTree);

        list<StmtNum> getAllAssignStmts();
        list<StmtNum> getAllCallStmts();
        list<string> getAllConstants();
        list<StmtNum> getAllIfStmts();
        list<StmtNum> getAllWhileStmts();
        list<StmtNum> getAllPrintStmts();
        list<StmtNum> getAllReadStmts();
        list<VarName> getAllVarNames();
        list<ProcName> getAllProcNames();
        StmtNum getLargestStmtNum();

//        VarTable getVarTable();
//        static UsesTable getUsesTable();


    };
}

#endif // GUARD_PKB_ABSTRACTOR_H
