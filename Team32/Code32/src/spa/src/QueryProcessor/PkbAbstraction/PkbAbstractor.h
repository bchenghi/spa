#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>

// include pkb api
#include "../src/QueryProcessor/DesignEntity.h"

typedef int StmtNo;
typedef std::string VarName;

class PkbAbstractor {
    public:
        VarTable varTable;
        ProcTable procTable;
        FollowsTable followsTable;
        ParentsTable parentsTable;
        UsesTable usesTable;
        ModifiesTable modifiesTable;
        AssignAstTable assignAstTable;

        static VarTable getVarTable();
        static ProcTable getProcTable();

        static FollowsTable getFollowsTable();
        static ParentsTable getParentsTable();
        static UsesTable getUsesTable();
        static ModifiesTable getModifiesTable();

        static Data getDataFromFollows(StmtNo, DesignEntity, StmtNo, DesignEntity);
        static Data getDataFromFollowsStar(StmtNo, DesignEntity, StmtNo, DesignEntity);
        static Data getDataFromParents(StmtNo, DesignEntity, StmtNo, DesignEntity);
        static Data getDataFromParentsStar(StmtNo, DesignEntity, StmtNo, DesignEntity);
        static Data getDataFromUses(StmtNo, DesignEntity, VarName);
        static Data getDataFromModifies(StmtNo, DesignEntity, VarName);

        static AssignAstTable getAssignAstTable();
        static bool checkAstContains(StmtNo, *AST_Node, std::string, std::string);

        static std::list<StmtNo> getAssignList();
        static std::list<StmtNo> getCallList();
        static std::list<StmtNo> getPrintList();
        static std::list<StmtNo> getReadList();
        static std::list<StmtNo> getIfList();
        static std::list<StmtNo> getWhileList();

};
