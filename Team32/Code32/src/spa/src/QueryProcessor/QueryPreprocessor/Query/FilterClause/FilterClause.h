#ifndef INC_21S1_CP_SPA_TEAM_32_FILTERCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_FILTERCLAUSE_H

#include <vector>
#include "FilterResult.h"
#include "../../../PkbAbstraction/PkbAbstractor.h"

class FilterClause {
public:
    virtual FilterResult* executePKBAbsQuery(PkbAbstractor pkbAbstractor) {
        return new FilterResult();
    };
};


#endif //INC_21S1_CP_SPA_TEAM_32_FILTERCLAUSE_H
