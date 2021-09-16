#include "ProcTable.h"

unordered_map<PROC_NAME, LIST_OF_STMT_NO> ProcTable::nameToStmtListMap;
LIST_OF_PROC_NAME ProcTable::procNameList;
int ProcTable::size = 0;

bool ProcTable::addProc(PROC_NAME procName, LIST_OF_STMT_NO stmtNumList)
{
	auto res = ProcTable::nameToStmtListMap.find(procName);
	if (res != ProcTable::nameToStmtListMap.end()) {
		//I am not sure the expected behavior here when already a stmtList exist.
		//Append to the stmtList? or Return a false.
		throw "Undefined.";
	}
	else {
		ProcTable::nameToStmtListMap[procName] = stmtNumList;
		ProcTable::procNameList.push_back(procName);
	}
	return false;
}

LIST_OF_STMT_NO ProcTable::getProcStmtList(PROC_NAME procName)
{
	auto res = ProcTable::nameToStmtListMap.find(procName);
	if (res != ProcTable::nameToStmtListMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_STMT_NO();
	}
	return LIST_OF_STMT_NO();
}

LIST_OF_PROC_NAME ProcTable::getAllProcedure()
{
	return ProcTable::procNameList;
}

int ProcTable::getSize()
{
	return ProcTable::size;
}

void ProcTable::clear() {
    procNameList.clear();
    nameToStmtListMap.clear();
}
