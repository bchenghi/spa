#ifndef INC_21S1_CP_SPA_TEAM_32_PARENTCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_PARENTCLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

class ParentClause : public SuchThatClause {
public:
    FilterResult* executePKBAbsQuery(PkbAbstractor pkbAbstractor);
};


#endif //INC_21S1_CP_SPA_TEAM_32_PARENTCLAUSE_H
