#ifndef GUARD_ASSIGNMENT_PATTERN_H
#define GUARD_ASSIGNMENT_PATTERN_H

#include "../FilterResult.h"
#include "PatternClause.h"
#include "pql/PkbAbstractor/PkbAbstractor.h"

#include <string>

namespace pql {
    class AssignmentPattern : public PatternClause {
    public:
        std::vector<std::string> postFixStr;
        bool hasUnderscores;
        AssignmentPattern(QueryArg designEntityArg, QueryArg variableArg, std::vector<std::string> postFixStr, bool hasUnderscores);
        FilterResult executePKBAbsQuery(PkbAbstractor* pkbAbstractor);
        bool operator==(const AssignmentPattern& other) const {
            if (designEntityArg == other.designEntityArg &&
                variableArg == other.variableArg &&
                postFixStr == other.postFixStr &&
                hasUnderscores == other.hasUnderscores) {
                return true;
            }
            return false;
        }
        virtual ClauseType getClauseType() {
            return ClauseType::ASSIGNMENTPATTERN;
        }
    };
}

#endif
