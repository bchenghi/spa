#ifndef GUARD_STMT_TYPE_H
#define GUARD_STMT_TYPE_H

namespace simple {
    enum class StmtType {
        ASSIGN,
        IF_STMT,
        WHILE_STMT,
        READ_STMT,
        PRINT_STMT,
        NOT_STMT,
        PROCEDURE_DEF,
        CALL_STMT
    };
}
#endif
