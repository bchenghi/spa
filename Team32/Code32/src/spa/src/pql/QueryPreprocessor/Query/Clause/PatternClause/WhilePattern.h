#ifndef GUARD_WHILE_PATTERN_H
#define GUARD_WHILE_PATTERN_H

#include "PatternClause.h"

namespace pql {
    class WhilePattern : public PatternClause {
    public:
        WhilePattern(QueryArg designEntityArg, QueryArg variableArg);
        FilterResult executePKBAbsQuery(PkbAbstractor* pkbAbstractor);
        virtual ClauseType getClauseType() {
            return ClauseType::WHILEPATTERN;
        }
    };
}

#endif
