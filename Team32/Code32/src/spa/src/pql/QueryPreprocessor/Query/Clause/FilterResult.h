#ifndef GUARD_FILTER_RESULT_H
#define GUARD_FILTER_RESULT_H

#include <vector>
#include <unordered_map>
#include <utility>
#include "../QueryArgValue.h"
#include "../QueryDesignEntity.h"

using std::vector;
using std::pair;
using std::unordered_map;

namespace pql {
    class FilterResult {
    private:
        bool hasMatch;
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results;

    public:
        FilterResult(vector<vector<pair<QueryDesignEntity, QueryArgValue>>>, bool);
        bool addResult(const vector<pair<QueryDesignEntity, QueryArgValue>>& result);
        size_t getSize();
        vector<pair<QueryDesignEntity, QueryArgValue>> getEntitiesAndValuesAtIndex(int index);
        void setHasMatch(bool);
        bool getHasMatch() const;
        bool operator==(const FilterResult& other) const;
    };
}

#endif
