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
typedef std::string VarName;

namespace pql {
    class PkbAbstractor {
    public:
        VarTable varTable;
        ProcTable procTable;
        static FollowsTable followsTable;
        ParentsTable parentsTable;
        UsesTable usesTable;
        ModifiesTable modifiesTable;
        AssignAstTable assignAstTable;
        TypeToStmtNo typeToStmtNoTable;

        static VarTable getVarTable();
        static ProcTable getProcTable();

        static FollowsTable getFollowsTable();
        static ParentsTable getParentsTable();
        static UsesTable getUsesTable();
        static ModifiesTable getModifiesTable();

        static TypeToStmtNo getTypeToStmtNoTable();

        static std::list<std::pair<StmtNum, StmtNum>> getDataFromFollows(DesignEntity, StmtNum, DesignEntity, StmtNum, DesignEntity);
        static Data getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        static Data getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity);

        static Data getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);
        static Data getDataFromUses(StmtNum, DesignEntity, VarName);

        static Data getDataFromModifies(StmtNum, DesignEntity, VarName);
        static AssignAstTable getAssignAstTable();
        static bool checkAstContains(StmtNum, *AST_Node, std::string, std::string);

        //        static std::list<StmtNum> getAssignList();
        //        static std::list<StmtNum> getCallList();
        //        static std::list<StmtNum> getPrintList();
        //        static std::list<StmtNum> getReadList();
        //        static std::list<StmtNum> getIfList();
        //        static std::list<StmtNum> getWhileList();

    };
}

#endif // GUARD_PKB_ABSTRACTOR_H