#include "catch.hpp"

#include <set>
#include "pql/QueryEvaluator/Optimisation/Optimiser.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/FollowsClause.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/FollowsStarClause.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ModifiesClause.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/UsesClause.h"

using std::set;
using pql::DesignEntity;
using pql::FilterClause;
using pql::FollowsClause;
using pql::FollowsStarClause;
using pql::ModifiesClause;
using pql::UsesClause;
using pql::Optimiser;
using pql::QueryArg;
using pql::QueryArgValue;
using pql::QueryDesignEntity;


TEST_CASE("Optimiser should sort correctly", "[Optimiser]") {
    SECTION("should not fail with no clauses") {
        vector<FilterClause*> clauses = {};
        vector<FilterClause*> sortedClauses = Optimiser::sortClauses(clauses);
        REQUIRE(sortedClauses == clauses);
    }

    SECTION("should not fail with a single clause") {
        // sort Follows(a, 1) where a is assign.
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryArgValue stmt1 = {DesignEntity::STMT, "1"};
        QueryArg arg1 = {&assignA, nullptr, false};
        QueryArg arg2 = {nullptr, &stmt1, false};
        FollowsClause followsClause = {arg1, arg2};
        vector<FilterClause*> clauses = {&followsClause};
        vector<FilterClause*> sortedClauses = Optimiser::sortClauses(clauses);
        REQUIRE(sortedClauses == clauses);
    }

    SECTION("should sort clauses of different types correctly") {
        // {Follows*, Follows} should be sorted to {Follows, Follows*}
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryArgValue stmt1 = {DesignEntity::STMT, "1"};
        QueryArg arg1 = {&assignA, nullptr, false};
        QueryArg arg2 = {nullptr, &stmt1, false};
        FollowsClause followsClause = {arg1, arg2};
        FollowsStarClause followsStarClause = {arg1, arg2};
        vector<FilterClause*> clauses = {&followsStarClause, &followsClause};
        vector<FilterClause*> sortedClauses = Optimiser::sortClauses(clauses);
        vector<FilterClause*> expectedClauses = {&followsClause, &followsStarClause};
        REQUIRE(sortedClauses == expectedClauses);
    }

    SECTION("should sort clauses of same types but different number of synonyms correctly") {
        // {Follows(a,s), Follows(a,1)} should be sorted to {Follows(a,1), Follows(a,s)}
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryDesignEntity stmtS = {DesignEntity::STMT, "s"};
        QueryArgValue stmt1 = {DesignEntity::STMT, "1"};
        QueryArg arg1 = {&assignA, nullptr, false};
        QueryArg arg2 = {nullptr, &stmt1, false};
        QueryArg arg3 = {&stmtS, nullptr, false};
        FollowsClause followsClause = {arg1, arg2}; // Follows(a, 1)
        FollowsClause followsClause1 = {arg1, arg3}; // Follows(a, s)
        vector<FilterClause*> clauses = {&followsClause1, &followsClause};
        vector<FilterClause*> sortedClauses = Optimiser::sortClauses(clauses);
        vector<FilterClause*> expectedClauses = {&followsClause, &followsClause1};
        REQUIRE(sortedClauses == expectedClauses);
    }
}

