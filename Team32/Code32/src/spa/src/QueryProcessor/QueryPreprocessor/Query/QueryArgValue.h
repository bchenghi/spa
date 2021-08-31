#ifndef INC_21S1_CP_SPA_TEAM_32_QUERYARGVALUE_H
#define INC_21S1_CP_SPA_TEAM_32_QUERYARGVALUE_H

#include <string>
#include "../../DesignEntity.h"

class QueryArgValue {
public:
    DesignEntity designEntity;
    std::string value;
    QueryArgValue(DesignEntity designEntity, std::string value);
    bool operator== (const QueryArgValue & other) const;
};


#endif //INC_21S1_CP_SPA_TEAM_32_QUERYARGVALUE_H
