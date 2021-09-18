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
        READ,
        STMT,
        VARIABLE,
        WHILE,
        NONE
    };
}


#endif //GUARD_DESIGN_ENTITY_H
