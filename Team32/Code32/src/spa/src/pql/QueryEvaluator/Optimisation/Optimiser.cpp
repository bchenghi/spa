#include "Optimiser.h"

#include <algorithm>
#include <list>
#include <set>

using pql::Optimiser;
using pql::FilterClause;
using pql::ClauseType;
using std::list;
using std::set;
using std::sort;

unordered_map<ClauseType, int> Optimiser::rankingOfClauseType = {{ClauseType::WITH, 1},
                                                                 {ClauseType::PARENT, 2},
                                                                 {ClauseType::FOLLOWS, 2},
                                                                 {ClauseType::ASSIGNMENTPATTERN, 3},
                                                                 {ClauseType::IFPATTERN, 3},
                                                                 {ClauseType::WHILEPATTERN, 3},
                                                                 {ClauseType::USES, 4},
                                                                 {ClauseType::MODIFIES, 4},
                                                                 {ClauseType::CALLS, 5},
                                                                 {ClauseType::CALLSSTAR, 5},
                                                                 {ClauseType::PARENTSTAR, 6},
                                                                 {ClauseType::FOLLOWSSTAR, 6},
                                                                 {ClauseType::NEXT, 7},
                                                                 {ClauseType::NEXTSTAR, 8},
                                                                 {ClauseType::AFFECTS, 9},
                                                                 {ClauseType::AFFECTSSTAR, 9},
                                                                 {ClauseType::NONE, 10},
                                                                 };

vector<FilterClause*> Optimiser::optimise(vector<QueryDesignEntity> selectedEntities, vector<FilterClause*> clauses) {
    vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClauses(clauses);
    vector<FilterClause*> finalResult = {};
    for (vector<FilterClause*> clauseGroup : groupedClauses) {
        vector<FilterClause*> sortedClauseGroup = Optimiser::sortClauses(clauseGroup);
        finalResult.insert(finalResult.end(), sortedClauseGroup.begin(), sortedClauseGroup.end());
    }
    finalResult = setShldReturnEntityValBoolsInClauses(selectedEntities, finalResult);
    return finalResult;
}

vector<FilterClause*> Optimiser::sortClauses(vector<FilterClause*> clauses) {
    sort(clauses.begin(), clauses.end(), ClauseSortStruct());
    return clauses;
}

