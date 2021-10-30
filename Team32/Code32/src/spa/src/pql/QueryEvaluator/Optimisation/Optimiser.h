#ifndef GUARD_OPTIMISER_H
#define GUARD_OPTIMISER_H

#include "pql/QueryPreprocessor/Query/Clause/FilterClause.h"

namespace pql {
    class Optimiser {
        // Group based on same synonym
    public:
        // Clause with higher rank will be at the back of the list
        static unordered_map<ClauseType, int> rankingOfClauseType;
        static vector<FilterClause*> optimise(vector<QueryDesignEntity> selectedEntities, vector<FilterClause*>);
        static vector<FilterClause*> sortClauses(vector<FilterClause*>);
        static vector<vector<FilterClause*>> groupClausesBySynonym(vector<FilterClause*>);
        static vector<vector<FilterClause*>> mergeClauseGroupsBySynonym(vector<vector<FilterClause*>>);
        static vector<vector<FilterClause*>> orderClauseGroups(vector<vector<FilterClause*>>);
        static int calculateGroupPriorityScore(vector<FilterClause*>);

        // If an entity is used only once in entire query (select and filter clause),
        // the entity does not need to be tracked.
        // Clauses do not need to return their values
        static vector<FilterClause*> setShldReturnEntityValBoolsInClauses(vector<QueryDesignEntity>, vector<FilterClause*>);
        struct ClauseSortStruct {
            bool operator()(FilterClause* firstClause, FilterClause* secondClause) const {
                // Sort by clause type
                ClauseType firstClauseType = firstClause -> getClauseType();
                ClauseType secondClauseType = secondClause -> getClauseType();
                int firstClausePriority = rankingOfClauseType.at(firstClauseType);
                int secondClausePriority = rankingOfClauseType.at(secondClauseType);
                if (firstClausePriority != secondClausePriority) {
                    return firstClausePriority < secondClausePriority;
                }

                // If clause type is the same, prioritise more restrictive arguments.
                // Value worth 2, Synonyms worth 1 pt, wildcard worth 0.
                int firstClauseRestrictivenessPoints = 0;
                int secondClauseRestrictivenessPoints = 0;
                vector<QueryArg*> firstClauseArgs = firstClause -> getQueryArgs();
                for (QueryArg* argPtr : firstClauseArgs) {
                    if (argPtr -> queryDesignEntity != nullptr) {
                        firstClauseRestrictivenessPoints++;
                    } else if (argPtr -> argValue != nullptr) {
                        firstClauseRestrictivenessPoints += 2;
                    }
                }
                vector<QueryArg*> secondClauseArgs = secondClause -> getQueryArgs();
                for (QueryArg* argPtr : secondClauseArgs) {
                    if (argPtr -> queryDesignEntity != nullptr) {
                        secondClauseRestrictivenessPoints++;
                    } else if (argPtr -> argValue != nullptr) {
                        secondClauseRestrictivenessPoints += 2;
                    }
                }
                return firstClauseRestrictivenessPoints > secondClauseRestrictivenessPoints;
            }
        };
    };
}

#endif //GUARD_OPTIMISER_H
