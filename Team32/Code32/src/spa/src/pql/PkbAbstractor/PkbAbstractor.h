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
typedef std::string Value;
typedef std::string SubTree;

using std::string;
using std::list;
using std::pair;

namespace pql {
    class PkbAbstractor {
    private:
        VarTable varTable;
        ProcTable procTable;
        FollowsTable followsTable;
        ParentsTable parentsTable;
        UsesTable usesTable;
        ModifiesTable modifiesTable;
        AssignAstTable assignAstTable;
        TypeToStmtNo typeToStmtNoTable;

    public:
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

        list<pair<StmtNum, StmtNum>> getDataFromFollows(StmtNum, DesignEntity, StmtNum, DesignEntity);
        list<pair<StmtNum, StmtNum>> getDataFromFollowsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        list<pair<StmtNum, StmtNum>> getDataFromParents(StmtNum, DesignEntity, StmtNum, DesignEntity);
        list<pair<StmtNum, StmtNum>> getDataFromParentsStar(StmtNum, DesignEntity, StmtNum, DesignEntity);

        list<pair<Value , list<VarName>>> getDataFromUses(Value, DesignEntity, VarName);
        list<pair<Value , list<VarName>>> getDataFromModifies(Value, DesignEntity, VarName);

        list<pair<StmtNum, VarName>> getPattern(StmtNum, Value, SubTree);
    };
}

#endif // GUARD_PKB_ABSTRACTOR_H
