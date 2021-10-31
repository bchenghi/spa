#ifndef GUARD_NEXT_BIP_STAR_CLAUSE_H
#define GUARD_NEXT_BIP_STAR_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class NextBipStarClause : public SuchThatClause {
    public:
        NextBipStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::NEXTBIPSTAR;
        }
    };
}


#endif //GUARD_NEXT_BIP_STAR_CLAUSE_H
