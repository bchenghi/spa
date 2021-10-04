#include "catch.hpp"

#include "pql/QueryPreprocessor/Query/Clause/SelectClause.h"
#include "Stubs/PkbAbstractorStub.cpp"

#include <set>

using clausetest::PkbAbstractorStub;
using pql::SelectClause;
using pql::QueryArgValue;
using pql::QueryDesignEntity;
using std::set;


TEST_CASE("Equality of select clauses", "[SelectClause]") {
    SECTION("Select clause with no entities") {
        SelectClause selectClause({});
        SelectClause selectClause1({});
        REQUIRE(selectClause == selectClause1);
    }

    SECTION("Select clause with more than 1 entities") {
        QueryDesignEntity assignA(DesignEntity::ASSIGN, "a");
        QueryDesignEntity stmtS(DesignEntity::STMT, "s");
        SelectClause selectClause({assignA, stmtS});
        SelectClause selectClause1({assignA, stmtS});
        REQUIRE(selectClause == selectClause1);
    }
}
