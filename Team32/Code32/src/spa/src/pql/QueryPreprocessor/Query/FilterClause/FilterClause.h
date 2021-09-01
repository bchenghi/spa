#ifndef GUARD_FILTER_CLAUSE_H
#define GUARD_FILTER_CLAUSE_H

#include <vector>
#include "../../../PkbAbstraction/PkbAbstractor.h"
#include "FilterResult.h"

namespace pql {
    class FilterClause {
    public:
        virtual FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor) {
            return FilterResult();
        };
    };
}

#endif //GUARD_FILTER_CLAUSE_H
