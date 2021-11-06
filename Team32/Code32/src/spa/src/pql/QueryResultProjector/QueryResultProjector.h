#ifndef GUARD_QUERY_RESULT_PROJECTOR_H
#define GUARD_QUERY_RESULT_PROJECTOR_H

#include <vector>
#include <string>
#include "pql/QueryResult.h"

using pql::QueryResult;

namespace pql{
    class QueryResultProjector {
    public:
        set<string> createResultSet(QueryResult queryResult);
    };
}


#endif
