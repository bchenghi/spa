#ifndef GUARD_FOLLOWS_CLAUSE_H
#define GUARD_FOLLOWS_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class FollowsClause : public SuchThatClause {
    public:
        FollowsClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}

#endif //GUARD_FOLLOWS_CLAUSE_H
