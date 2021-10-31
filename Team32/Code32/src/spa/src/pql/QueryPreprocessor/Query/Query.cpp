#include "Query.h"
#include <unordered_set>
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/SuchThatClause.h"
#include "pql/QueryPreprocessor/Query/Clause/PatternClause//PatternClause.h"
#include <algorithm>
#include "SyntaxCheck.h"

using std::unordered_set;
using pql::FilterClause;
using pql::Query;
using pql::QueryDesignEntity;
using pql::SelectClause;
using pql::SemanticError;

Query::Query(SelectClause* select, std::vector<QueryDesignEntity> designEntitiesVector, std::vector<FilterClause*> filterClauseVector)
: select(select), designEntitiesVector(designEntitiesVector), filterClauseVector(filterClauseVector) {
    unordered_set<std::string> entityNames = {};
    for (QueryDesignEntity qde: designEntitiesVector) {
        if (entityNames.find(qde.variableName) == entityNames.end()) {
            entityNames.insert(qde.variableName);
        } else {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Query: Repeated use of same synonym not allowed");
        }
    }

    unordered_set<QueryDesignEntity> designEntitiesSet(designEntitiesVector.begin(), designEntitiesVector.end());

    for (QueryDesignEntity qde : select->queryDesignEntities) {
        if (designEntitiesSet.find(qde) == designEntitiesSet.end()) {
            if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Query: Selected entity is not declared");
        }
    }


    for (FilterClause* filterClause : filterClauseVector) {
        vector<QueryArg*> queryArgs = filterClause->getQueryArgs();
        for (QueryArg* queryArg : queryArgs) {
            if (queryArg->queryDesignEntity != nullptr && designEntitiesSet.find(*queryArg->queryDesignEntity) == designEntitiesSet.end()) {
                if (!pql::SyntaxCheck::isSyntaxCheck()) throw SemanticError("Query: Query argument in clause is not declared");
            }
        }
    }
}

bool Query::operator==(const Query& other) const {
    if (filterClauseVector.size() != other.filterClauseVector.size()) {
        return false;
    }
    vector<pql::SuchThatClause> s = {};
    vector<pql::PatternClause> p = {};
    for (FilterClause* filterClausePtr : filterClauseVector) {
        SuchThatClause* suchThatClausePtr = dynamic_cast<SuchThatClause*>(filterClausePtr);
        if (suchThatClausePtr != nullptr) {
            s.push_back(*suchThatClausePtr);
        }
        PatternClause* patternClausePtr = dynamic_cast<PatternClause*>(filterClausePtr);
        if (patternClausePtr != nullptr) {
            p.push_back(*patternClausePtr);
        }
    }
    for (FilterClause* filterClausePtr : other.filterClauseVector) {
        SuchThatClause* suchThatClausePtr = dynamic_cast<SuchThatClause*>(filterClausePtr);
        if (suchThatClausePtr != nullptr) {
            auto it = std::find(s.begin(), s.end(), *suchThatClausePtr);
            if (it == s.end()) {
                return false;
            }
        }
        PatternClause* patternClausePtr = dynamic_cast<PatternClause*>(filterClausePtr);
        if (patternClausePtr != nullptr) {
            auto it = std::find(p.begin(), p.end(), *patternClausePtr);
            if (it == p.end()) {
                return false;
            }
        }
    }
    return *select == *other.select && designEntitiesVector == other.designEntitiesVector;
}