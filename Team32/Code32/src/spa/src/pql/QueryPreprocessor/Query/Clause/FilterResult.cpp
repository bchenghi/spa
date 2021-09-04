#include "FilterResult.h"

using std::pair;

using pql::FilterResult;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

bool FilterResult::addResult(vector<pair<QueryDesignEntity, QueryArgValue>> result) {
    try {
        results.push_back(result);
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

int FilterResult::getSize() {
    return results.size();
}

vector<pair<QueryDesignEntity, QueryArgValue>> FilterResult::getEntitiesAndValuesAtIndex(int index) {
    return results.at(index);
}
