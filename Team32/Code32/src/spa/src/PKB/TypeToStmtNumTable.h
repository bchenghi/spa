#ifndef GUARD_TYPE_TO_STMT_NUM_TABLE_H
#define GUARD_TYPE_TO_STMT_NUM_TABLE_H

#include "pql/DesignEntity.h"
#include "TypePreDefine.h"

#include <unordered_map>

class TypeToStmtNumTable {
public:
    static bool addStmtWithType(pql::DesignEntity type, STMT_NO stmt);
    static LIST_OF_STMT_NO getStmtWithType(pql::DesignEntity type);
    static pql::DesignEntity getTypeOfStmt(STMT_NO stmt);
    static STMT_NO getLargestStmt();
    static const std::unordered_map<pql::DesignEntity, LIST_OF_STMT_NO>& getTypeToStmtMap();
    static const std::unordered_map<STMT_NO, pql::DesignEntity>& getStmtToTypeMap();
    static void clear();

private:
    static std::unordered_map<pql::DesignEntity, LIST_OF_STMT_NO> typeToStmtMap;
    static std::unordered_map<STMT_NO, pql::DesignEntity> stmtToTypeMap;
    static STMT_NO largestStmt;
};

#endif //GUARD_TYPE_TO_STMT_NUM_TABLE_H
