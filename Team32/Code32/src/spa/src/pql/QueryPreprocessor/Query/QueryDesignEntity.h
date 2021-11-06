#ifndef GUARD_QUERY_DESIGN_ENTITY_H
#define GUARD_QUERY_DESIGN_ENTITY_H

#include <string>
#include "../../DesignEntity.h"
#include "../../AttributeType.h"
#include "pql/Errors/SemanticError.h"

namespace pql {
    class QueryDesignEntity {
    public:
        QueryDesignEntity();
        QueryDesignEntity(DesignEntity designEntity, std::string variableName, AttributeType attributeType = AttributeType::NONE);
        bool operator==(const QueryDesignEntity& other) const;
        bool operator!=(const QueryDesignEntity& other) const;
        std::size_t operator()(const QueryDesignEntity& k) const;
        bool operator <( const QueryDesignEntity& k) const;
        DesignEntity getDesignEntity() const;
        std::string getVariableName() const;
        AttributeType getAttributeType() const;

    private:
        DesignEntity designEntity;
        std::string variableName;
        AttributeType attributeType;
    };
}

namespace std
{
    template<> struct hash<pql::QueryDesignEntity> {
        std::size_t operator()(const pql::QueryDesignEntity& k) const {
            return ((std::hash<pql::DesignEntity>()(k.getDesignEntity())
            ^ (std::hash<std::string>()(k.getVariableName()) << 1)) >> 1);
        }
    };
}


#endif
