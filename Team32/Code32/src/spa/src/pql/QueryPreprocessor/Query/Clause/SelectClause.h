#ifndef GUARD_SELECT_CLAUSE_H
#define GUARD_SELECT_CLAUSE_H

#include <vector>
#include <utility>
#include "../QueryDesignEntity.h"
#include "../QueryArgValue.h"

using std::pair;
using std::vector;

namespace pql {
    class SelectClause {
    public:
        QueryDesignEntity queryDesignEntity;
        SelectClause(QueryDesignEntity queryDesignEntity) : queryDesignEntity(queryDesignEntity) {}
        virtual vector<vector<pair<QueryDesignEntity, QueryArgValue>>> getAllEntityCombinations();
    };
}


#endif //GUARD_SELECT_CLAUSE_H
