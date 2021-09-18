#ifndef GUARD_ASSIGNMENT_PATTERN_H
#define GUARD_ASSIGNMENT_PATTERN_H

#include "../FilterResult.h"
#include "PatternClause.h"
#include "pql/PkbAbstractor/PkbAbstractor.h"

#include <string>

namespace pql {
    class AssignmentPattern : public PatternClause {
    public:
        AssignmentPattern(QueryArg designEntityArg, QueryArg variableArg, std::vector<std::string> postFixStr);
        FilterResult executePKBAbsQuery(PkbAbstractor* pkbAbstractor);
    };
}

#endif //GUARD_ASSIGNMENT_PATTERN_H
