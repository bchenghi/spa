#ifndef GUARD_AFFECTS_CLAUSE_H
#define GUARD_AFFECTS_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class AffectsClause : public SuchThatClause {
    public:
        AffectsClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::AFFECTS;
        }
    };
}


#endif //GUARD_AFFECTS_CLAUSE_H