TEST_CASE("should group clauses correctly", "[Optimiser]") {
    SECTION("should not fail with no clauses") {
        vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClausesBySynonym({});
        set<set<FilterClause*>> obtainedGrouping = {};
        for (vector<FilterClause*> group : groupedClauses) {
            set<FilterClause*> groupSet(group.begin(), group.end());
            obtainedGrouping.insert(groupSet);
        }
        set<set<FilterClause*>> expectedGrouping = {};
        REQUIRE(obtainedGrouping == expectedGrouping);
    }

    SECTION("should not fail with 1 clause") {
        // Follows(a, s)
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryDesignEntity stmtS = {DesignEntity::STMT, "s"};
        QueryArg assignAArg = {&assignA, nullptr, false};
        QueryArg stmtSArg = {&stmtS, nullptr, false};
        FollowsClause follows = {assignAArg, stmtSArg};
        vector<FilterClause*> clauses = {&follows};
        vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClausesBySynonym(clauses);
        set<set<FilterClause*>> obtainedGrouping = {};
        for (vector<FilterClause*> group : groupedClauses) {
            set<FilterClause*> groupSet(group.begin(), group.end());
            obtainedGrouping.insert(groupSet);
        }
        set<set<FilterClause*>> expectedGrouping = {{&follows}};
        REQUIRE(obtainedGrouping == expectedGrouping);
    }

    SECTION("should not fail with 1 clause with 2 same synonyms") {
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryDesignEntity assignA1 = {DesignEntity::ASSIGN, "a"};
        QueryArg assignAArg = {&assignA, nullptr, false};
        QueryArg assignAArg1 = {&assignA1, nullptr, false};
        FollowsClause follows = {assignAArg, assignAArg1};
        vector<FilterClause*> clauses = {&follows};
        vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClausesBySynonym(clauses);
        set<set<FilterClause*>> obtainedGrouping = {};
        for (vector<FilterClause*> group : groupedClauses) {
            set<FilterClause*> groupSet(group.begin(), group.end());
            obtainedGrouping.insert(groupSet);
        }
        set<set<FilterClause*>> expectedGrouping = {{&follows}};
        REQUIRE(obtainedGrouping == expectedGrouping);
    }

    SECTION("should group multiple clauses with synonyms correctly") {
        // assign a; stmt s, s1; variable v, v1
        // {Follows(s, v), Uses(s1, v1), Modifies(s,v)} =>
        // {Follows(s, 1), Modifies(s,v)}, {Uses(s1, v1)}}
        QueryArgValue stmt1 = {DesignEntity::STMT, "1"};
        QueryDesignEntity stmtS = {DesignEntity::STMT, "s"};
        QueryDesignEntity stmtS1 = {DesignEntity::STMT, "s1"};
        QueryDesignEntity varV = {DesignEntity::VARIABLE, "v"};
        QueryDesignEntity varV1= {DesignEntity::VARIABLE, "v1"};
        QueryArg stmt1Arg = {nullptr, &stmt1, false};
        QueryArg stmtSArg = {&stmtS, nullptr, false};
        QueryArg stmtS1Arg = {&stmtS1, nullptr, false};
        QueryArg varVArg = {&varV, nullptr, false};
        QueryArg varV1Arg = {&varV1, nullptr, false};
        FollowsClause follows = {stmtSArg, stmt1Arg};
        UsesClause uses = {stmtS1Arg, varV1Arg};
        ModifiesClause modifies = {stmtSArg, varVArg};
        vector<FilterClause*> clauses = {&follows, &uses, &modifies};
        vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClausesBySynonym(clauses);
        vector<set<FilterClause*>> obtainedGrouping = {};
        for (vector<FilterClause*> group : groupedClauses) {
            set<FilterClause*> groupSet(group.begin(), group.end());
            obtainedGrouping.push_back(groupSet);
        }
        vector<set<FilterClause*>> expectedGrouping = {{&follows, &modifies}, {&uses}};
        REQUIRE(expectedGrouping == obtainedGrouping);
    }

    SECTION("should group multiple clauses with synonyms correctly") {
        // assign a; stmt s, s1; variable v, v1
        // {Follows(a, s), Follows*(s,a), Uses(s1, v1), Modifies(s,v)} =>
        // {Follows(a, s), Follows*(s,a), Modifies(s,v)} & {Uses(s1, v1)}
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryDesignEntity stmtS = {DesignEntity::STMT, "s"};
        QueryDesignEntity stmtS1 = {DesignEntity::STMT, "s1"};
        QueryDesignEntity varV = {DesignEntity::VARIABLE, "v"};
        QueryDesignEntity varV1= {DesignEntity::VARIABLE, "v1"};
        QueryArg assignAArg = {&assignA, nullptr, false};
        QueryArg stmtSArg = {&stmtS, nullptr, false};
        QueryArg stmtS1Arg = {&stmtS1, nullptr, false};
        QueryArg varVArg = {&varV, nullptr, false};
        QueryArg varV1Arg = {&varV1, nullptr, false};
        FollowsClause follows = {assignAArg, stmtSArg};
        FollowsStarClause followsStar = {stmtSArg, assignAArg};
        UsesClause uses = {stmtS1Arg, varV1Arg};
        ModifiesClause modifies = {stmtSArg, varVArg};
        vector<FilterClause*> clauses = {&follows, &followsStar, &uses, &modifies};
        vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClausesBySynonym(clauses);
        set<set<FilterClause*>> obtainedGrouping = {};
        for (vector<FilterClause*> group : groupedClauses) {
            set<FilterClause*> groupSet(group.begin(), group.end());
            obtainedGrouping.insert(groupSet);
        }
        set<set<FilterClause*>> expectedGrouping = {{&follows, &followsStar, &modifies}, {&uses}};
        REQUIRE(expectedGrouping == obtainedGrouping);
    }

    SECTION("should group multiple clauses with synonyms correctly ii") {
//        select <s, s3> such that Follows(s, s1) such that Follows(s2, s3) such that follows(s1, s2)
        QueryDesignEntity stmtS = {DesignEntity::STMT, "s"};
        QueryDesignEntity stmtS1 = {DesignEntity::STMT, "s1"};
        QueryDesignEntity stmtS2 = {DesignEntity::STMT, "s2"};
        QueryDesignEntity stmtS3 = {DesignEntity::STMT, "s3"};
        QueryArg stmtSArg = {&stmtS, nullptr, false};
        QueryArg stmtS1Arg = {&stmtS1, nullptr, false};
        QueryArg stmtS2Arg = {&stmtS2, nullptr, false};
        QueryArg stmtS3Arg = {&stmtS3, nullptr, false};
        FollowsClause follows = {stmtSArg, stmtS1Arg};
        FollowsClause follows1 = {stmtS2Arg, stmtS3Arg};
        FollowsClause follows2 = {stmtS1Arg, stmtS2Arg};
        vector<FilterClause*> clauses = {&follows, &follows1, &follows2};
        vector<vector<FilterClause*>> groupedClauses = Optimiser::groupClausesBySynonym(clauses);
        int firstGroupSize = 0;
        int secondGroupSize = 0;
        firstGroupSize = groupedClauses[0].size();
        secondGroupSize = groupedClauses[1].size();

        // As long as a group of 2 is at the front, a group of one is at the back, no cartesian product.
        REQUIRE((firstGroupSize == 2 && secondGroupSize == 1));
    }
}

