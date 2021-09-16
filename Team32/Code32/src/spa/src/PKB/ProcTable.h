#ifndef GUARD_PROC_TABLE_H
#define GUARD_PROC_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

using std::unordered_map;

class ProcTable {
public:
	static bool addProc(PROC_NAME procName, LIST_OF_STMT_NO stmtNumList);
	static LIST_OF_STMT_NO getProcStmtList(PROC_NAME procName);
	static LIST_OF_PROC_NAME getAllProcedure();
	static int getSize();
	static void clear();

private:
	static unordered_map<PROC_NAME, LIST_OF_STMT_NO> nameToStmtListMap;
	static LIST_OF_PROC_NAME procNameList;
	static int size;
};

#endif // GUARD_PROC_TABLE_H
