#include "Query.h"

Query::Query(QueryDesignEntity select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause> filterClauseVector)
: select(select), designEntitiesVector(designEntitiesVector), filterClauseVector(filterClauseVector){
}