TEST_CASE("should set 'shldReturn' booleans in clauses correctly", "[Optimiser]") {
    SECTION("should not fail with no clauses") {
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        vector<FilterClause*> obtainedResult = Optimiser::setShldReturnEntityValBoolsInClauses({assignA}, {});
        vector<FilterClause*> expectedResult = {};
        REQUIRE(expectedResult == obtainedResult);
    }

    SECTION("should set booleans correctly when entity in clause is selected") {
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryDesignEntity stmtS = {DesignEntity::STMT, "s"};
        QueryArg assignAArg = {&assignA, nullptr, false};
        QueryArg stmtSArg = {&stmtS, nullptr, false};
        FollowsClause follows = {assignAArg, stmtSArg};
        FollowsClause expectedFollows = {assignAArg, stmtSArg};
        vector<FilterClause*> obtainedResult = Optimiser::setShldReturnEntityValBoolsInClauses({assignA}, {&follows});
        expectedFollows.setShldReturnFirst(true);
        expectedFollows.setShldReturnSecond(false);
        REQUIRE(follows == expectedFollows);
    }

    SECTION("should set booleans correctly when entity in clause is not selected") {
        QueryDesignEntity assignA = {DesignEntity::ASSIGN, "a"};
        QueryDesignEntity stmtS = {DesignEntity::STMT, "s"};
        QueryArg assignAArg = {&assignA, nullptr, false};
        QueryArg stmtSArg = {&stmtS, nullptr, false};
        FollowsClause follows = {assignAArg, stmtSArg};
        FollowsClause expectedFollows = {assignAArg, stmtSArg};
        vector<FilterClause*> obtainedResult = Optimiser::setShldReturnEntityValBoolsInClauses({}, {&follows});
        expectedFollows.setShldReturnFirst(false);
        expectedFollows.setShldReturnSecond(false);
        REQUIRE(follows == expectedFollows);
    }
}