#include "catch.hpp"

#include "simple/SourceProcessor/Parser.h"
#include "Utils/TestUtils.h"
TEST_CASE("Test CFG without dummy node") {
    clearPKB();
    string source = "procedure A {\n"
                    "\tx = x + 1;\n"
                    "\ty = 3;\n"
                    "\tz = 4;\n"
                    "}";

    Parser parser;
    parser.parse(source);

    Graph cfg = parser.getCFG();
    Graph expCfg = {{0, 1, 0},
                    {0, 0, 1},
                    {0, 0, 0}};

    REQUIRE(cfg == expCfg);
}

TEST_CASE("Test CFG with ending dummy node") {
    clearPKB();
    string source = "procedure A {\n"
                    "\tx = x + 1;\n"
                    "\tif (x == 1) then {\n"
                    "\t\tx = x + 1;\n"
                    "\t} else {\n"
                    "\t\tz = 4;\n"
                    "\t}\n"
                    "}";
    Parser parser;
    parser.parse(source);

    Graph cfg = parser.getCFG();
    Graph expCfg = {{0, 1, 0, 0, 0},
                    {0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 1},
                    {0, 0, 0, 0, 1},
                    {0, 0, 0, 0, 0}};

    REQUIRE(cfg == expCfg);
}

TEST_CASE("Test for while loop") {
    clearPKB();
    string source = "procedure A {\n"
                    "\tx = x + 1;\n"
                    "\twhile (x < 1) {\n"
                    "\t\tx = x + 1;\n"
                    "\t}\n"
                    "}";

    Parser parser;
    parser.parse(source);

    Graph cfg = parser.getCFG();
    Graph expCfg = {{0, 1, 0},
                    {0, 0, 1},
                    {0, 1, 0},};

    REQUIRE(cfg == expCfg);
}