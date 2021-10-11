#ifndef GUARD_CALLS_CLAUSE_H
#define GUARD_CALLS_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class CallsClause : public SuchThatClause {
    public:
        CallsClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::CALLS;
        }
    };
}


#endif //GUARD_CALLS_CLAUSE_H
