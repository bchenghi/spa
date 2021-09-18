#include "TypeToStmtNumTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<pql::DesignEntity, ListOfStmtNos> TypeToStmtNumTable::typeToStmtMap;
unordered_map<StmtNo, pql::DesignEntity> TypeToStmtNumTable::stmtToTypeMap;
StmtNo TypeToStmtNumTable::largestStmt = 0;

bool TypeToStmtNumTable::addStmtWithType(pql::DesignEntity type, StmtNo stmt)
{
    if (stmt > TypeToStmtNumTable::largestStmt) {
        TypeToStmtNumTable::largestStmt = stmt;
    }

    TypeToStmtNumTable::typeToStmtMap[pql::DesignEntity::STMT].insert(stmt);

    auto res = TypeToStmtNumTable::typeToStmtMap.find(type);
    if (res != TypeToStmtNumTable::typeToStmtMap.end()) {
        ListOfStmtNos* stmtList = &(res->second);
        stmtList->insert(stmt);
        TypeToStmtNumTable::stmtToTypeMap[stmt] = type;
        return true;
    }
    else {
        TypeToStmtNumTable::typeToStmtMap[type] = ListOfStmtNos();
        TypeToStmtNumTable::typeToStmtMap[type].insert(stmt);
        TypeToStmtNumTable::stmtToTypeMap[stmt] = type;
        return true;
    }
}

ListOfStmtNos TypeToStmtNumTable::getStmtWithType(pql::DesignEntity type)
{
    auto res = TypeToStmtNumTable::typeToStmtMap.find(type);
    if (res != TypeToStmtNumTable::typeToStmtMap.end()) {
        return res->second;
    }
    else {
        return ListOfStmtNos();
    }
}

pql::DesignEntity TypeToStmtNumTable::getTypeOfStmt(StmtNo stmt)
{
    auto res = TypeToStmtNumTable::stmtToTypeMap.find(stmt);
    if (res != TypeToStmtNumTable::stmtToTypeMap.end()) {
        return res->second;
    }
    else {
        throw "None Statement Type.";
    }
}

StmtNo TypeToStmtNumTable::getLargestStmt()
{
    return TypeToStmtNumTable::largestStmt;
}

const unordered_map<pql::DesignEntity, ListOfStmtNos> & TypeToStmtNumTable::getTypeToStmtMap()
{
    return typeToStmtMap;
}

const unordered_map<StmtNo, pql::DesignEntity> & TypeToStmtNumTable::getStmtToTypeMap()
{
    return stmtToTypeMap;
}

void TypeToStmtNumTable::clear()
{
    stmtToTypeMap.clear();
    typeToStmtMap.clear();
    largestStmt = 0;
}
