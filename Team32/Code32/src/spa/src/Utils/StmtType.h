//
// Created by geyul on 1/9/2021.
//

#ifndef AUTOTESTER_STMTTYPE_H
#define AUTOTESTER_STMTTYPE_H

namespace simple {
    enum class StmtType {
        assign,
        if_stmt,
        while_stmt,
        read_stmt,
        print_stmt,
        not_stmt,
        procedure_def
    };
}
#endif //AUTOTESTER_STMTTYPE_H
