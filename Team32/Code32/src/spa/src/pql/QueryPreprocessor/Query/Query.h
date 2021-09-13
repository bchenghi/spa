#ifndef GUARD_QUERY_H
#define GUARD_QUERY_H

#include <vector>
#include "QueryDesignEntity.h"
#include "Clause/FilterClause.h"
#include "Clause/SelectClause.h"

namespace pql {
    class Query {
    public:
        SelectClause* select;
        std::vector<QueryDesignEntity> designEntitiesVector;
        std::vector<FilterClause*> filterClauseVector;
        Query(SelectClause* select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause*> filterClauseVector);
        bool operator==(const Query& other) const;
    };
}

#endif //GUARD_QUERY_H
