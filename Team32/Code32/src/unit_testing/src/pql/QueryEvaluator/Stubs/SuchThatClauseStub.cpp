#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/SuchThatClause.h"

using std::vector;
using std::pair;
using pql::SuchThatClause;
using pql::QueryDesignEntity;
using pql::DesignEntity;
using pql::FilterResult;
using pql::PkbAbstractor;
using pql::QueryArgValue;
using pql::QueryArg;

namespace qetest {
    class SuchThatClauseStub : public SuchThatClause {
    private:
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> db;
        FilterResult f = FilterResult({}, false);
    public:
        SuchThatClauseStub(QueryArg firstArg, QueryArg secondArg) : SuchThatClause(firstArg, secondArg){
        }
        FilterResult executePKBAbsQuery(PkbAbstractor *pkbAbstractor) {
            // For every vector in database, check if first pair and second pair matches the 2 data in db.
            // Match means either QueryDesignEntity / QueryArgValue matches the final result.
            f = FilterResult({}, false);
            for (int i = 0; i < db.size(); i++) {
                vector<pair<QueryDesignEntity, QueryArgValue>> currentData = db[i];
                bool shouldAdd = true;
                if (currentData.size() == 1) {
                    if (firstArg.queryDesignEntity != nullptr && !(*firstArg.queryDesignEntity == currentData[0].first)) {
                        shouldAdd = false;
                    }
                    if (firstArg.queryDesignEntity != nullptr && firstArg.argValue != nullptr && !(*firstArg.argValue == currentData[0].second)) {
                        shouldAdd = false;
                    }

                    if (secondArg.queryDesignEntity != nullptr && !(*secondArg.queryDesignEntity == currentData[0].first)) {
                        shouldAdd = false;
                    }
                    if (secondArg.queryDesignEntity != nullptr && secondArg.argValue != nullptr && !(*secondArg.argValue == currentData[0].second)) {
                        shouldAdd = false;
                    }
                } else {
                    if (firstArg.queryDesignEntity != nullptr && !(*firstArg.queryDesignEntity == currentData[0].first)) {
                        shouldAdd = false;
                    }
                    if (firstArg.queryDesignEntity != nullptr && firstArg.argValue != nullptr && !(*firstArg.argValue == currentData[0].second)) {
                        shouldAdd = false;
                    }

                    if (secondArg.queryDesignEntity != nullptr && !(*secondArg.queryDesignEntity == currentData[1].first)) {
                        shouldAdd = false;
                    }
                    if (secondArg.queryDesignEntity != nullptr && secondArg.argValue != nullptr && !(*secondArg.argValue == currentData[1].second)) {
                        shouldAdd = false;
                    }
                }
                if (shouldAdd) {
                    f.addResult(db[i]);
                }
            }
            if (f.getSize() > 0) {
                f.setHasMatch(true);
            }
            return f;
        };
        void addResults(vector<vector<pair<QueryDesignEntity, QueryArgValue>>> results) {
            db = results;
        }
    };
}
