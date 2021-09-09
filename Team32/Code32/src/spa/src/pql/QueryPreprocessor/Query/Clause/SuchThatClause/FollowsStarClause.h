#ifndef GUARD_FOLLOWS_STAR_CLAUSE_H
#define GUARD_FOLLOWS_STAR_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class FollowsStarClause : public SuchThatClause {
    public:
        FollowsStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}

#endif //GUARD_FOLLOWS_STAR_CLAUSE_H
