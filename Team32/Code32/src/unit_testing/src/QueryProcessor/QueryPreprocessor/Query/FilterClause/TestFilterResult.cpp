#include "catch.hpp"
#include "QueryProcessor/QueryPreprocessor/Query/FilterClause/FilterResult.h"

using pql::DesignEntity;
using pql::FilterResult;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

TEST_CASE("FilterResult", "[filter result]") {
    QueryArgValue result(DesignEntity::Stmt, "10");
    QueryDesignEntity qde(DesignEntity::Stmt, "s");
    std::pair<QueryDesignEntity, QueryArgValue> pair (qde, result);
    FilterResult fr;
    SECTION("should successfully add result to FilterResult") {
        REQUIRE(fr.addResult(qde, result) == true);
    }

    SECTION("should get correct value at index") {
        fr.addResult(qde, result);
        REQUIRE(fr.getEntityValueAtIndex(0) == pair);
    }

    SECTION("should get correct number of results in FilterResult") {
        fr.addResult(qde, result);
        REQUIRE(fr.getSize() == 1);
    }
}
