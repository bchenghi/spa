#ifndef GUARD_QUERY_ARG_H
#define GUARD_QUERY_ARG_H

#include "QueryArgValue.h"
#include "QueryDesignEntity.h"

namespace pql {
    class QueryArg {
    public:
        QueryDesignEntity* queryDesignEntity;
        QueryArgValue* argValue;
        bool isWildCard;
        QueryArg(QueryDesignEntity* queryDesignEntity, QueryArgValue* argValue, bool isWildCard);
        bool operator==(const QueryArg& other) const;
    };
}


#endif //GUARD_QUERY_ARG_H
