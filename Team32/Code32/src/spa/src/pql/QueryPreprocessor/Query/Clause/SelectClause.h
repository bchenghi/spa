#ifndef GUARD_SELECT_CLAUSE_H
#define GUARD_SELECT_CLAUSE_H

#include <utility>
#include <vector>
#include <utility>
#include "../QueryDesignEntity.h"
#include "../QueryArgValue.h"
#include "../../../PkbAbstractor/PkbAbstractor.h"

using std::pair;
using std::vector;

namespace pql {
    class SelectClause {
    public:
        vector<QueryDesignEntity> queryDesignEntities;
        SelectClause(vector<QueryDesignEntity> queryDesignEntities) : queryDesignEntities(std::move(queryDesignEntities)) {}
        bool operator==(const SelectClause& other) const;
    };
}


#endif //GUARD_SELECT_CLAUSE_H
