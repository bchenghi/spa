#ifndef GUARD_USES_CLAUSE_H
#define GUARD_USES_CLAUSE_H

#include "SuchThatClause.h"

namespace pql {
    class UsesClause : public SuchThatClause {
    public:
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}


#endif //GUARD_USES_CLAUSE_H
