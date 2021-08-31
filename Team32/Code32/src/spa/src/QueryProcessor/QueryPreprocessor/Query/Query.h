#ifndef INC_21S1_CP_SPA_TEAM_32_QUERY_H
#define INC_21S1_CP_SPA_TEAM_32_QUERY_H

#include <vector>
#include "QueryDesignEntity.h"
#include "FilterClause/FilterClause.h"

class Query {
public:
    QueryDesignEntity select;
    std::vector<QueryDesignEntity> designEntitiesVector;
    std::vector<FilterClause> filterClauseVector;
    Query(QueryDesignEntity select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause> filterClauseVector);
};

#endif //INC_21S1_CP_SPA_TEAM_32_QUERY_H
