#include "QueryArg.h"

using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

QueryArg::QueryArg(QueryDesignEntity* queryDesignEntity, QueryArgValue* argValue, bool isWildCard)
: queryDesignEntity(queryDesignEntity), argValue(argValue), isWildCard(isWildCard) {
}

bool QueryArg::operator==(const QueryArg& other) const {
    // Both wildcards
    if (queryDesignEntity == nullptr && other.getQueryDesignEntity() == nullptr &&
    argValue == nullptr && other.getQueryArgValue() == nullptr &&
    isWildCard == other.isWildCardArg()) {
        return true;
    }

    // Same design entity and value
    if ((queryDesignEntity != nullptr && other.getQueryDesignEntity() != nullptr &&
    *queryDesignEntity == *(other.getQueryDesignEntity())) && (argValue != nullptr && other.getQueryArgValue()!= nullptr &&
    *argValue == *(other.getQueryArgValue()))) {
        return true;
    }

    // Same design entity
    if (queryDesignEntity != nullptr && other.getQueryDesignEntity() != nullptr &&
    argValue == nullptr && other.getQueryArgValue()== nullptr &&
    *queryDesignEntity == *(other.getQueryDesignEntity())) {
        return true;
    }

    // Same value
    if (queryDesignEntity == nullptr && other.getQueryDesignEntity() == nullptr &&
    argValue != nullptr && other.getQueryArgValue()!= nullptr &&
    *argValue == *(other.getQueryArgValue())) {
        return true;
    }

    return false;
}

void QueryArg::free() {
    if (queryDesignEntity != nullptr) {
        delete queryDesignEntity;
    }
    if (argValue != nullptr) {
        delete argValue;
    }
}

QueryDesignEntity* QueryArg::getQueryDesignEntity() const {
    return queryDesignEntity;
}

QueryArgValue* QueryArg::getQueryArgValue() const  {
    return argValue;
}

bool QueryArg::isWildCardArg() const {
    return isWildCard;
}

void QueryArg::setQueryArgValue(QueryArgValue* newArgValue) {
    argValue = newArgValue;
}
