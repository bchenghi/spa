#ifndef INC_21S1_CP_SPA_TEAM_32_SUCHTHATCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_SUCHTHATCLAUSE_H

#include "../FilterClause.h"
#include "../../QueryArg.h"

class SuchThatClause : public FilterClause {
public:
    QueryArg firstArg;
    QueryArg secondArg;
    bool operator== (const SuchThatClause & other) const {
        if (firstArg == other.firstArg && secondArg == other.secondArg) {
            return true;
        }
        return false;
    }
};

#endif //INC_21S1_CP_SPA_TEAM_32_SUCHTHATCLAUSE_H
