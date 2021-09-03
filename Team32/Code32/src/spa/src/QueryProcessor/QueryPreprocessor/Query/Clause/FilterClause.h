#ifndef GUARD_FILTER_CLAUSE_H
#define GUARD_FILTER_CLAUSE_H

#include <vector>
#include "../QueryArg.h"
#include "../../../PkbAbstraction/PkbAbstractor.h"
#include "FilterResult.h"

namespace pql {
    class FilterClause {
    public:
        virtual FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor) {
            return FilterResult();
        };
        virtual std::vector<QueryArg> getQueryArgs();
        virtual void setQueryArgs(std::vector<QueryArg> queryArgs);
    };
}

#endif //GUARD_FILTER_CLAUSE_H
