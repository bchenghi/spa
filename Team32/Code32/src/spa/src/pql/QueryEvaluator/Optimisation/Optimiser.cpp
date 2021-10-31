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
                                                                 {ClauseType::NEXT, 6},
                                                                 {ClauseType::NEXTBIP, 7},
                                                                 {ClauseType::AFFECTSBIP, 8},
                                                                 {ClauseType::CALLSSTAR, 9},
                                                                 {ClauseType::NEXTBIPSTAR, 10},
                                                                 {ClauseType::AFFECTSBIPSTAR, 11},
                                                                 {ClauseType::PARENTSTAR, 12},
                                                                 {ClauseType::FOLLOWSSTAR, 12},
                                                                 {ClauseType::AFFECTS, 13},
                                                                 {ClauseType::NEXTSTAR, 14},
                                                                 {ClauseType::AFFECTSSTAR, 15},
                                                                 {ClauseType::NONE, 16},
                                                                 };

vector<FilterClause*> Optimiser::optimise(vector<QueryDesignEntity> selectedEntities, vector<FilterClause*> clauses) {
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

    vector<FilterClause*> remainingClausesVector(remainingClauses.begin(), remainingClauses.end());
    vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClausesBySynonym(remainingClausesVector);

    vector<vector<FilterClause*>> groupsWithSortedClauses = {};
    for (vector<FilterClause*> clauseGroup : groupedClauses) {
        vector<FilterClause*> sortedClauseGroup = Optimiser::sortClauses(clauseGroup);
        groupsWithSortedClauses.push_back(sortedClauseGroup);
    }

    vector<vector<FilterClause*>> clauseGroupsAftMerge = Optimiser::mergeClauseGroupsBySynonym(groupsWithSortedClauses);
    vector<vector<FilterClause*>> sortedClauseGroups = Optimiser::orderClauseGroups(clauseGroupsAftMerge);

    // Ordering of groups: only values, one value and one wildcard, clauses with at least one synonym, only wildcards.
    vector<vector<FilterClause*>> finalGrouping = {};
    if (!clausesWithOnlyValuesAsArgs.empty()) {
        finalGrouping.push_back(clausesWithOnlyValuesAsArgs);
    }
    if (!clausesWithValueAndWildcard.empty()) {
        finalGrouping.push_back(clausesWithValueAndWildcard);
    }
    finalGrouping.insert(finalGrouping.end(), sortedClauseGroups.begin(), sortedClauseGroups.end());
    if (!clausesWithOnlyWildcardsAsArgs.empty()) {
        finalGrouping.push_back(clausesWithOnlyWildcardsAsArgs);
    }

    vector<FilterClause*> finalResult = {};
    for (vector<FilterClause*> clauseGroup : finalGrouping) {
        finalResult.insert(finalResult.end(), clauseGroup.begin(), clauseGroup.end());
    }

    finalResult = setShldReturnEntityValBoolsInClauses(selectedEntities, finalResult);
    return finalResult;
}

vector<FilterClause*> Optimiser::sortClauses(vector<FilterClause*> clauses) {
    sort(clauses.begin(), clauses.end(), ClauseSortStruct());
    return clauses;
}

vector<vector<FilterClause*>> Optimiser::groupClausesBySynonym(vector<FilterClause*> clauses) {
    list<FilterClause*> remainingClauses(clauses.begin(), clauses.end());
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
    return clauseGroupsWithSynonyms;
}

vector<vector<FilterClause*>> Optimiser::mergeClauseGroupsBySynonym(vector<vector<FilterClause*>> clauseGroupsWithSynonyms) {
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
        vector<vector<int>> collectionOfLargestGroupsOfGroups = {};
        set<int> visitedGroups = {};
        vector<int> groupIdxWithLinks = {};
        for(int i = 0; i < graphOfGroupIdx.size(); i++) {
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
                collectionOfLargestGroupsOfGroups = {groupIdxWithLinks};
                sizeOfLargestGroup = groupIdxWithLinks.size();
            } else if (groupIdxWithLinks.size() == sizeOfLargestGroup) {
                collectionOfLargestGroupsOfGroups.push_back(groupIdxWithLinks);
            }
            groupIdxWithLinks = {};
            visitedGroups = {};
        }

        // choose the largest group of groups that decreases in restrictiveness the most.
        int bestScore = -1;
        vector<int> largestGroupOfGroups = {};
        for (vector<int> groupOfGroups : collectionOfLargestGroupsOfGroups) {
            // Priorities should be ordered such that smallest at the front.
            // Increase score by difference in worsening of ordering of priority. e.g. priorities of groups: 1 -> 5 -> 2.
            // 1 -> (0) 5 -> (-3) 2 so final score is 3.
            int score = 0;
            int prevGroupScore = -1;
            for (int groupIdx : groupOfGroups) {
                int averageClauseGroupScore = Optimiser::calculateGroupPriorityScore(clauseGroupsWithSynonyms[groupIdx]);
                if (prevGroupScore != -1 && prevGroupScore > averageClauseGroupScore) {
                    score += prevGroupScore - averageClauseGroupScore;
                } else {
                    prevGroupScore = averageClauseGroupScore;
                }
            }
            if (bestScore == -1) {
                bestScore = score;
                largestGroupOfGroups = groupOfGroups;
            } else if (bestScore > score) {
                bestScore = score;
                largestGroupOfGroups = groupOfGroups;
            }
        }

        vector<FilterClause*> mergedGroupOfGroups = {};
        // Merge clause groups with links between them and add merged group to final vector
        for (int groupId : largestGroupOfGroups) {
            vector<FilterClause*> groupInLargestGroup = clauseGroupsWithSynonyms[groupId];
            mergedGroupOfGroups.insert(mergedGroupOfGroups.end(), groupInLargestGroup.begin(), groupInLargestGroup.end());
        }

        orderedClauseGroupsWithSynonyms.push_back(mergedGroupOfGroups);

        set<int> orderedIdsInLargestGroup(largestGroupOfGroups.begin(), largestGroupOfGroups.end());
        // Remove the groups from original group vector.
        for (auto it = orderedIdsInLargestGroup.rbegin(); it != orderedIdsInLargestGroup.rend(); ++it) {
            clauseGroupsWithSynonyms.erase(clauseGroupsWithSynonyms.begin() + *it);
        }
    }
    return orderedClauseGroupsWithSynonyms;
}

vector<vector<FilterClause*>> Optimiser::orderClauseGroups(vector<vector<FilterClause*>> clauseGroups) {
    vector<pair<int, int>> listOfPriorityAndIdx = {};
    for (int i = 0; i < clauseGroups.size(); i++) {
        vector<FilterClause*> group = clauseGroups[i];
        int averagePriorityScore = Optimiser::calculateGroupPriorityScore(group);
        listOfPriorityAndIdx.push_back({averagePriorityScore, i});
    }
    std::sort(listOfPriorityAndIdx.begin(), listOfPriorityAndIdx.end());
    vector<vector<FilterClause*>> result = {};
    for (pair<int, int> priorityAndIdx : listOfPriorityAndIdx) {
        int idx = priorityAndIdx.second;
        result.push_back(clauseGroups[idx]);
    }
    return result;
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

int Optimiser::calculateGroupPriorityScore(vector<FilterClause *> group) {
    int totalPriorityScore = 0;
    int numOfClausesInGroup = 0;
    for (FilterClause* clause : group) {
        totalPriorityScore += rankingOfClauseType.at(clause->getClauseType());
        numOfClausesInGroup++;
    }
    int averagePriorityScore = totalPriorityScore / numOfClausesInGroup;
    return averagePriorityScore;
}