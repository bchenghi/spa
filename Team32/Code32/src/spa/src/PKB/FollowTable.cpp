#include "FollowTable.h"

#define INVALID_STMT_NO 0

unordered_map<STMT_NO, STMT_NO> FollowTable::followMap;
unordered_map<STMT_NO, STMT_NO> FollowTable::reverseFollowMap;
unordered_map<STMT_NO, LIST_OF_STMT_NO> FollowTable::followStarMap;
unordered_map<STMT_NO, LIST_OF_STMT_NO> FollowTable::reverseFollowStarMap;

bool FollowTable::addFollow(STMT_NO stmt1, STMT_NO stmt2)
{
	auto res = FollowTable::followMap.find(stmt1);
	if (res != FollowTable::followMap.end()) {
		if (res->second == stmt2) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		FollowTable::followMap[stmt1] = stmt2;
		FollowTable::reverseFollowMap[stmt1] = stmt2;
		return true;
	}
	return false;
}

bool FollowTable::addFollowStar(STMT_NO stmt, LIST_OF_STMT_NO stmtList)
{
	auto res = FollowTable::followStarMap.find(stmt);
	if (res != FollowTable::followStarMap.end()) {
		//I am not sure the expected behavior here when already a stmtList exist.
		//Append to the stmtList? or Return a false.
		throw "Undefined.";
	}
	else {
		FollowTable::followStarMap[stmt] = stmtList;
		return true;
	}
	return false;
}

bool FollowTable::addFollowStarBy(STMT_NO stmt, LIST_OF_STMT_NO stmtList)
{
	auto res = FollowTable::reverseFollowStarMap.find(stmt);
	if (res != FollowTable::reverseFollowStarMap.end()) {
		//I am not sure the expected behavior here when already a stmtList exist.
		//Append to the stmtList? or Return a false.
		throw "Undefined.";
	}
	else {
		FollowTable::reverseFollowStarMap[stmt] = stmtList;
		return true;
	}
	return false;
}

bool FollowTable::isFollow(STMT_NO stmt1, STMT_NO stmt2)
{
	auto res = FollowTable::followMap.find(stmt1);
	if (res != FollowTable::followMap.end()) {
		if (res->second == stmt2) {
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

bool FollowTable::isFollowStar(STMT_NO stmt1, STMT_NO stmt2)
{
	auto res = FollowTable::followStarMap.find(stmt1);
	if (res != FollowTable::followStarMap.end()) {
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

STMT_NO FollowTable::getFollowedBy(STMT_NO stmt2)
{
	auto res = FollowTable::reverseFollowMap.find(stmt2);
	if (res != FollowTable::reverseFollowMap.end()) {
		return res->second;
	}
	else {
		return INVALID_STMT_NO;
	}
	return INVALID_STMT_NO;
}

STMT_NO FollowTable::getFollow(STMT_NO stmt1)
{
	auto res = FollowTable::followMap.find(stmt1);
	if (res != FollowTable::followMap.end()) {
		return res->second;
	}
	else {
		return INVALID_STMT_NO;
	}
	return INVALID_STMT_NO;
}

LIST_OF_STMT_NO FollowTable::getFollowedStarBy(STMT_NO stmt2)
{
	auto res = FollowTable::reverseFollowStarMap.find(stmt2);
	if (res != FollowTable::reverseFollowStarMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_STMT_NO();
	}
	return LIST_OF_STMT_NO();
}

LIST_OF_STMT_NO FollowTable::getFollowStar(STMT_NO stmt1)
{
	auto res = FollowTable::followStarMap.find(stmt1);
	if (res != FollowTable::followStarMap.end()) {
		return res->second;
	}
	else {
		return LIST_OF_STMT_NO();
	}
	return LIST_OF_STMT_NO();
}

unordered_map<STMT_NO, STMT_NO> FollowTable::getFollowMap() {
    return followMap;
}

unordered_map<STMT_NO, LIST_OF_STMT_NO> FollowTable::getFollowStarMap() {
    return followStarMap;
}

void FollowTable::clear() {
    followMap.clear();
    followStarMap.clear();
    reverseFollowStarMap.clear();
    reverseFollowMap.clear();
}
