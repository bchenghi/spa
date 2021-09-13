#include "catch.hpp"
#include "pql/QueryPreprocessor/Query/Clause/SelectClause.h"
#include "Stubs/PkbAbstractorStub.cpp"
#include <set>

using clausetest::PkbAbstractorStub;
using pql::SelectClause;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using std::set;

TEST_CASE("Select Clause should return all entity values", "[SelectClause]") {
    PkbAbstractorStub pkbAbsStub;
    SECTION("select clause should return all stmt design entities (assign/call/if/while/etc) in correct format") {
        // assign a; Select a;
        pkbAbsStub.resultStmtList = {1,2,3};
        QueryDesignEntity assignA(DesignEntity::Assign, "a");
        SelectClause selectA(assignA);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedResult = selectA.getAllEntityCombinations(&pkbAbsStub);
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryArgValue stmt2(DesignEntity::Stmt, "2");
        QueryArgValue stmt3(DesignEntity::Stmt, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> expectedResult = {{pair<QueryDesignEntity, QueryArgValue>(assignA, stmt1)},
                                                                                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt2)},
                                                                                 {pair<QueryDesignEntity, QueryArgValue>(assignA, stmt3)}};
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> expectedSet = set<vector<pair<QueryDesignEntity, QueryArgValue>>>(expectedResult.begin(), expectedResult.end());
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet = set<vector<pair<QueryDesignEntity, QueryArgValue>>>(obtainedResult.begin(), obtainedResult.end());

        REQUIRE(expectedSet == obtainedSet);
    }

    SECTION("select clause should return all values (procedure/variables/constants) in correct format") {
        // constant c; Select c

        pkbAbsStub.resultStrList = {"1", "2", "3"};
        QueryDesignEntity assignA(DesignEntity::Constant, "c");
        SelectClause selectC(assignA);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedResult = selectC.getAllEntityCombinations(&pkbAbsStub);
        QueryArgValue constant1(DesignEntity::Constant, "1");
        QueryArgValue constant2(DesignEntity::Constant, "2");
        QueryArgValue constant3(DesignEntity::Constant, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> expectedResult = {{pair<QueryDesignEntity, QueryArgValue>(assignA, constant1)},
                                                                                 {pair<QueryDesignEntity, QueryArgValue>(assignA, constant2)},
                                                                                 {pair<QueryDesignEntity, QueryArgValue>(assignA, constant3)}};
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> expectedSet = set<vector<pair<QueryDesignEntity, QueryArgValue>>>(expectedResult.begin(), expectedResult.end());
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet = set<vector<pair<QueryDesignEntity, QueryArgValue>>>(obtainedResult.begin(), obtainedResult.end());

        REQUIRE(expectedSet == obtainedSet);
    }

    SECTION("select clause should return all stmts in correct format") {
        // stmt s; Select s;
        pkbAbsStub.largestStmtNum = 3;
        QueryDesignEntity stmtS(DesignEntity::Stmt, "s");
        SelectClause selectS(stmtS);
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedResult = selectS.getAllEntityCombinations(&pkbAbsStub);
        QueryArgValue stmt1(DesignEntity::Stmt, "1");
        QueryArgValue stmt2(DesignEntity::Stmt, "2");
        QueryArgValue stmt3(DesignEntity::Stmt, "3");
        vector<vector<pair<QueryDesignEntity, QueryArgValue>>> expectedResult = {{pair<QueryDesignEntity, QueryArgValue>(stmtS, stmt1)},
                                                                                 {pair<QueryDesignEntity, QueryArgValue>(stmtS, stmt2)},
                                                                                 {pair<QueryDesignEntity, QueryArgValue>(stmtS, stmt3)}};
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> expectedSet = set<vector<pair<QueryDesignEntity, QueryArgValue>>>(expectedResult.begin(), expectedResult.end());
        set<vector<pair<QueryDesignEntity, QueryArgValue>>> obtainedSet = set<vector<pair<QueryDesignEntity, QueryArgValue>>>(obtainedResult.begin(), obtainedResult.end());

        REQUIRE(expectedSet == obtainedSet);
    }
}