vector<vector<FilterClause*>> Optimiser::groupClauses(vector<FilterClause*> clauses) {
    // Get clauses with only values as arguments
    vector<FilterClause*> clausesWithOnlyValuesAsArgs = {};
    list<FilterClause*> remainingClauses(clauses.begin(), clauses.end());
    auto it = remainingClauses.begin();
    while(it != remainingClauses.end()) {
        FilterClause* clause = *it;
        vector<QueryArg*> args = clause->getQueryArgs();
        bool clauseHasValuesAsArgs = true;
        for (QueryArg* arg : args) {
            if (arg->isWildCard || arg->queryDesignEntity != nullptr) {
                clauseHasValuesAsArgs = false;
                break;
            }
        }
        if (clauseHasValuesAsArgs) {
            it = remainingClauses.erase(it);
            clausesWithOnlyValuesAsArgs.push_back(clause);
            continue;
        }
        it++;
    }

    // Get clauses with only wildcards as arguments
    vector<FilterClause*> clausesWithOnlyWildcardsAsArgs = {};
    it = remainingClauses.begin();
    while (it != remainingClauses.end()) {
        FilterClause* clause = *it;
        vector<QueryArg*> args = clause->getQueryArgs();
        bool clauseHasWildcardsAsArgs = true;
        for (QueryArg* arg : args) {
            if (!arg->isWildCard) {
                clauseHasWildcardsAsArgs = false;
                break;
            }
        }
        if (clauseHasWildcardsAsArgs) {
            it = remainingClauses.erase(it);
            clausesWithOnlyWildcardsAsArgs.push_back(clause);
            continue;
        }
        it++;
    }

    // Get clauses with one value and one wildcard
    vector<FilterClause*> clausesWithValueAndWildcard = {};
    it = remainingClauses.begin();
    while (it != remainingClauses.end()) {
        FilterClause* clause = *it;
        vector<QueryArg*> args = clause->getQueryArgs();
        if ((args[0]->isWildCard && args[1]->argValue != nullptr) || (args[1]->isWildCard && args[0]->argValue != nullptr)) {
            it = remainingClauses.erase(it);
            clausesWithValueAndWildcard.push_back(clause);
            continue;
        }
        it++;
    }

    // Remaining clauses should contain at least one synonym.
    // Use greedy algorithm to form the least number of groups of clauses with synonyms.
    // O(n^2)
    vector<vector<FilterClause*>> clauseGroupsWithSynonyms = {};
    while (!remainingClauses.empty()) {
        // Allocate clauses to synonyms they used.
        unordered_map<QueryDesignEntity, set<FilterClause*>> mapOfSynonymAndClausesWithSynonym = {};
        for (FilterClause* clause : remainingClauses) {
            vector<QueryArg*> args = clause->getQueryArgs();
            for (QueryArg* arg : args) {
                if (arg->queryDesignEntity == nullptr) {
                    continue;
                }
                QueryDesignEntity qde = *(arg->queryDesignEntity);
                if (mapOfSynonymAndClausesWithSynonym.find(qde) == mapOfSynonymAndClausesWithSynonym.end()) {
                    mapOfSynonymAndClausesWithSynonym.insert({qde, {clause}});
                } else {
                    mapOfSynonymAndClausesWithSynonym.at(qde).insert(clause);
                }
            }
        }

        // Get clauses in largest group.
        // not possible for map to be empty
        QueryDesignEntity synonymWithMostClauses = {DesignEntity::NONE, "placeholder"};
        int largestSize = 0;
        for (auto& synonymAndClauses : mapOfSynonymAndClausesWithSynonym) {
            int size = synonymAndClauses.second.size();
            if (size > largestSize) {
                largestSize = size;
                synonymWithMostClauses = synonymAndClauses.first;
            }
        }

        set<FilterClause*> largestGroupOfClausesSet = mapOfSynonymAndClausesWithSynonym.at(synonymWithMostClauses);
        vector<FilterClause*> largestGroupOfClauses(largestGroupOfClausesSet.begin(), largestGroupOfClausesSet.end());
        clauseGroupsWithSynonyms.push_back(largestGroupOfClauses);

        // Remove the clauses from remaining clauses list.
        for (FilterClause* clause : largestGroupOfClauses) {
            remainingClauses.remove(clause);
        }
    }

    // clause groups with synonym can be ordered such that the groups have links between each other.
    vector<vector<FilterClause*>> orderedClauseGroupsWithSynonyms = {};
    while (!clauseGroupsWithSynonyms.empty()) {
        unordered_map<int, set<int>> graphOfGroupIdx = {};
        // Allocate groups to synonyms they used.
        unordered_map<int, set<QueryDesignEntity>> mapOfClauseGroupIdxAndSynonym = {};
        unordered_map<QueryDesignEntity, set<int>> mapOfSynonymAndClauseGroupIdx = {};
        for (int idx = 0; idx < clauseGroupsWithSynonyms.size(); idx++) {
            vector<FilterClause*> clauseGroup = clauseGroupsWithSynonyms[idx];
            for (FilterClause* clause : clauseGroup) {
                vector<QueryArg*> args = clause->getQueryArgs();
                for (QueryArg* arg : args) {
                    if (arg->queryDesignEntity == nullptr) {
                        continue;
                    }
                    QueryDesignEntity qde = *(arg->queryDesignEntity);
                    if (mapOfSynonymAndClauseGroupIdx.find(qde) == mapOfSynonymAndClauseGroupIdx.end()) {
                        mapOfSynonymAndClauseGroupIdx.insert({qde, {idx}});
                    } else {
                        mapOfSynonymAndClauseGroupIdx.at(qde).insert(idx);
                    }

                    if (mapOfClauseGroupIdxAndSynonym.find(idx) == mapOfClauseGroupIdxAndSynonym.end()) {
                        mapOfClauseGroupIdxAndSynonym.insert({idx, {qde}});
                    } else {
                        mapOfClauseGroupIdxAndSynonym.at(idx).insert(qde);
                    }
                }
            }
        }

        for (int idx = 0; idx < clauseGroupsWithSynonyms.size(); idx++) {
            set<QueryDesignEntity> entitiesInGroup = mapOfClauseGroupIdxAndSynonym.at(idx);
            set<int> groupIdxWithEdges = {};
            for (QueryDesignEntity entity : entitiesInGroup) {
                set<int> groupIdxWithEntity = mapOfSynonymAndClauseGroupIdx.at(entity);
                groupIdxWithEntity.erase(idx);
                groupIdxWithEdges.insert(groupIdxWithEntity.begin(), groupIdxWithEntity.end());
            }
            graphOfGroupIdx.insert({idx, groupIdxWithEdges});
        }

        int sizeOfLargestGroup = 0;
        vector<int> largestGroup = {};
        set<int> visitedGroups = {};
        vector<int> groupIdxWithLinks = {};
        for(int i = 0; i < graphOfGroupIdx.size(); i++) {
            if (visitedGroups.find(i) != visitedGroups.end()) {
                continue;
            }
            list<int> queue = {i};
            while(!queue.empty()) {
                int currentGroupIdx = queue.front();
                queue.pop_front();
                // If already visited.
                if (visitedGroups.find(currentGroupIdx) != visitedGroups.end()) {
                    continue;
                }

                groupIdxWithLinks.push_back(currentGroupIdx);
                visitedGroups.insert(currentGroupIdx);
                set<int> adjacentGroupIdx = graphOfGroupIdx.at(currentGroupIdx);
                for (int groupId : adjacentGroupIdx) {
                    queue.push_back(groupId);
                }
            }

            if (groupIdxWithLinks.size() > sizeOfLargestGroup) {
                sizeOfLargestGroup = groupIdxWithLinks.size();
                largestGroup = groupIdxWithLinks;
            }
            groupIdxWithLinks = {};
        }

        // Add clause groups with links between them to final vector
        for (int groupId : largestGroup) {
            orderedClauseGroupsWithSynonyms.push_back(clauseGroupsWithSynonyms[groupId]);
        }

        // Remove the groups from original group vector.
        for (auto it = largestGroup.rbegin(); it != largestGroup.rend(); ++it) {
            clauseGroupsWithSynonyms.erase(clauseGroupsWithSynonyms.begin() + *it);
        }
    }

    // Ordering of groups: only values, one value and one wildcard, clauses with at least one synonym, only wildcards.
    vector<vector<FilterClause*>> finalGrouping = {};
    if (!clausesWithOnlyValuesAsArgs.empty()) {
        finalGrouping.push_back(clausesWithOnlyValuesAsArgs);
    }
    if (!clausesWithValueAndWildcard.empty()) {
        finalGrouping.push_back(clausesWithValueAndWildcard);
    }
    finalGrouping.insert(finalGrouping.end(), orderedClauseGroupsWithSynonyms.begin(), orderedClauseGroupsWithSynonyms.end());
    if (!clausesWithOnlyWildcardsAsArgs.empty()) {
        finalGrouping.push_back(clausesWithOnlyWildcardsAsArgs);
    }
    return finalGrouping;
}

