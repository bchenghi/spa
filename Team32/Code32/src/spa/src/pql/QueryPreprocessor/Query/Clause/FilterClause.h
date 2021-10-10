#ifndef GUARD_FILTER_CLAUSE_H
#define GUARD_FILTER_CLAUSE_H

#include <vector>
#include "ClauseType.h"
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
        virtual ClauseType getClauseType() {
            return ClauseType::NONE;
        }
        virtual void setQueryArgs(std::vector<QueryArg> queryArgs) {};

        // If the argument is a synonym, should return their valid values in executePKBAbsQuery.
        // Set to true in constructors.
        bool shldReturnFirst = false;
        bool shldReturnSecond = false;

        virtual void free() {};
    };
}

#endif //GUARD_FILTER_CLAUSE_H
