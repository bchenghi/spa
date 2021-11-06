#ifndef GUARD_DESIGN_ENTITY_H
#define GUARD_DESIGN_ENTITY_H

namespace pql {
    enum class DesignEntity {
        ASSIGN,
        CALL,
        CONSTANT,
        IF,
        PRINT,
        PROCEDURE,
        PROGRAM_LINE,
        READ,
        STMT,
        VARIABLE,
        WHILE,
        NONE
    };
}


#endif
