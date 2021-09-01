#include "Query.h"

using pql::FilterClause;
using pql::Query;
using pql::QueryDesignEntity;

Query::Query(QueryDesignEntity select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause*> filterClauseVector)
: select(select), designEntitiesVector(designEntitiesVector), filterClauseVector(filterClauseVector){
}
