#ifndef GUARD_USE_TABLE_H
#define GUARD_USE_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

using std::unordered_map;

class UseTable {
public:
	static bool addStmtUse(STMT_NO stmt, VAR_NAME varName);
	static bool addProcUse(PROC_NAME procName, VAR_NAME varName);
	static bool isStmtUse(STMT_NO stmt, VAR_NAME varName);
	static bool isProcUse(PROC_NAME procName, VAR_NAME varName);
	static LIST_OF_VAR_NAME getStmtUse(STMT_NO stmt);
	static LIST_OF_VAR_NAME getProcUse(PROC_NAME procName);
	static unordered_map<STMT_NO, LIST_OF_VAR_NAME> getStmtUseMap();
	static unordered_map<PROC_NAME , LIST_OF_VAR_NAME > getProUseMap();

private:
	static unordered_map<STMT_NO, LIST_OF_VAR_NAME> stmtUseMap;
	static unordered_map<PROC_NAME, LIST_OF_VAR_NAME> procUseMap;
};

#endif // GUARD_USE_TABLE_H
