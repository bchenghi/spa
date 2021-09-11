#include "FilterResult.h"

using std::pair;

using pql::FilterResult;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

FilterResult::FilterResult(vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results, bool hasMatch) : results(results), hasMatch(hasMatch) {

}

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

void FilterResult::setHasMatch(bool hasMatch) {
    this->hasMatch = hasMatch;
}

bool FilterResult::getHasMatch() {
    return hasMatch;
}
