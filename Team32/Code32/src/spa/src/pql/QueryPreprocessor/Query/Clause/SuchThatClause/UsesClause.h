#ifndef GUARD_USES_CLAUSE_H
#define GUARD_USES_CLAUSE_H

#include "SuchThatClause.h"

namespace pql {
    class UsesClause : public SuchThatClause {
    public:
        UsesClause(QueryArg queryArg, QueryArg queryArg1);
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}

#endif //GUARD_USES_CLAUSE_H
