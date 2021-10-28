#include "TypeToStmtNumTable.h"

StmtNo TypeToStmtNumTable::largestStmt = 0;
TypeToStmtNumTable* TypeToStmtNumTable::type_table_ptr = nullptr;

bool TypeToStmtNumTable::addStmtWithType(pql::DesignEntity type, StmtNo stmt)
{
    if (stmt > TypeToStmtNumTable::largestStmt) {
        TypeToStmtNumTable::largestStmt = stmt;
    }

    return getInstance()->add_one_to_many(TYPE_TO_STMT_MAP, pql::DesignEntity::STMT, stmt)
        && getInstance()->add_one_to_many(TYPE_TO_STMT_MAP, type, stmt)
        && getInstance()->add_one_to_one_rev(STMT_TO_TYPE_MAP, stmt, type);
}

ListOfStmtNos TypeToStmtNumTable::getStmtWithType(pql::DesignEntity type)
{
    return getInstance()->get_one_to_many(TYPE_TO_STMT_MAP, type);
}

pql::DesignEntity TypeToStmtNumTable::getTypeOfStmt(StmtNo stmt)
{
    return getInstance()->get_one_to_one_rev(STMT_TO_TYPE_MAP, stmt);
}

StmtNo TypeToStmtNumTable::getLargestStmt()
{
    return TypeToStmtNumTable::largestStmt;
}

const std::unordered_map<pql::DesignEntity, ListOfStmtNos> & TypeToStmtNumTable::getTypeToStmtMap()
{
    return getInstance()->get_one_to_many_map(TYPE_TO_STMT_MAP);
}

const std::unordered_map<StmtNo, pql::DesignEntity> & TypeToStmtNumTable::getStmtToTypeMap()
{
    return getInstance()->get_one_to_one_rev_map(STMT_TO_TYPE_MAP);
}

void TypeToStmtNumTable::clear()
{
    getInstance()->clearAll();
    largestStmt = 0;
}
