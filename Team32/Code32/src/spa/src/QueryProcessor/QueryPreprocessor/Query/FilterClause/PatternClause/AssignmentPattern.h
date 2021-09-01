#ifndef GUARD_ASSIGNMENT_PATTERN_H
#define GUARD_ASSIGNMENT_PATTERN_H

#include "PatternClause.h"
#include "../FilterResult.h"
#include "../../../../PkbAbstraction/PkbAbstractor.h"

namespace pql {
    class AssignmentPattern : public PatternClause{
    public:
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}


#endif //GUARD_ASSIGNMENT_PATTERN_H
