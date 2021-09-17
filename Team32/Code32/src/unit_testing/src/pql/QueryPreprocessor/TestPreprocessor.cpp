#include "catch.hpp"
#include "pql/QueryPreprocessor/Preprocessor.h"
#include "pql/QueryPreprocessor/Query/Clause/SuchThatClause/ParentClause.h"
#include "pql/QueryPreprocessor/Query/Clause/PatternClause/AssignmentPattern.h"

#include <string>
#include <vector>

using pql::DesignEntity;
using pql::Preprocessor;
using pql::Query;
using pql::QueryDesignEntity;
using pql::SelectClause;
using std::string;
using std::vector;

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

    SECTION("should return correct object with filter clauses") {
        vector<string> postfix = { "count" };
        string input = "while w; assign a;\nSelect w such that Parent(w, a) pattern a(_ , _\"count\"_)";
        Preprocessor preprocessor;
        Query obtainedQueryObj = preprocessor.preprocess(input);
        QueryDesignEntity whileW(QueryDesignEntity(DesignEntity::While, "w"));
        QueryDesignEntity assignA(QueryDesignEntity(DesignEntity::Assign, "a"));
        SelectClause selectS(whileW);
        pql::ParentClause parentClause(pql::QueryArg(&whileW, nullptr, false), pql::QueryArg(&assignA, nullptr, false));
        pql::AssignmentPattern assignmentPattern(pql::QueryArg(&assignA, nullptr, false), pql::QueryArg(nullptr, nullptr, true), postfix);
        Query expectedQueryObj(&selectS, {whileW, assignA},{&parentClause, &assignmentPattern});
        REQUIRE(expectedQueryObj == obtainedQueryObj);
    }
}
