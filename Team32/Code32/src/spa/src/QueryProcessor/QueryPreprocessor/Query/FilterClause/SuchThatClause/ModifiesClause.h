#ifndef INC_21S1_CP_SPA_TEAM_32_MODIFIESCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_MODIFIESCLAUSE_H

#include "../FilterResult.h"
#include "SuchThatClause.h"

class ModifiesClause : public SuchThatClause {
public:
    FilterResult* executePKBAbsQuery(PkbAbstractor pkbAbstractor);
};


#endif //INC_21S1_CP_SPA_TEAM_32_MODIFIESCLAUSE_H
