#ifndef INC_21S1_CP_SPA_TEAM_32_FOLLOWSSTARCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_FOLLOWSSTARCLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

class FollowsStarClause : public SuchThatClause {
public:
    FilterResult* executePKBAbsQuery(PkbAbstractor pkbAbstractor);
};


#endif //INC_21S1_CP_SPA_TEAM_32_FOLLOWSSTARCLAUSE_H
