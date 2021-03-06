#ifndef GUARD_FOLLOWS_STAR_CLAUSE_H
#define GUARD_FOLLOWS_STAR_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class FollowsStarClause : public SuchThatClause {
    public:
        FollowsStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::FOLLOWSSTAR;
        }
    protected:
        virtual bool argIsValid(QueryArg);
    };
}

#endif
