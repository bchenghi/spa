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
        std::size_t operator()(const QueryDesignEntity& k) const;
        bool operator <( const QueryDesignEntity& k) const;
    };
}

namespace std
{
    template<> struct hash<pql::QueryDesignEntity> {
        std::size_t operator()(const pql::QueryDesignEntity& k) const {
            return ((std::hash<pql::DesignEntity>()(k.designEntity)
            ^ (std::hash<std::string>()(k.variableName) << 1)) >> 1);
        }
    };
}


#endif //GUARD_QUERY_DESIGN_ENTITY_H
