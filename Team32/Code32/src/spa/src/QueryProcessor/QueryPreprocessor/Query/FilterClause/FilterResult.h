#ifndef INC_21S1_CP_SPA_TEAM_32_FILTERRESULT_H
#define INC_21S1_CP_SPA_TEAM_32_FILTERRESULT_H

#include <vector>
#include <utility>
#include "../QueryArgValue.h"
#include "../QueryDesignEntity.h"

class FilterResult {
private:
    std::vector<std::pair<QueryDesignEntity, QueryArgValue>> results;

public:
    bool addResult(QueryDesignEntity queryDesignEntity, QueryArgValue value);
    int getSize();
    std::pair<QueryDesignEntity, QueryArgValue> getEntityValueAtIndex(int index);
};


#endif //INC_21S1_CP_SPA_TEAM_32_FILTERRESULT_H
