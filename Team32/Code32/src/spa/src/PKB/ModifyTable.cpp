#include "ModifyTable.h"

unordered_map<STMT_NO, LIST_OF_VAR_NAME> ModifyTable::stmtModifyMap;
unordered_map<PROC_NAME, LIST_OF_VAR_NAME> ModifyTable::procModifyMap;

bool ModifyTable::addStmtModify(STMT_NO stmt, VAR_NAME varName)
{
	auto res = ModifyTable::stmtModifyMap.find(stmt);
	if (res != ModifyTable::stmtModifyMap.end()) {
		LIST_OF_VAR_NAME* varList = &(res->second);
		varList->insert(varName);
		return true;
	}
	else {
		ModifyTable::stmtModifyMap[stmt] = LIST_OF_VAR_NAME();
		ModifyTable::stmtModifyMap[stmt].insert(varName);
		return true;
	}
	return false;
}

bool ModifyTable::addProcModify(PROC_NAME procName, VAR_NAME varName)
{
	auto res = ModifyTable::procModifyMap.find(procName);
	if (res != ModifyTable::procModifyMap.end()) {
		LIST_OF_VAR_NAME* varList = &(res->second);
		varList->insert(varName);
		return true;
	}
	else {
		ModifyTable::procModifyMap[procName] = LIST_OF_VAR_NAME();
		ModifyTable::procModifyMap[procName].insert(varName);
		return true;
	}
	return false;
}

bool ModifyTable::isStmtModify(STMT_NO stmt, VAR_NAME varName)
{
	auto res = ModifyTable::stmtModifyMap.find(stmt);
	if (res != ModifyTable::stmtModifyMap.end()) {
		if (res->second.count(varName) == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return false;
}

bool ModifyTable::isProcModify(PROC_NAME procName, VAR_NAME varName)
{
	auto res = ModifyTable::procModifyMap.find(procName);
	if (res != ModifyTable::procModifyMap.end()) {
		if (res->second.count(varName) == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return false;
}

LIST_OF_VAR_NAME ModifyTable::getStmtModify(STMT_NO stmt)
{
	auto res = ModifyTable::stmtModifyMap.find(stmt);
	if (res != ModifyTable::stmtModifyMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_VAR_NAME();
	}
	return LIST_OF_VAR_NAME();
}

LIST_OF_VAR_NAME ModifyTable::getProcModify(PROC_NAME procName)
{
	auto res = ModifyTable::procModifyMap.find(procName);
	if (res != ModifyTable::procModifyMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_VAR_NAME();
	}
	return LIST_OF_VAR_NAME();
}

unordered_map<STMT_NO, LIST_OF_VAR_NAME> ModifyTable::getStmtModifyMap() {
    return stmtModifyMap;
}

unordered_map<PROC_NAME, LIST_OF_VAR_NAME> ModifyTable::getProcModifyMap() {
    return procModifyMap;
}

void ModifyTable::clear() {
    stmtModifyMap.clear();
    procModifyMap.clear();
}
