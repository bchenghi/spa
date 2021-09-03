#ifndef GUARD_FOLLOWS_CLAUSE_H
#define GUARD_FOLLOWS_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class FollowsClause : public SuchThatClause {
    public:
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}

#endif //GUARD_FOLLOWS_CLAUSE_H
