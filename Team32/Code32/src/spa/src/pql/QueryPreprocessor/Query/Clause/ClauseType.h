#ifndef GUARD_CLAUSE_TYPE_H
#define GUARD_CLAUSE_TYPE_H

namespace pql {
    enum class ClauseType {
        PARENT,
        PARENTSTAR,
        FOLLOWS,
        FOLLOWSSTAR,
        USES,
        MODIFIES,
        CALLS,
        CALLSSTAR,
        NEXT,
        NEXTSTAR,
        NEXTBIP,
        NEXTBIPSTAR,
        AFFECTS,
        AFFECTSSTAR,
        AFFECTSBIP,
        AFFECTSBIPSTAR,
        ASSIGNMENTPATTERN,
        IFPATTERN,
        WHILEPATTERN,
        WITH,
        NONE
    };
}


#endif //GUARD_CLAUSE_TYPE_H
