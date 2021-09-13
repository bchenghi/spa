#ifndef GUARD_MODIFIES_CLAUSE_H
#define GUARD_MODIFIES_CLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

namespace pql {
    class ModifiesClause : public SuchThatClause {
    public:
        ModifiesClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
    };
}


#endif //GUARD_MODIFIES_CLAUSE_H
