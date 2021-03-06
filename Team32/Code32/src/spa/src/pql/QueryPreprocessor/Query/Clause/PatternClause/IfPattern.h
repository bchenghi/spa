#ifndef GUARD_IF_PATTERN_H
#define GUARD_IF_PATTERN_H

#include "PatternClause.h"

namespace pql {
    class IfPattern : public PatternClause {
    public:
        IfPattern(QueryArg designEntityArg, QueryArg variableArg);
        FilterResult executePKBAbsQuery(PkbAbstractor* pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::IFPATTERN;
        }
    };
}

#endif
