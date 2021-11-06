#ifndef GUARD_OPTIMISER_H
#define GUARD_OPTIMISER_H

#include <set>
#include "pql/QueryPreprocessor/Query/Clause/FilterClause.h"

using std::set;

namespace pql {
    class Optimiser {
    public:
        static vector<FilterClause*> optimise(vector<QueryDesignEntity>, vector<FilterClause*>);
        static vector<FilterClause*> sortClauses(vector<FilterClause*>);
        static vector<vector<FilterClause*>> groupClausesBySynonym(vector<FilterClause*>);
        static vector<FilterClause*> setShldReturnEntityValBoolsInClauses(vector<QueryDesignEntity>, vector<FilterClause*>);
    private:
        // Clause with higher rank will be at the back of the list
        static unordered_map<ClauseType, int> rankingOfClauseType;
        static vector<vector<FilterClause*>> groupClausesByArgs(vector<FilterClause*>);
        static vector<vector<FilterClause*>> groupClausesWithSynByArgUsage(vector<FilterClause*>);
        static vector<vector<FilterClause*>> mergeClauseGroupsBySynonym(vector<vector<FilterClause*>>);
        static vector<vector<FilterClause*>> linkClauseGroupsBySynonym(vector<vector<FilterClause*>>);
        static vector<vector<FilterClause*>> orderClauseGroups(vector<vector<FilterClause*>>);
        static int calculateGroupPriorityScore(vector<FilterClause*>);
        static unordered_map<int, set<int>> createGraphOfGroupIdx(vector<vector<FilterClause*>>);
        static vector<vector<int>> getCollectionOfLargestGroupsOfGroupIdxWithLinks(unordered_map<int, set<int>>);
        struct ClauseSortStruct {
            bool operator()(FilterClause* firstClause, FilterClause* secondClause) const {
                ClauseType firstClauseType = firstClause->getClauseType();
                ClauseType secondClauseType = secondClause->getClauseType();
                int firstClausePriority = rankingOfClauseType.at(firstClauseType);
                int secondClausePriority = rankingOfClauseType.at(secondClauseType);
                if (firstClausePriority != secondClausePriority) {
                    return firstClausePriority < secondClausePriority;
                }

                int argIsSynonymPoints = 2;
                int argIsValuePoints = 1;
                int firstClauseRestrictivenessPoints = 0;
                int secondClauseRestrictivenessPoints = 0;
                vector<QueryArg*> firstClauseArgs = firstClause->getQueryArgs();
                for (QueryArg* argPtr : firstClauseArgs) {
                    if (argPtr->getQueryDesignEntity() != nullptr) {
                        firstClauseRestrictivenessPoints += argIsValuePoints;
                    } else if (argPtr->getQueryArgValue() != nullptr) {
                        firstClauseRestrictivenessPoints += argIsSynonymPoints;
                    }
                }
                vector<QueryArg*> secondClauseArgs = secondClause->getQueryArgs();
                for (QueryArg* argPtr : secondClauseArgs) {
                    if (argPtr->getQueryDesignEntity() != nullptr) {
                        secondClauseRestrictivenessPoints += argIsValuePoints;
                    } else if (argPtr->getQueryArgValue() != nullptr) {
                        secondClauseRestrictivenessPoints += argIsSynonymPoints;
                    }
                }
                return firstClauseRestrictivenessPoints > secondClauseRestrictivenessPoints;
            }
        };
    };
}

#endif
