#ifndef GUARD_NEXT_CLAUSE_H
#define GUARD_NEXT_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class NextClause : public SuchThatClause {
    public:
        NextClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::NEXT;
        }
    protected:
        virtual bool argIsValid(QueryArg);
    };
}


#endif //GUARD_NEXT_CLAUSE_H
