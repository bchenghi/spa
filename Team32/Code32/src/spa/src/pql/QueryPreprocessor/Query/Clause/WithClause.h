#ifndef GUARD_WITH_CLAUSE_H
#define GUARD_WITH_CLAUSE_H

#include "FilterResult.h"
#include "FilterClause.h"

namespace pql {
    class WithClause : FilterClause {
    public:
        QueryArg firstArg;
        QueryArg secondArg;
        bool operator==(const WithClause& other) const {
            if (firstArg == other.firstArg && secondArg == other.secondArg) {
                return true;
            }
            return false;
        }
        std::vector<QueryArg*> getQueryArgs() {
            std::vector<QueryArg*> result;
            result.push_back(&firstArg);
            result.push_back(&secondArg);
            return result;
        }
        WithClause(QueryArg firstArg, QueryArg secondArg);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::WITH;
        }
    };
}


#endif //GUARD_WITH_CLAUSE_H