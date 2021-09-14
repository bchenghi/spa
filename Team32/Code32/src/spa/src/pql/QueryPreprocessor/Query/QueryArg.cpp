#include "QueryArg.h"

using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

QueryArg::QueryArg(QueryDesignEntity* queryDesignEntity, QueryArgValue* argValue, bool isWildCard)
: queryDesignEntity(queryDesignEntity), argValue(argValue), isWildCard(isWildCard) {
}

bool QueryArg::operator==(const QueryArg& other) const {
    // Both wildcards
    if (queryDesignEntity == nullptr && other.queryDesignEntity == nullptr &&
    argValue == nullptr && other.argValue == nullptr &&
    isWildCard == other.isWildCard) {
        return true;
    }

    // Same design entity and value
    if ((queryDesignEntity != nullptr && other.queryDesignEntity != nullptr &&
    *queryDesignEntity == *(other.queryDesignEntity)) && (argValue != nullptr && other.argValue!= nullptr &&
    *argValue == *(other.argValue))) {
        return true;
    }

    // Same design entity
    if (queryDesignEntity != nullptr && other.queryDesignEntity != nullptr &&
    argValue == nullptr && other.argValue== nullptr &&
    *queryDesignEntity == *(other.queryDesignEntity)) {
        return true;
    }

    // Same value
    if (queryDesignEntity == nullptr && other.queryDesignEntity == nullptr &&
    argValue != nullptr && other.argValue!= nullptr &&
    *argValue == *(other.argValue)) {
        return true;
    }

    return false;
}
