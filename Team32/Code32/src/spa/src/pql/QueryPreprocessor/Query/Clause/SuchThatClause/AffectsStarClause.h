#ifndef GUARD_AFFECTS_STAR_CLAUSE_H
#define GUARD_AFFECTS_STAR_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class AffectsStarClause : public SuchThatClause {
    public:
        AffectsStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::AFFECTSSTAR;
        }
    };
}


#endif //GUARD_AFFECTS_STAR_CLAUSE_H
