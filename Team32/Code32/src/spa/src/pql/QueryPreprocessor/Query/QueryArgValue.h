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
    };
}


#endif //GUARD_QUERY_ARG_VALUE_H
