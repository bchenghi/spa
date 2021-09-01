#ifndef GUARD_PATTERN_CLAUSE_H
#define GUARD_PATTERN_CLAUSE_H

#include <string>
#include "../FilterClause.h"
#include "../../QueryArg.h"

namespace pql {
    class PatternClause : public FilterClause {
        QueryArg designEntity;
        QueryArg variable;
        std::string subtreeString;
        bool operator==(const PatternClause& other) const {
            if (designEntity == other.designEntity && variable == other.variable && subtreeString == other.subtreeString) {
                return true;
            }
            return false;
        }
    };
}
#endif //GUARD_PATTERN_CLAUSE_H
