#include "QueryArg.h"

QueryArg::QueryArg(QueryDesignEntity queryDesignEntity, QueryArgValue argValue, bool isWildCard)
: queryDesignEntity(queryDesignEntity), argValue(argValue), isWildCard(isWildCard) {
}

bool QueryArg::operator==(const QueryArg &other) const {
    if (queryDesignEntity == other.queryDesignEntity && argValue == other.argValue && isWildCard == other.isWildCard) {
        return true;
    }
    return false;
}