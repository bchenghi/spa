#ifndef GUARD_ASSIGNMENT_PATTERN_H
#define GUARD_ASSIGNMENT_PATTERN_H

#include <string>
#include "PatternClause.h"
#include "../FilterResult.h"
#include "pql/PkbAbstractor/PkbAbstractor.h"

namespace pql {
    class AssignmentPattern : public PatternClause{
    public:
        AssignmentPattern(QueryArg designEntityArg, QueryArg variableArg, std::string postFixStr);
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor);
    };
}


#endif //GUARD_ASSIGNMENT_PATTERN_H
