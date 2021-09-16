#include "ParentTable.h"

#define INVALID_STMT_NO 0

unordered_map<STMT_NO, LIST_OF_STMT_NO> ParentTable::parentMap;
unordered_map<STMT_NO, STMT_NO> ParentTable::reverseParentMap;
unordered_map<STMT_NO, LIST_OF_STMT_NO> ParentTable::parentStarMap;
unordered_map<STMT_NO, LIST_OF_STMT_NO> ParentTable::reverseParentStarMap;


bool ParentTable::addParent(STMT_NO stmt1, LIST_OF_STMT_NO stmtList)
{
	auto res = ParentTable::parentMap.find(stmt1);
	if (res != ParentTable::parentMap.end()) {
		//I am not sure the expected behavior here when already a stmtList exist.
		//Append to the stmtList? or Return a false.
		throw "Undefined.";
	}
	else {
		ParentTable::parentMap[stmt1] = stmtList;
		for (auto iter = stmtList.begin(); iter != stmtList.end(); ++iter) {
			size_t stmtNum = *iter;
			auto res_ = ParentTable::reverseParentMap.find(stmtNum);
			if (res_ != ParentTable::reverseParentMap.end()) {
				if (res_->second == stmt1) {
					continue;
				} else {
					return false;
				}
			}
			else {
				ParentTable::reverseParentMap[stmtNum] = stmt1;
			}
		}
		return true;
	}
	return false;
}

bool ParentTable::addChildrenStar(STMT_NO stmt, LIST_OF_STMT_NO stmtList)
{
	auto res = ParentTable::parentStarMap.find(stmt);
	if (res != ParentTable::parentStarMap.end()) {
		//I am not sure the expected behavior here when already a stmtList exist.
		//Append to the stmtList? or Return a false.
		throw "Undefined.";
	}
	else {
		ParentTable::parentStarMap[stmt] = stmtList;
		return true;
	}
	return false;
}

bool ParentTable::addParentStar(STMT_NO stmt, LIST_OF_STMT_NO stmtList)
{
	auto res = ParentTable::reverseParentStarMap.find(stmt);
	if (res != ParentTable::reverseParentStarMap.end()) {
		//I am not sure the expected behavior here when already a stmtList exist.
		//Append to the stmtList? or Return a false.
		throw "Undefined.";
	}
	else {
		ParentTable::reverseParentStarMap[stmt] = stmtList;
		return true;
	}
	return false;
}

bool ParentTable::isParent(STMT_NO stmt1, STMT_NO stmt2)
{
	auto res = ParentTable::parentMap.find(stmt1);
	if (res != ParentTable::parentMap.end()) {
		if (res->second.count(stmt2) == 1) {
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

bool ParentTable::isParentStar(STMT_NO stmt1, STMT_NO stmt2)
{
	auto res = ParentTable::parentStarMap.find(stmt1);
	if (res != ParentTable::parentStarMap.end()) {
		if (res->second.count(stmt2) == 1) {
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

STMT_NO ParentTable::getParent(STMT_NO stmt2)
{
	auto res = ParentTable::reverseParentMap.find(stmt2);
	if (res != ParentTable::reverseParentMap.end()) {
		return res->second;
	}
	else {
		return INVALID_STMT_NO;
	}
	return INVALID_STMT_NO;
}

LIST_OF_STMT_NO ParentTable::getChildren(STMT_NO stmt1)
{
	auto res = ParentTable::parentMap.find(stmt1);
	if (res != ParentTable::parentMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_STMT_NO();
	}
	return LIST_OF_STMT_NO();
}

LIST_OF_STMT_NO ParentTable::getParentStar(STMT_NO stmt2)
{
	auto res = ParentTable::reverseParentStarMap.find(stmt2);
	if (res != ParentTable::reverseParentStarMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_STMT_NO();
	}
	return LIST_OF_STMT_NO();
}

LIST_OF_STMT_NO ParentTable::getChildrenStar(STMT_NO stmt1)
{
	auto res = ParentTable::parentStarMap.find(stmt1);
	if (res != ParentTable::parentStarMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_STMT_NO();
	}
	return LIST_OF_STMT_NO();
}

const unordered_map<STMT_NO, LIST_OF_STMT_NO> & ParentTable::getParentMap() {
    return parentMap;
}

const unordered_map<STMT_NO, STMT_NO> & ParentTable::getParentReverseMap() {
    return reverseParentMap;
}

const unordered_map<STMT_NO, LIST_OF_STMT_NO> & ParentTable::getParentStarMap() {
    return parentStarMap;
}

void ParentTable::clear() {
    parentMap.clear();
    reverseParentMap.clear();
    parentStarMap.clear();
    reverseParentStarMap.clear();
}
