//
// Created by Jerry Lin on 12/9/21.
//
#include "simple/SourceProcessor/Parser.h"
#include <catch.hpp>

TEST_CASE("Parser can parse Follow Relationship", "[Parser]") {
    SECTION("Should parse follow relationship without container") {
        std::string source = "procedure test {\n"
                                "x = x + 1;\n"
                                "y = y + 1;\n"
                                "}";
    }

    SECTION("Should parse follow relationship inside container statement") {
        std::string source = "procedure test {\n"
                             "if (x > 1) then {\n"
                             "x = x + 1;\n"
                             "y = y + 1;\n"
                             "}\n else { \n"
                             "z = z + 1;\n"
                             "k = k + 1;\n"
                             "}\n";
    }

    SECTION("Should parse follow relationship for container after non-container statement") {

    }

    SECTION("Should parse follow relationship for non-container - container - non-container") {

    }
}

TEST_CASE("Parser can parse Parent Relationship", "[Parser]") {
    SECTION("Shouldn't have parent relationship without container statement") {

    }

    SECTION("Should parse parent relationship for single container statement") {

    }

    SECTION("Should parse parent relationship for nested container statement") {

    }
}

TEST_CASE("Parser can detect invalid syntax") {

}
