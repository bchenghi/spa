#ifndef GUARD_AFFECTS_BIP_STAR_CLAUSE_H
#define GUARD_AFFECTS_BIP_STAR_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class AffectsBipStarClause : public SuchThatClause {
    public:
        AffectsBipStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::AFFECTSBIPSTAR;
        }
    };
}


#endif //GUARD_AFFECTS_BIP_STAR_CLAUSE_H
