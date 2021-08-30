#ifndef INC_21S1_CP_SPA_TEAM_32_QUERYDESIGNENTITY_H
#define INC_21S1_CP_SPA_TEAM_32_QUERYDESIGNENTITY_H

#include <string>
#include "../../DesignEntity.h"

class QueryDesignEntity {
public:
    DesignEntity designEntity;
    std::string variableName;
    QueryDesignEntity(DesignEntity designEntity, std::string variableName);
    bool operator==(const QueryDesignEntity & other) const;
};


#endif //INC_21S1_CP_SPA_TEAM_32_QUERYDESIGNENTITY_H
