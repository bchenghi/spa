#ifndef GUARD_TYPE_TO_STMT_NUM_TABLE_H
#define GUARD_TYPE_TO_STMT_NUM_TABLE_H

#include <unordered_map>

#include "TypePreDefine.h"
#include "pql/DesignEntity.h"

using std::unordered_map;

class TypeToStmtNumTable {
public:
	static bool addStmtWithType(pql::DesignEntity type, STMT_NO stmt);
	static LIST_OF_STMT_NO getStmtWithType(pql::DesignEntity type);
	static pql::DesignEntity getTypeOfStmt(STMT_NO stmt);

private:
	static unordered_map<pql::DesignEntity, LIST_OF_STMT_NO> typeToStmtMap;
	static unordered_map<STMT_NO, pql::DesignEntity> stmtToTypeMap;
};

#endif //GUARD_TYPE_TO_STMT_NUM_TABLE_H
