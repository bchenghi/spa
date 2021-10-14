#ifndef GUARD_NEXT_STAR_CLAUSE_H
#define GUARD_NEXT_STAR_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class NextStarClause : public SuchThatClause {
    public:
        NextStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::NEXTSTAR;
        }
    };
}


#endif //GUARD_NEXT_STAR_CLAUSE_H
