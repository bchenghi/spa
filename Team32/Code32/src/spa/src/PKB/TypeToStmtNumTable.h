#ifndef GUARD_TYPE_TO_STMT_NUM_H
#define GUARD_TYPE_TO_STMT_NUM_H

#include <unordered_map>
#include <vector>

#include "pql/DesignEntity.h"

using std::unordered_map;
using std::vector;

typedef int STMT_NO;
typedef vector<STMT_NO> LIST_OF_STMT_NO;

class TypeToStmtNumTable {
public:
    static bool addStmtWithType(pql::DesignEntity type, STMT_NO stmtNo);
    static LIST_OF_STMT_NO getStmtWithType(pql::DesignEntity type);
    static pql::DesignEntity getTypeOfStmt(STMT_NO stmtNo);

private:
    static unordered_map<pql::DesignEntity, LIST_OF_STMT_NO> typeToStmtMap;
    static unordered_map<STMT_NO, pql::DesignEntity> stmtToType;
};

#endif //GUARD_TYPE_TO_STMT_NUM_H