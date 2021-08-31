#ifndef INC_21S1_CP_SPA_TEAM_32_QUERYARG_H
#define INC_21S1_CP_SPA_TEAM_32_QUERYARG_H

#include "QueryArgValue.h"
#include "QueryDesignEntity.h"

class QueryArg {
public:
    QueryDesignEntity queryDesignEntity;
    QueryArgValue argValue;
    bool isWildCard;
    QueryArg(QueryDesignEntity queryDesignEntity, QueryArgValue argValue, bool isWildCard);
    bool operator==(const QueryArg & other) const;
};


#endif //INC_21S1_CP_SPA_TEAM_32_QUERYARG_H
