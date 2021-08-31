#ifndef INC_21S1_CP_SPA_TEAM_32_USESCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_USESCLAUSE_H

#include "SuchThatClause.h"

class UsesClause : public SuchThatClause {
public:
    FilterResult* executePKBAbsQuery(PkbAbstractor pkbAbstractor);
};


#endif //INC_21S1_CP_SPA_TEAM_32_USESCLAUSE_H
