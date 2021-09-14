#include "catch.hpp"
#include "pql/QueryPreprocessor/Preprocessor.h"
#include <string>

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
        REQUIRE(expectedQueryObj == obtainedQueryObj);
    }
}