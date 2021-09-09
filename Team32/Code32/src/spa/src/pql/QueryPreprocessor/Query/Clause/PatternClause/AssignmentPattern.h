#ifndef GUARD_ASSIGNMENT_PATTERN_H
#define GUARD_ASSIGNMENT_PATTERN_H

#include <string>
#include "PatternClause.h"
#include "../FilterResult.h"
#include "../../../../PkbAbstractor/PkbAbstractor.h"

namespace pql {
    class AssignmentPattern : public PatternClause{
    public:
        AssignmentPattern(QueryArg queryDesignEntity, QueryArg variable, std::string subtreeStr);
        FilterResult executePKBAbsQuery(PkbAbstractor pkbAbstractor);
    };
}


#endif //GUARD_ASSIGNMENT_PATTERN_H
