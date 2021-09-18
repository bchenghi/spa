#ifndef GUARD_TYPE_TO_STMT_NUM_TABLE_H
#define GUARD_TYPE_TO_STMT_NUM_TABLE_H

#include "pql/DesignEntity.h"
#include "TypePreDefine.h"

#include <unordered_map>

class TypeToStmtNumTable {
public:
    static bool addStmtWithType(pql::DesignEntity type, StmtNo stmt);
    static ListOfStmtNos getStmtWithType(pql::DesignEntity type);
    static pql::DesignEntity getTypeOfStmt(StmtNo stmt);
    static StmtNo getLargestStmt();
    static const std::unordered_map<pql::DesignEntity, ListOfStmtNos>& getTypeToStmtMap();
    static const std::unordered_map<StmtNo, pql::DesignEntity>& getStmtToTypeMap();
    static void clear();

private:
    static std::unordered_map<pql::DesignEntity, ListOfStmtNos> typeToStmtMap;
    static std::unordered_map<StmtNo, pql::DesignEntity> stmtToTypeMap;
    static StmtNo largestStmt;
};

#endif //GUARD_TYPE_TO_STMT_NUM_TABLE_H
