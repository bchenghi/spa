#ifndef GUARD_NEXT_BIP_CLAUSE_H
#define GUARD_NEXT_BIP_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class NextBipClause : public SuchThatClause {
    public:
        NextBipClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::NEXTBIP;
        }
    };
}


#endif //GUARD_NEXT_BIP_CLAUSE_H
