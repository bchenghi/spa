//
// Created by Cheng Hin on 30/8/2021.
//

#ifndef INC_21S1_CP_SPA_TEAM_32_PARENTSTARCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_PARENTSTARCLAUSE_H

#include "SuchThatClause.h"

class ParentStarClause : public SuchThatClause {
public:
    FilterResult* executePKBAbsQuery(PkbAbstractor pkbAbstractor);
};


#endif //INC_21S1_CP_SPA_TEAM_32_PARENTSTARCLAUSE_H
