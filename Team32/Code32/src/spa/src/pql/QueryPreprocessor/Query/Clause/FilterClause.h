#ifndef GUARD_FILTER_CLAUSE_H
#define GUARD_FILTER_CLAUSE_H

#include <vector>
#include "../QueryArg.h"
#include "../../../PkbAbstractor/PkbAbstractor.h"
#include "FilterResult.h"

namespace pql {
    class FilterClause {
    public:
        virtual FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
            return FilterResult({}, false);
        };
        virtual std::vector<QueryArg*> getQueryArgs() {
            std::vector<QueryArg*> v = {};
            return v;
        };
        virtual void setQueryArgs(std::vector<QueryArg> queryArgs) {};
        virtual void free() {};
    };
}

#endif //GUARD_FILTER_CLAUSE_H
