#ifndef GUARD_QUERY_ARG_VALUE_H
#define GUARD_QUERY_ARG_VALUE_H

#include <string>
#include "../../DesignEntity.h"

namespace pql {
    class QueryArgValue {
    public:
        DesignEntity designEntity;
        std::string value;
        QueryArgValue(DesignEntity designEntity, std::string value);
        bool operator==(const QueryArgValue& other) const;
        std::size_t operator()(const QueryArgValue& k) const;
        bool operator <( const QueryArgValue& k) const;
    };
}

namespace std
{
    template<> struct hash<pql::QueryArgValue> {
        std::size_t operator()(const pql::QueryArgValue& k) const {
            return ((std::hash<pql::DesignEntity>()(k.designEntity)
            ^ (std::hash<std::string>()(k.value) << 2)) >> 2);
        }
    };
}
#endif //GUARD_QUERY_ARG_VALUE_H
