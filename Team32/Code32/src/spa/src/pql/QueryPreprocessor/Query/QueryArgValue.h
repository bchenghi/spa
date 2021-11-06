#ifndef GUARD_QUERY_ARG_VALUE_H
#define GUARD_QUERY_ARG_VALUE_H

#include <string>
#include "../../DesignEntity.h"

namespace pql {
    class QueryArgValue {
    public:
        QueryArgValue(DesignEntity designEntity, std::string value);
        bool operator==(const QueryArgValue& other) const;
        std::size_t operator()(const QueryArgValue& k) const;
        bool operator <( const QueryArgValue& k) const;
        DesignEntity getDesignEntity() const;
        std::string getValue() const;
        void setDesignEntity(DesignEntity);

    private:
        DesignEntity designEntity;
        std::string value;
    };
}

namespace std
{
    template<> struct hash<pql::QueryArgValue> {
        std::size_t operator()(const pql::QueryArgValue& k) const {
            return ((std::hash<pql::DesignEntity>()(k.getDesignEntity())
            ^ (std::hash<std::string>()(k.getValue()) << 2)) >> 2);
        }
    };
}
#endif
