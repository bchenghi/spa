#include <catch.hpp>

#include "PKB/ModifyTable.h"
#include "PKB/UseTable.h"
#include "simple/SourceProcessor/DesignExtractor.h"
#include "simple/SourceProcessor/Parser.h"
#include "Utils/TestUtils.h"

typedef unordered_map<StmtNo, StmtNo> FollowType;
typedef unordered_map<StmtNo, ListOfStmtNos> FollowStarType, ParentStarType, ParentType;
typedef unordered_map<StmtNo, ListOfVarNames> UseType, ModifyType;

TEST_CASE("While loop inside else block") {
    SECTION("Parsing the statement and extract design") {
        clearPKB();

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
    }

    SECTION("Check FollowTTable") {
        FollowStarType resFollowTTable = FollowTable::getFollowStarMap();
        FollowStarType expectedFollowTTable = {
                {1, {2}},
                {3, {4}},
                {6, {7}},
        };

        REQUIRE(resFollowTTable == expectedFollowTTable);
    }

    SECTION("Check ParentTTable") {
        ParentStarType resParentTTable = ParentTable::getParentStarMap();
        ParentStarType expectedParentTTable = {
                {2, {3, 4, 5, 6, 7}},
                {5, {6, 7}},
        };
        REQUIRE(resParentTTable == expectedParentTTable);
    }


    SECTION("Check ParentTable") {
        ParentType resParentTable = ParentTable::getParentMap();
        ParentType expectedParentTable = {
                {2, {3, 4, 5}},
                {5, {6, 7}}
        };
        REQUIRE(resParentTable == expectedParentTable);
    }

    SECTION("Check FollowTable") {
        FollowType resFollowTable = FollowTable::getFollowMap();
        FollowType expectedFollowTable = {
                {1, 2},
                {3, 4},
                {6, 7}
        };
        REQUIRE(resFollowTable == expectedFollowTable);
    }

    SECTION("Check Use Table") {
        UseType resUseTable = UseTable::getStmtUseMap();
        UseType expectedUseTable = {
                {2, {"x"}},
                {5, {"x"}},
                {6, {"x"}}
        };
        REQUIRE(resUseTable == expectedUseTable);
    }

    SECTION("Check Modify Table") {
        ModifyType resModifyTable = ModifyTable::getStmtModifyMap();
        ModifyType expectedModifyTable = {
                {1, {"x"}},
                {2, {"x", "y", "z"}},
                {3, {"y"}},
                {4, {"z"}},
                {5, {"x", "z"}},
                {6, {"x"}},
                {7, {"z"}}
        };
        REQUIRE(resModifyTable == expectedModifyTable);
    }
}

TEST_CASE("Nested loop inside if block") {
    clearPKB();
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
    SECTION("Parse and Extract Design") {
        clearPKB();
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

    SECTION("Check FollowTTable") {
        FollowStarType resFollowTTable = FollowTable::getFollowStarMap();
        FollowStarType expectedFollowTTable = {
                {1, {2, 3}},
                {2, {3}},
                {5, {6}},
                {7, {8}}
        };

        REQUIRE(resFollowTTable == expectedFollowTTable);
    }

    SECTION("Check ParentTTable") {
        ParentStarType resParentTTable = ParentTable::getParentStarMap();
        ParentStarType expectedParentTTable = {
                {3, {4, 5, 6, 7, 8}},
                {4, {5, 6}},
        };
        REQUIRE(resParentTTable == expectedParentTTable);
    }


    SECTION("Check ParentTable") {
        ParentType resParentTable = ParentTable::getParentMap();
        ParentType expectedParentTable = {
                {3, {4, 7, 8}},
                {4, {5, 6}}
        };
        REQUIRE(resParentTable == expectedParentTable);
    }

    SECTION("Check FollowTable") {
        FollowType resFollowTable = FollowTable::getFollowMap();
        FollowType expectedFollowTable = {
                {1, 2},
                {2, 3},
                {5, 6},
                {7, 8}
        };
        REQUIRE(resFollowTable == expectedFollowTable);
    }

    SECTION("Check Use Table") {
        UseType resUseTable = UseTable::getStmtUseMap();
        UseType expectedUseTable = {
                {3, {"y", "x", "z"}},
                {4, {"x"}},
                {5, {"x"}},
                {8, {"z"}}
        };
        REQUIRE(resUseTable == expectedUseTable);
    }

    SECTION("Check Modify Table") {
        ModifyType resModifyTable = ModifyTable::getStmtModifyMap();
        ModifyType expectedModifyTable = {
                {1, {"x"}},
                {2, {"y"}},
                {3, {"x", "k", "z"}},
                {4, {"x", "k"}},
                {5, {"x"}},
                {6, {"k"}},
                {7, {"z"}},
                {8, {"z"}}
        };
        REQUIRE(resModifyTable == expectedModifyTable);
    }
}

TEST_CASE("Nested loop inside if block and statement after nested if statement") {
    SECTION("Parse and Extract Design") {
        clearPKB();
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


    SECTION("Check FollowTTable") {
        FollowStarType resFollowTTable = FollowTable::getFollowStarMap();
        FollowStarType expectedFollowTTable = {
                {1, {2, 3, 12}},
                {2, {3, 12}},
                {3, {12}},
                {4, {5, 9}},
                {5, {9}},
                {10, {11}}
        };

        REQUIRE(resFollowTTable == expectedFollowTTable);
    }

    SECTION("Check ParentTTable") {
        ParentStarType resParentTTable = ParentTable::getParentStarMap();
        ParentStarType expectedParentTTable = {
                {3, {4, 5, 6, 7, 8, 9, 10, 11}},
                {5, {6, 7, 8}},
                {7, {8}}
        };
        REQUIRE(resParentTTable == expectedParentTTable);
    }


    SECTION("Check ParentTable") {
        ParentType resParentTable = ParentTable::getParentMap();
        ParentType expectedParentTable = {
                {3, {4, 5, 9, 10, 11}},
                {5, {6, 7}},
                {7, {8}},
        };
        REQUIRE(resParentTable == expectedParentTable);
    }

    SECTION("Check FollowTable") {
        FollowType resFollowTable = FollowTable::getFollowMap();
        FollowType expectedFollowTable = {
                {1, 2},
                {2, 3},
                {3, 12},
                {4, 5},
                {5, 9},
                {10, 11}
        };
        REQUIRE(resFollowTable == expectedFollowTable);
    }

    SECTION("Check Use Table") {
        UseType resUseTable = UseTable::getStmtUseMap();
        UseType expectedUseTable = {
                {3, {"y", "x", "z", "k"}},
                {4, {"y"}},
                {5, {"y", "z"}},
                {7, {"z"}},
                {8, {"z"}},
                {11, {"k"}}
        };
        REQUIRE(resUseTable == expectedUseTable);
    }

    SECTION("Check Modify Table") {
        ModifyType resModifyTable = ModifyTable::getStmtModifyMap();
        ModifyType expectedModifyTable = {
                {1, {"x"}},
                {2, {"y"}},
                {3, {"k", "z", "y"}},
                {4, {"y"}},
                {5, {"z"}},
                {6, {"z"}},
                {7, {"z"}},
                {8, {"z"}},
                {9, {"z"}},
                {10, {"k"}},
                {11, {"k"}},
                {12, {"z"}}
        };
        REQUIRE(resModifyTable == expectedModifyTable);
    }
}
