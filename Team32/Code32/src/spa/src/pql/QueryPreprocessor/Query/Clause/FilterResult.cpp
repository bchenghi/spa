#include "FilterResult.h"
#include <iostream>
#include <utility>
using namespace std;
using std::pair;

using pql::FilterResult;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

FilterResult::FilterResult(vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results, bool hasMatch)
    : results(std::move(results)), hasMatch(hasMatch) { }

bool FilterResult::addResult(const vector<pair<QueryDesignEntity, QueryArgValue>>& result) {
    try {
        results.push_back(result);
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

size_t FilterResult::getSize() {
    return results.size();
}

vector<pair<QueryDesignEntity, QueryArgValue>> FilterResult::getEntitiesAndValuesAtIndex(int index) {
    return results.at(index);
}

void FilterResult::setHasMatch(bool hasMatch) {
    this->hasMatch = hasMatch;
}

bool FilterResult::getHasMatch() const {
    return hasMatch;
}

bool FilterResult::operator==(const FilterResult& other) const {
    return hasMatch == other.hasMatch && results == other.results;
}