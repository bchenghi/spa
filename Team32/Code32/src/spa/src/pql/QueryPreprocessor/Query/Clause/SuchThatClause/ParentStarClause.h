#ifndef GUARD_PARENT_STAR_CLAUSE_H
#define GUARD_PARENT_STAR_CLAUSE_H

#include "SuchThatClause.h"

namespace pql {
    class ParentStarClause : public SuchThatClause {
    public:
        ParentStarClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::PARENTSTAR;
        }
    protected:
        virtual bool argIsValid(QueryArg);
    };
}

#endif //GUARD_PARENT_STAR_CLAUSE_H
