#ifndef GUARD_DESIGN_ENTITY_H
#define GUARD_DESIGN_ENTITY_H

namespace pql {
    enum class DesignEntity {
        Assign,
        Call,
        Constant,
        If,
        Print,
        Procedure,
        Read,
        Stmt,
        Variable,
        While,
        None
    };
}


#endif //GUARD_DESIGN_ENTITY_H
