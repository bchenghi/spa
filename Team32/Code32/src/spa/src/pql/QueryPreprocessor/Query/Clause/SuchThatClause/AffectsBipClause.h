#ifndef GUARD_AFFECTS_BIP_CLAUSE_H
#define GUARD_AFFECTS_BIP_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class AffectsBipClause : public SuchThatClause {
    public:
        AffectsBipClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::AFFECTSBIP;
        }
    protected:
        virtual bool argIsValid(QueryArg);
    };
}


#endif
