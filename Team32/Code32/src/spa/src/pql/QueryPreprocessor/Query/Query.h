#ifndef GUARD_QUERY_H
#define GUARD_QUERY_H

#include <vector>
#include "QueryDesignEntity.h"
#include "FilterClause/FilterClause.h"

namespace pql {
    class Query {
    public:
        QueryDesignEntity select;
        std::vector<QueryDesignEntity> designEntitiesVector;
        std::vector<FilterClause*> filterClauseVector;
        Query(QueryDesignEntity select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause*> filterClauseVector);
    };
}

#endif //GUARD_QUERY_H
