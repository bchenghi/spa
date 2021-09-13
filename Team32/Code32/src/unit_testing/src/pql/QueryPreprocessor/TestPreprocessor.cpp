#include "catch.hpp"
#include "pql/QueryPreprocessor/Preprocessor.h"
#include "pql/QueryPreprocessor/Query/Query.h"
#include "pql/QueryPreprocessor/Query/Clause/SelectClause.h"
#include <string>
#include <iostream>

using pql::DesignEntity;
using pql::Preprocessor;
using pql::Query;
using pql::QueryDesignEntity;
using pql::SelectClause;
using std::string;

TEST_CASE("Preprocessor should create correct Query object", "[Preprocessor]") {
    SECTION("should return correct object with no filter clauses") {
        string input = "stmt s;\nSelect s";
        Preprocessor preprocessor;
        Query obtainedQueryObj = preprocessor.preprocess(input);
        QueryDesignEntity stmtS(QueryDesignEntity(DesignEntity::Stmt, "s"));
        SelectClause selectS(stmtS);
        Query expectedQueryObj(&selectS, {stmtS},{});
        std::cout << (obtainedQueryObj.select == expectedQueryObj.select);
        std::cout << (obtainedQueryObj.filterClauseVector == expectedQueryObj.filterClauseVector);
        REQUIRE(expectedQueryObj == obtainedQueryObj);
    }
}