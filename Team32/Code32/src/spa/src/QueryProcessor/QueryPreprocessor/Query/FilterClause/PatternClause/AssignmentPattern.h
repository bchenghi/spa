#ifndef INC_21S1_CP_SPA_TEAM_32_ASSIGNMENTPATTERN_H
#define INC_21S1_CP_SPA_TEAM_32_ASSIGNMENTPATTERN_H

#include "PatternClause.h"
#include "../FilterResult.h"

class AssignmentPattern : public PatternClause{
public:
    FilterResult* executePKBAbsQuery(PkbAbstractor pkbAbstractor);
};


#endif //INC_21S1_CP_SPA_TEAM_32_ASSIGNMENTPATTERN_H
