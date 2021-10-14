#include "catch.hpp"

#include "pql/AttributeType.h"
#include "pql/DesignEntity.h"
#include "pql/QueryPreprocessor/Query/QueryDesignEntity.h"

using pql::AttributeType;
using pql::DesignEntity;
using pql::QueryDesignEntity;

TEST_CASE("Ensure error is thrown when attribute type is invalid for design entity", "[QueryDesignEntity]") {
    SECTION("Check for invalid entity when attribute type is stmt num") {
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::CONSTANT, "name", AttributeType::STMT_NUM});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PROCEDURE, "name", AttributeType::STMT_NUM});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PROGRAM_LINE, "name", AttributeType::STMT_NUM});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::VARIABLE, "name", AttributeType::STMT_NUM});
    }

    SECTION("Check for valid entity when attribute type is stmt num") {
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::STMT, "name", AttributeType::STMT_NUM});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::READ, "name", AttributeType::STMT_NUM});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::PRINT, "name", AttributeType::STMT_NUM});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::CALL, "name", AttributeType::STMT_NUM});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::WHILE, "name", AttributeType::STMT_NUM});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::IF, "name", AttributeType::STMT_NUM});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::ASSIGN, "name", AttributeType::STMT_NUM});
    }

    SECTION("Check for invalid entity when attribute type is variable") {
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::ASSIGN, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::CALL, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::CONSTANT, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::IF, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PROCEDURE, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PROGRAM_LINE, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::STMT, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::WHILE, "name", AttributeType::VARIABLE_NAME});
    }

    SECTION("Check for valid entity when attribute type is variable") {
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::VARIABLE, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::READ, "name", AttributeType::VARIABLE_NAME});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::PRINT, "name", AttributeType::VARIABLE_NAME});
    }

    SECTION("Check for invalid entity when attribute type is procedure") {
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::ASSIGN, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::CONSTANT, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::IF, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PRINT, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PROGRAM_LINE, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::READ, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::STMT, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::VARIABLE, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::WHILE, "name", AttributeType::PROCEDURE_NAME});
    }

    SECTION("Check for valid entity when attribute type is procedure") {
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::PROCEDURE, "name", AttributeType::PROCEDURE_NAME});
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::CALL, "name", AttributeType::PROCEDURE_NAME});
    }

    SECTION("Check for invalid entity when attribute type is value") {
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::ASSIGN, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::CALL, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::IF, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PRINT, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PROCEDURE, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::PROGRAM_LINE, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::READ, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::STMT, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::VARIABLE, "name", AttributeType::VALUE});
        REQUIRE_THROWS(QueryDesignEntity{DesignEntity::WHILE, "name", AttributeType::VALUE});
    }

    SECTION("Check for valid entity when attribute type is value") {
        REQUIRE_NOTHROW(QueryDesignEntity{DesignEntity::CONSTANT, "name", AttributeType::VALUE});
    }
}