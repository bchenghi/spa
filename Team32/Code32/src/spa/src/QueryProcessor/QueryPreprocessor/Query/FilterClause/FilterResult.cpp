#include "FilterResult.h"
bool FilterResult::addResult(QueryDesignEntity queryDesignEntity, QueryArgValue value) {
    try {
        results.push_back(std::make_pair(queryDesignEntity, value));
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

int FilterResult::getSize() {
    return results.size();
}

std::pair<QueryDesignEntity, QueryArgValue> FilterResult::getEntityValueAtIndex(int index) {
    return results.at(index);
}
