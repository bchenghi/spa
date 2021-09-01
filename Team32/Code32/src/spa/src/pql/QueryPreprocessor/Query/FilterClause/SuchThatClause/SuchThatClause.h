#ifndef GUARD_SUCH_THAT_CLAUSE
#define GUARD_SUCH_THAT_CLAUSE

#include "../FilterClause.h"
#include "../../QueryArg.h"

namespace pql {
    class SuchThatClause : public FilterClause {
    public:
        QueryArg firstArg;
        QueryArg secondArg;
        bool operator==(const SuchThatClause& other) const {
            if (firstArg == other.firstArg && secondArg == other.secondArg) {
                return true;
            }
            return false;
        }
    };
}

#endif //GUARD_SUCH_THAT_CLAUSE
