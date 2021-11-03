#ifndef GUARD_CALLS_STAR_CLAUSE_H
#define GUARD_CALLS_STAR_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class CallsStarClause : public SuchThatClause {
    public:
        CallsStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::CALLSSTAR;
        }
    protected:
        virtual bool argIsValid(QueryArg);
    };
}


#endif //GUARD_CALLS_STAR_CLAUSE_H
