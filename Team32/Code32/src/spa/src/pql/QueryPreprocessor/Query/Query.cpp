#include "Query.h"

using pql::FilterClause;
using pql::Query;
using pql::QueryDesignEntity;
using pql::SelectClause;

Query::Query(SelectClause* select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause*> filterClauseVector)
: select(select), designEntitiesVector(designEntitiesVector), filterClauseVector(filterClauseVector){
}
