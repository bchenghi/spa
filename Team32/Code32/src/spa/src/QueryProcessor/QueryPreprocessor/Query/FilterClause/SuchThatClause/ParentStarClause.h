#ifndef GUARD_PARENT_STAR_CLAUSE_H
#define GUARD_PARENT_STAR_CLAUSE_H

#include "SuchThatClause.h"

namespace pql {
    class ParentStarClause : public SuchThatClause {
    public:
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}


#endif //GUARD_PARENT_STAR_CLAUSE_H
