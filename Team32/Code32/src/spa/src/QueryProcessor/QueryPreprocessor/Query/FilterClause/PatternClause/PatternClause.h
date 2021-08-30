#ifndef INC_21S1_CP_SPA_TEAM_32_PATTERNCLAUSE_H
#define INC_21S1_CP_SPA_TEAM_32_PATTERNCLAUSE_H

#include <string>
#include "../FilterClause.h"
#include "../../QueryArg.h"

class PatternClause : public FilterClause {
    QueryArg designEntity;
    QueryArg variable;
    std::string subtreeString;
    bool operator== (const PatternClause & other) const {
        if (designEntity == other.designEntity && variable == other.variable && subtreeString == other.subtreeString) {
            return true;
        }
        return false;
    }
};
#endif //INC_21S1_CP_SPA_TEAM_32_PATTERNCLAUSE_H
