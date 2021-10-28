#ifndef GUARD_TYPE_TO_STMT_NUM_TABLE_H
#define GUARD_TYPE_TO_STMT_NUM_TABLE_H

#include "pql/DesignEntity.h"
#include "TypePreDefine.h"
#include "Table.h"

class TypeToStmtNumTable : Table<pql::DesignEntity, StmtNo> {
public:
    static TypeToStmtNumTable* getInstance() {
        if (type_table_ptr == nullptr) {
            type_table_ptr = new TypeToStmtNumTable;
        }
        return type_table_ptr;
    }
    static bool addStmtWithType(pql::DesignEntity type, StmtNo stmt);
    static ListOfStmtNos getStmtWithType(pql::DesignEntity type);
    static pql::DesignEntity getTypeOfStmt(StmtNo stmt);
    static StmtNo getLargestStmt();
    static const std::unordered_map<pql::DesignEntity, ListOfStmtNos>& getTypeToStmtMap();
    static const std::unordered_map<StmtNo, pql::DesignEntity>& getStmtToTypeMap();
    static void clear();

private:
    //static std::unordered_map<pql::DesignEntity, ListOfStmtNos> typeToStmtMap;
    //static std::unordered_map<StmtNo, pql::DesignEntity> stmtToTypeMap;

    static TypeToStmtNumTable* type_table_ptr;
    static const size_t TYPE_TO_STMT_MAP = 1;
    static const size_t STMT_TO_TYPE_MAP = 3;

    static StmtNo largestStmt;

    TypeToStmtNumTable() {
        one_to_many_map[TYPE_TO_STMT_MAP] = std::unordered_map<pql::DesignEntity, ListOfStmtNos>();
        one_to_one_rev_map[STMT_TO_TYPE_MAP] = std::unordered_map<StmtNo, pql::DesignEntity>();
    }
};

#endif //GUARD_TYPE_TO_STMT_NUM_TABLE_H
