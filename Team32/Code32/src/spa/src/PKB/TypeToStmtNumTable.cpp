#include "TypeToStmtNumTable.h"

unordered_map<pql::DesignEntity, LIST_OF_STMT_NO> TypeToStmtNumTable::typeToStmtMap;
unordered_map<STMT_NO, pql::DesignEntity> TypeToStmtNumTable::stmtToTypeMap;

bool TypeToStmtNumTable::addStmtWithType(pql::DesignEntity type, STMT_NO stmt)
{
	auto res = TypeToStmtNumTable::typeToStmtMap.find(type);
	if (res != TypeToStmtNumTable::typeToStmtMap.end()) {
		LIST_OF_STMT_NO* stmtList = &(res->second);
		stmtList->insert(stmt);
		TypeToStmtNumTable::stmtToTypeMap[stmt] = type;
		return true;
	}
	else {
		TypeToStmtNumTable::typeToStmtMap[type] = LIST_OF_STMT_NO();
		TypeToStmtNumTable::typeToStmtMap[type].insert(stmt);
		TypeToStmtNumTable::stmtToTypeMap[stmt] = type;
		return true;
	}
	return false;
}

LIST_OF_STMT_NO TypeToStmtNumTable::getStmtWithType(pql::DesignEntity type)
{
	auto res = TypeToStmtNumTable::typeToStmtMap.find(type);
	if (res != TypeToStmtNumTable::typeToStmtMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_STMT_NO();
	}
	return LIST_OF_STMT_NO();
}

pql::DesignEntity TypeToStmtNumTable::getTypeOfStmt(STMT_NO stmt)
{
	auto res = TypeToStmtNumTable::stmtToTypeMap.find(stmt);
	if (res != TypeToStmtNumTable::stmtToTypeMap.end()) {
		return res->second;
	}
	else {
		throw "None Statement Type.";
	}
}
