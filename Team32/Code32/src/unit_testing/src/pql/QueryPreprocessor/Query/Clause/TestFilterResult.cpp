#include "catch.hpp"

#include "pql/QueryPreprocessor/Query/Clause/FilterResult.h"

using pql::DesignEntity;
using pql::FilterResult;
using pql::QueryArgValue;
using pql::QueryDesignEntity;

TEST_CASE("FilterResult", "[filter result]") {
    QueryArgValue value(DesignEntity::STMT, "10");
    QueryDesignEntity qde(DesignEntity::STMT, "s");
    std::pair<QueryDesignEntity, QueryArgValue> p (qde, value);
    std::vector<std::pair<QueryDesignEntity, QueryArgValue>> result = {p};
    FilterResult fr({}, false);

    SECTION("should successfully add result to FilterResult") {
        REQUIRE(fr.addResult(result) == true);
    }

    SECTION("should get correct value at index") {
        fr.addResult(result);
        REQUIRE(fr.getEntitiesAndValuesAtIndex(0) == result);
    }

    SECTION("should get correct number of results in FilterResult") {
        fr.addResult(result);
        REQUIRE(fr.getSize() == 1);
    }
}
