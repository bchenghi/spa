#ifndef GUARD_PARENT_CLAUSE_H
#define GUARD_PARENT_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class ParentClause : public SuchThatClause {
    public:
        ParentClause(QueryArg queryArg, QueryArg queryArg1);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::PARENT;
        }
    protected:
        virtual bool argIsValid(QueryArg);
    };
}

#endif //GUARD_PARENT_CLAUSE_H
