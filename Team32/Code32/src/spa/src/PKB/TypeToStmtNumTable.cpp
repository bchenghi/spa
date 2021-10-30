#include "TypeToStmtNumTable.h"

StmtNo TypeToStmtNumTable::largestStmt = 0;
TypeToStmtNumTable* TypeToStmtNumTable::typeTablePtr = nullptr;

bool TypeToStmtNumTable::addStmtWithType(pql::DesignEntity type, StmtNo stmt)
{
    if (stmt > TypeToStmtNumTable::largestStmt) {
        TypeToStmtNumTable::largestStmt = stmt;
    }

    return getInstance()->addOneToMany(TYPE_TO_STMT_MAP, pql::DesignEntity::STMT, stmt)
        && getInstance()->addOneToMany(TYPE_TO_STMT_MAP, type, stmt)
        && getInstance()->addOneToOneRev(STMT_TO_TYPE_MAP, stmt, type);
}

ListOfStmtNos TypeToStmtNumTable::getStmtWithType(pql::DesignEntity type)
{
    return getInstance()->getOneToMany(TYPE_TO_STMT_MAP, type);
}

pql::DesignEntity TypeToStmtNumTable::getTypeOfStmt(StmtNo stmt)
{
    return getInstance()->getOneToOneRev(STMT_TO_TYPE_MAP, stmt);
}

StmtNo TypeToStmtNumTable::getLargestStmt()
{
    return TypeToStmtNumTable::largestStmt;
}

const std::unordered_map<pql::DesignEntity, ListOfStmtNos> & TypeToStmtNumTable::getTypeToStmtMap()
{
    return getInstance()->getOneToManyMap(TYPE_TO_STMT_MAP);
}

const std::unordered_map<StmtNo, pql::DesignEntity> & TypeToStmtNumTable::getStmtToTypeMap()
{
    return getInstance()->getOneToOneRevMap(STMT_TO_TYPE_MAP);
}

void TypeToStmtNumTable::clear()
{
    getInstance()->clearAll();
    largestStmt = 0;
}
