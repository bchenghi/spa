#include "TypeToStmtNumTable.h"

#include <unordered_map>

using std::unordered_map;

unordered_map<pql::DesignEntity, LIST_OF_STMT_NO> TypeToStmtNumTable::typeToStmtMap;
unordered_map<STMT_NO, pql::DesignEntity> TypeToStmtNumTable::stmtToTypeMap;
STMT_NO TypeToStmtNumTable::largestStmt = 0;

bool TypeToStmtNumTable::addStmtWithType(pql::DesignEntity type, STMT_NO stmt)
{
    if (stmt > TypeToStmtNumTable::largestStmt) {
        TypeToStmtNumTable::largestStmt = stmt;
    }

    TypeToStmtNumTable::typeToStmtMap[pql::DesignEntity::Stmt].insert(stmt);

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

STMT_NO TypeToStmtNumTable::getLargestStmt()
{
    return TypeToStmtNumTable::largestStmt;
}

const unordered_map<pql::DesignEntity, LIST_OF_STMT_NO> & TypeToStmtNumTable::getTypeToStmtMap()
{
    return typeToStmtMap;
}

const unordered_map<STMT_NO, pql::DesignEntity> & TypeToStmtNumTable::getStmtToTypeMap()
{
    return stmtToTypeMap;
}

void TypeToStmtNumTable::clear()
{
    stmtToTypeMap.clear();
    typeToStmtMap.clear();
    largestStmt = 0;
}
