#ifndef GUARD_PKB_ABSTRACTOR_H
#define GUARD_PKB_ABSTRACTOR_H

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>

// include pkb api
#include "../src/pql/DesignEntity.h"

typedef int StmtNum;
//typedef std::string VarName;
using std::string;
using std::list;
using std::pair;

namespace pql {
    class PkbAbstractor {
    public:
        VarTable varTable;
        ProcTable procTable;
        static FollowsTable followsTable;
        static ParentsTable parentsTable;
        UsesTable usesTable;
        ModifiesTable modifiesTable;
        AssignAstTable assignAstTable;
        static TypeToStmtNo typeToStmtNoTable;

        PkbAbstractor(Pkb* pkb) {
            varTable = pkb.getVarTable();
            procTable = pkb.getProcTable();
            followsTable = pkb.getFollowsTable();
            parentsTable = pkb.getParentsTable();
            usesTable = pkb.getUsesTable();
            modifiesTable = pkb.getModifiesTable();
            assignAstTable = pkb.getAssignAstTable();
            typeToStmtNoTable = pkb.getTypeToStmtNoTable();
        }

//        static VarTable getVarTable();
//        static ProcTable getProcTable();
//
//        static FollowsTable getFollowsTable();
//        static ParentsTable getParentsTable();
//        static UsesTable getUsesTable();
//        static ModifiesTable getModifiesTable();
//
//        static TypeToStmtNo getTypeToStmtNoTable();
//        static AssignAstTable getAssignAstTable();


        static list<pair<StmtNum, StmtNum>> getDataFromFollows(StmtNum, DesignEntity, StmtNum, DesignEntity);
        static list<pair<StmtNum, StmtNum>> getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        static list<pair<StmtNum, StmtNum>> getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity);
        static list<pair<StmtNum, StmtNum>> getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        static list<pair<string , list<string>>> getDataFromUses(StmtNum, DesignEntity, VarName);
        static list<pair<string , list<string>>> getDataFromModifies(StmtNum, DesignEntity, VarName);

        static bool checkAstContains(StmtNum, *AST_Node, std::string, std::string);
    };
}

#endif // GUARD_PKB_ABSTRACTOR_H