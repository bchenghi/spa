//
// Created by Jerry Lin on 15/9/21.
//
#include <catch.hpp>
#include <simple/SourceProcessor/Parser.h>
#include <simple/SourceProcessor/DesignExtractor.h>
#include <PKB/UseTable.h>

TEST_CASE("While loop inside else block") {
    std::string source = "procedure test {\n"
                         "x = 1;\n"
                         "if (x > 1) then {\n"
                         "y = 2;\n"
                         "z = 3;\n"
                         "} else {\n"
                         "while (x > 1) {\n"
                         "x = x + 1;\n"
                         "z = 4;\n"
                         "}\n"
                         "}\n"
                         "}";
    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();

    unordered_map<size_t, size_t> expectedFollowTable = {
            {1, 2},
            {3, 4},
            {6, 7}
    };
    unordered_map<size_t, size_t> resFollowTable = FollowTable::getFollowMap();
    REQUIRE(resFollowTable == expectedFollowTable);

    unordered_map<size_t, unordered_set<STMT_NO>> expectedParentTable = {
            {2, {3, 4, 5}},
            {5, {6, 7}}
    };
    unordered_map<size_t, unordered_set<STMT_NO>> resParentTable = ParentTable::getParentMap();

    REQUIRE(resParentTable == expectedParentTable);

    unordered_map<STMT_NO, LIST_OF_STMT_NO> expectedFollowTTable = {
            {1, {3}},
            {3, {4}},
    };
}

TEST_CASE("Nested loop inside if block") {
    std::string source = "procedure test {\n"
                         "\tx = 1;\n"
                         "\ty = 2;\n"
                         "\n"
                         "\tif (x > 0) then {\n"
                         "\t\ty = y + 1;\n"
                         "\n"
                         "\t\tif (y > 2) then {\n"
                         "\t\t\tz = 1;\n"
                         "\t\t} else {\n"
                         "\t\t\twhile (z < 100) {\n"
                         "\t\t\t\tz = z + 1;\n"
                         "\t\t\t}\n"
                         "\t\t}\n"
                         "\t} else {\n"
                         "\t\tk = 1;\n"
                         "\t\tk = k + 1;\n"
                         "\t}\n"
                         "\tz = 10;\n"
                         "}";
    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();
}

TEST_CASE("While loop in if block") {
    std::string source = "procedure test {\n"
                         "\tx = 1;\n"
                         "\ty = 1;\n"
                         "\n"
                         "\tif (y == 1) then {\n"
                         "\t\twhile (x < 10) {\n"
                         "\t\t\tx = x + 1;\n"
                         "\t\t\tk = 3;\n"
                         "\t\t}\n"
                         "\t} else {\n"
                         "\t\tz = 3;\n"
                         "\t\tz = z + 1;\n"
                         "\t}\n"
                         "}";

    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();

}

TEST_CASE("Nested loop inside if block and statement after nested if statement") {
    std::string source = "procedure test {\n"
                         "\tx = 1;\n"
                         "\ty = 2;\n"
                         "\n"
                         "\tif (x > 0) then {\n"
                         "\t\ty = y + 1;\n"
                         "\n"
                         "\t\tif (y > 2) then {\n"
                         "\t\t\tz = 1;\n"
                         "\t\t} else {\n"
                         "\t\t\twhile (z < 100) {\n"
                         "\t\t\t\tz = z + 1;\n"
                         "\t\t\t}\n"
                         "\t\t}\n"
                         "z = 3;\n"
                         "\t} else {\n"
                         "\t\tk = 1;\n"
                         "\t\tk = k + 1;\n"
                         "\t}\n"
                         "\tz = 10;\n"
                         "}";
    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();
}

TEST_CASE("While loop contains an if block") {
    std::string source = "procedure test {\n"
                         "\tx = 1;\n"
                         "\twhile (x < 10) {\n"
                         "\t\tx = x + 1;\n"
                         "\n"
                         "\t\tif (x > 5) then {\n"
                         "\t\t\ty = 1;\n"
                         "\t\t} else {\n"
                         "\t\t\tk = 1;\n"
                         "\t\t}\n"
                         "\t}\n"
                         "}";

    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();
}