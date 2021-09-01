#ifndef GUARD_QUERY_DESIGN_ENTITY_H
#define GUARD_QUERY_DESIGN_ENTITY_H

#include <string>
#include "../../DesignEntity.h"

namespace pql {
    class QueryDesignEntity {
    public:
        DesignEntity designEntity;
        std::string variableName;
        QueryDesignEntity(DesignEntity designEntity, std::string variableName);
        bool operator==(const QueryDesignEntity& other) const;
    };
}


#endif //GUARD_QUERY_DESIGN_ENTITY_H