vector<FilterClause*> Optimiser::setShldReturnEntityValBoolsInClauses(vector<QueryDesignEntity> selectedDesignEntities, vector<FilterClause*> clauses) {
    unordered_map<QueryDesignEntity, int> mapOfSynonymAndTheirUsageCount = {};
    for(QueryDesignEntity qde : selectedDesignEntities) {
        mapOfSynonymAndTheirUsageCount.insert({qde, 1});
    }

    unordered_map<QueryDesignEntity, vector<FilterClause*>> mapOfSynonymAndClausesWithSynonym = {};
    for (FilterClause* clause : clauses) {
        vector<QueryArg*> args = clause->getQueryArgs();
        for (QueryArg* arg : args) {
            if (arg->queryDesignEntity == nullptr) {
                continue;
            }
            QueryDesignEntity qde = *(arg->queryDesignEntity);
            if (mapOfSynonymAndClausesWithSynonym.find(qde) == mapOfSynonymAndClausesWithSynonym.end()) {
                mapOfSynonymAndClausesWithSynonym.insert({qde, {clause}});
            } else {
                mapOfSynonymAndClausesWithSynonym.at(qde).push_back(clause);
            }
            if (mapOfSynonymAndTheirUsageCount.find(qde) == mapOfSynonymAndTheirUsageCount.end()) {
                mapOfSynonymAndTheirUsageCount.insert({qde, 1});
            } else {
                mapOfSynonymAndTheirUsageCount.at(qde)++;
            }
        }
    }

    // Check number of usages of a synonym. If only used once, get the clause that uses the synonym,
    // and set the "shldReturnFirst" value to false if the synonym is the first arg, and and set the "shldReturnSecond" value to false
    // if the synonym is the second arg.
    for (auto it = mapOfSynonymAndTheirUsageCount.begin(); it != mapOfSynonymAndTheirUsageCount.end(); it++) {
        if (it->second == 1) {
            QueryDesignEntity entityOnlyUsedOnce = it->first;
            if (mapOfSynonymAndClausesWithSynonym.find(entityOnlyUsedOnce) == mapOfSynonymAndClausesWithSynonym.end()) {
                continue;
            }
            vector<FilterClause*> clausesWithTheEntity = mapOfSynonymAndClausesWithSynonym.at(entityOnlyUsedOnce);
            for (FilterClause* clause : clausesWithTheEntity) {
                vector<QueryArg*> args = clause->getQueryArgs();
                for (int i = 0; i < args.size(); i++) {
                    QueryArg* arg = args[i];
                    if (arg->queryDesignEntity == nullptr) {
                        continue;
                    }
                    QueryDesignEntity qde = *(arg->queryDesignEntity);
                    if (qde == it->first) {
                        if (i == 0) {
                            clause -> shldReturnFirst = false;
                        } else {
                            clause -> shldReturnSecond = false;
                        }
                    }
                }
            }
        }
    }
    return clauses;
}
