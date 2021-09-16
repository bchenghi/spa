#ifndef GUARD_MODIFY_TABLE_H
#define GUARD_MODIFY_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

using std::unordered_map;

class ModifyTable {
public:
	static bool addStmtModify(STMT_NO stmt, VAR_NAME varName);
	static bool addProcModify(PROC_NAME procName, VAR_NAME varName);
	static bool isStmtModify(STMT_NO stmt, VAR_NAME varName);
	static bool isProcModify(PROC_NAME procName, VAR_NAME varName);
	static LIST_OF_VAR_NAME getStmtModify(STMT_NO stmt);
	static LIST_OF_VAR_NAME getProcModify(PROC_NAME stmt);
	static unordered_map<STMT_NO, LIST_OF_VAR_NAME> getStmtModifyMap();
	static unordered_map<PROC_NAME, LIST_OF_VAR_NAME> getProcModifyMap();
	static void clear();

private:
	static unordered_map<STMT_NO, LIST_OF_VAR_NAME> stmtModifyMap;
	static unordered_map<PROC_NAME, LIST_OF_VAR_NAME> procModifyMap;
};

#endif // GUARD_MODIFY_TABLE_H
