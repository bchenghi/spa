#include <catch.hpp>
#include <PKB/CallStmtTable.h>

#include "PKB/CallTable.h"
#include "PKB/IfControlTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/UseTable.h"
#include "PKB/WhileControlTable.h"
#include "simple/SourceProcessor/DesignExtractor.h"
#include "simple/SourceProcessor/Parser.h"
#include "Utils/TestUtils.h"

typedef unordered_map<StmtNo, StmtNo> FollowType;
typedef unordered_map<StmtNo, ListOfStmtNos> FollowStarType, ParentStarType, ParentType;
typedef unordered_map<StmtNo, ListOfVarNames> UseStmtType, ModifyStmtType, WhileControlType, IfControlType;
typedef unordered_map<ProcName, ListOfVarNames> UseProcType, ModifyProcType;
typedef unordered_map<ProcName, ListOfProcNames> CallType;

TEST_CASE("While loop inside else block") {
    clearPKB();

    std::string source = "procedure test {\n"
                         "    x = 1;\n"
                         "    if (x > 1) then {\n"
                         "        y = 2;\n"
                         "        z = 3;\n"
                         "    } else {\n"
                         "        while (x > 1) {\n"
                         "            x = x + 1;\n"
                         "            z = 4;\n"
                         "        }\n"
                         "    }\n"
                         "}";
    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();

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
        UseStmtType resUseTable = UseTable::getStmtUseMap();
        UseStmtType expectedUseTable = {
                {2, {"x"}},
                {5, {"x"}},
                {6, {"x"}}
        };
        REQUIRE(resUseTable == expectedUseTable);
    }

    SECTION("Check Modify Table") {
        ModifyStmtType resModifyTable = ModifyTable::getStmtModifyMap();
        ModifyStmtType expectedModifyTable = {
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

    SECTION("Check CallsTable") {
        CallType resCallTable = CallTable::getCallMap();
        CallType expectedCallTable = {};
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallsTTable") {
        CallType resCallTable = CallTable::getCallStarMap();
        CallType expectedCallTable = {};
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallStmtTable") {
        std::unordered_map<StmtNo, ProcName> resCallStmtTable = CallStmtTable::getCallStmtToProcMap();
        std::unordered_map<StmtNo, ProcName> expectedCallStmtTable = {};
        std::unordered_map<ProcName, ListOfStmtNos> resProcTable = CallStmtTable::getProcToCallStmtsMap();
        std::unordered_map<ProcName, ListOfStmtNos> expectedProcTable = {};
        REQUIRE(resCallStmtTable == expectedCallStmtTable);
        REQUIRE(resProcTable == expectedProcTable);
    }

    SECTION("Check IfControlTable") {
        IfControlType resIfControlTable = IfControlTable::getIfToVarListMap();
        IfControlType expectedIfControlTable = {
                {2, {"x"}}
        };
        REQUIRE(resIfControlTable == expectedIfControlTable);
    }

    SECTION("Check WhileControlTable") {
        WhileControlType resWhileControlTable = WhileControlTable::getWhileToVarListMap();
        WhileControlType expectedWhileControlTable = {
                {5, {"x"}}
        };
        REQUIRE(resWhileControlTable == expectedWhileControlTable);
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
        UseStmtType resUseTable = UseTable::getStmtUseMap();
        UseStmtType expectedUseTable = {
                {3, {"y", "x", "z"}},
                {4, {"x"}},
                {5, {"x"}},
                {8, {"z"}}
        };
        REQUIRE(resUseTable == expectedUseTable);
    }

    SECTION("Check Modify Table") {
        ModifyStmtType resModifyTable = ModifyTable::getStmtModifyMap();
        ModifyStmtType expectedModifyTable = {
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

    SECTION("Check CallsTable") {
        CallType resCallTable = CallTable::getCallMap();
        CallType expectedCallTable = {};
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallsTTable") {
        CallType resCallTable = CallTable::getCallStarMap();
        CallType expectedCallTable = {};
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallStmtTable") {
        std::unordered_map<StmtNo, ProcName> resCallStmtTable = CallStmtTable::getCallStmtToProcMap();
        std::unordered_map<StmtNo, ProcName> expectedCallStmtTable = {};
        std::unordered_map<ProcName, ListOfStmtNos> resProcTable = CallStmtTable::getProcToCallStmtsMap();
        std::unordered_map<ProcName, ListOfStmtNos> expectedProcTable = {};
        REQUIRE(resCallStmtTable == expectedCallStmtTable);
        REQUIRE(resProcTable == expectedProcTable);
    }

    SECTION("Check IfControlTable") {
        IfControlType resIfControlTable = IfControlTable::getIfToVarListMap();
        IfControlType expectedIfControlTable = {
                {3, {"y"}}
        };
        REQUIRE(resIfControlTable == expectedIfControlTable);
    }

    SECTION("Check WhileControlTable") {
        WhileControlType resWhileControlTable = WhileControlTable::getWhileToVarListMap();
        WhileControlType expectedWhileControlTable = {
                {4, {"x"}}
        };
        REQUIRE(resWhileControlTable == expectedWhileControlTable);
    }
}

TEST_CASE("Nested loop inside if block and statement after nested if statement") {
    clearPKB();
    std::string source = "procedure test {\n"
                         "\tx = 1;\n"
                         "\ty = 2;\n"
                         "\n"
                         "\tif (x > k) then {\n"
                         "\t\ty = y + 1;\n"
                         "\n"
                         "\t\tif (y > z) then {\n"
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
                         "\tif (1 == 1) then { } else { }\n"
                         "}";
    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();

    SECTION("Check FollowTTable") {
        FollowStarType resFollowTTable = FollowTable::getFollowStarMap();
        FollowStarType expectedFollowTTable = {
                {1, {2, 3, 12, 13}},
                {2, {3, 12, 13}},
                {3, {12, 13}},
                {4, {5, 9}},
                {5, {9}},
                {10, {11}},
                {12, {13}}
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
                {13, {}}
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
                {10, 11},
                {12, 13}
        };
        REQUIRE(resFollowTable == expectedFollowTable);
    }

    SECTION("Check Use Table") {
        UseStmtType resUseTable = UseTable::getStmtUseMap();
        UseStmtType expectedUseTable = {
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
        ModifyStmtType resModifyTable = ModifyTable::getStmtModifyMap();
        ModifyStmtType expectedModifyTable = {
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

    SECTION("Check CallsTable") {
        CallType resCallTable = CallTable::getCallMap();
        CallType expectedCallTable = {};
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallsTTable") {
        CallType resCallTable = CallTable::getCallStarMap();
        CallType expectedCallTable = {};
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallStmtTable") {
        std::unordered_map<StmtNo, ProcName> resCallStmtTable = CallStmtTable::getCallStmtToProcMap();
        std::unordered_map<StmtNo, ProcName> expectedCallStmtTable = {};
        std::unordered_map<ProcName, ListOfStmtNos> resProcTable = CallStmtTable::getProcToCallStmtsMap();
        std::unordered_map<ProcName, ListOfStmtNos> expectedProcTable = {};
        REQUIRE(resCallStmtTable == expectedCallStmtTable);
        REQUIRE(resProcTable == expectedProcTable);
    }

    SECTION("Check IfControlTable") {
        IfControlType resIfControlTable = IfControlTable::getIfToVarListMap();
        IfControlType expectedIfControlTable = {
                {3, {"x", "k"}},
                {5, {"y", "z"}}
        };
        REQUIRE(resIfControlTable == expectedIfControlTable);
    }

    SECTION("Check WhileControlTable") {
        WhileControlType resWhileControlTable = WhileControlTable::getWhileToVarListMap();
        WhileControlType expectedWhileControlTable = {
                {7, {"z"}}
        };
        REQUIRE(resWhileControlTable == expectedWhileControlTable);
    }
}

// TODO: uncomment assertions once call statements and their container statements are set with their proper relationships
TEST_CASE("Multiple procedures") {
    clearPKB();
    std::string source = "procedure First {\n"
                         "    read x;\n"
                         "    read z;\n"
                         "    call Second;\n"
                         "}\n"
                         "\n"
                         "procedure Second {\n"
                         "    x = 0;\n"
                         "    i = 5;\n"
                         "    while (i!=0) {\n"
                         "        x = x + 2 * y;\n"
                         "        call Third;\n"
                         "        i = i - 1;\n"
                         "    }\n"
                         "    if (x==1) then {\n"
                         "        x = x + 1;\n"
                         "    } else {\n"
                         "        z = 1;\n"
                         "    }\n"
                         "    z = z + x + i;\n"
                         "    y = z + 2;\n"
                         "    x = x * y + z;\n"
                         "}\n"
                         "\n"
                         "procedure Third {\n"
                         "    z = 5;\n"
                         "    v = z;\n"
                         "    print v;\n"
                         "}";
    Parser parser;
    parser.parse(source);

    DesignExtractor designExtractor;
    designExtractor.extractDesign();

    SECTION("Check FollowTTable") {
        FollowStarType resFollowTTable = FollowTable::getFollowStarMap();
        FollowStarType expectedFollowTTable = {
                {1, {2, 3}},
                {2, {3}},
                {4, {5, 6, 10, 13, 14, 15}},
                {5, {6, 10, 13, 14, 15}},
                {6, {10, 13, 14, 15}},
                {7, {8, 9}},
                {8, {9}},
                {10, {13, 14, 15}},
                {13, {14, 15}},
                {14, {15}},
                {16, {17, 18}},
                {17, {18}}
        };

        REQUIRE(resFollowTTable == expectedFollowTTable);
    }

    SECTION("Check ParentTTable") {
        ParentStarType resParentTTable = ParentTable::getParentStarMap();
        ParentStarType expectedParentTTable = {
                {6, {7, 8, 9}},
                {10, {11, 12}}
        };
        REQUIRE(resParentTTable == expectedParentTTable);
    }


    SECTION("Check ParentTable") {
        ParentType resParentTable = ParentTable::getParentMap();
        ParentType expectedParentTable = {
                {6, {7, 8, 9}},
                {10, {11, 12}}
        };
        REQUIRE(resParentTable == expectedParentTable);
    }

    SECTION("Check FollowTable") {
        FollowType resFollowTable = FollowTable::getFollowMap();
        FollowType expectedFollowTable = {
                {1, 2},
                {2, 3},
                {4, 5},
                {5, 6},
                {6, 10},
                {10, 13},
                {13, 14},
                {14, 15},
                {16, 17},
                {17, 18},
                {7, 8},
                {8, 9},
        };
        REQUIRE(resFollowTable == expectedFollowTable);
    }

    SECTION("Check Use Table") {
        UseStmtType resStmtUseTable = UseTable::getStmtUseMap();
        UseStmtType expectedStmtUseTable = {
                {3, {"i", "x", "y", "z", "v"}},
                {6, {"i", "x", "y", "z", "v"}},
                {7, {"x", "y"}},
                {8, {"z", "v"}},
                {9, {"i"}},
                {10, {"x"}},
                {11, {"x"}},
                {13, {"z", "x", "i"}},
                {14, {"z"}},
                {15, {"x", "y", "z"}},
                {17, {"z"}},
                {18, {"v"}}
        };
        UseProcType resProcUseTable = UseTable::getProcUseMap();
        UseProcType expectedProcUseTable = {
                {"First", {"i", "x", "y", "z", "v"}},
                {"Second", {"i", "x", "y", "z", "v"}},
                {"Third", {"z", "v"}}
        };
        REQUIRE(resStmtUseTable == expectedStmtUseTable);
        REQUIRE(resProcUseTable == expectedProcUseTable);
    }

    SECTION("Check Modify Table") {
        ModifyStmtType resStmtModifyTable = ModifyTable::getStmtModifyMap();
        ModifyStmtType expectedStmtModifyTable = {
                {1, {"x"}},
                {2, {"z"}},
                {3, {"x", "i", "z", "v", "y"}},
                {4, {"x"}},
                {5, {"i"}},
                {6, {"x", "z", "v", "i"}},
                {7, {"x"}},
                {8, {"z", "v"}},
                {9, {"i"}},
                {10, {"x", "z"}},
                {11, {"x"}},
                {12, {"z"}},
                {13, {"z"}},
                {14, {"y"}},
                {15, {"x"}},
                {16, {"z"}},
                {17, {"v"}},
        };
        ModifyProcType resProcModifyTable = ModifyTable::getProcModifyMap();
        ModifyProcType expectedProcModifyTable = {
                {"First", {"x", "i", "z", "v", "y"}},
                {"Second", {"x", "i", "z", "v", "y"}},
                {"Third", {"z", "v"}}
        };
        REQUIRE(resStmtModifyTable == expectedStmtModifyTable);
        REQUIRE(resProcModifyTable == expectedProcModifyTable);
    }

    SECTION("Check CallsTable") {
        CallType resCallTable = CallTable::getCallMap();
        CallType expectedCallTable = {
                {"First", {"Second"}},
                {"Second", {"Third"}}
        };
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallsTTable") {
        CallType resCallTable = CallTable::getCallStarMap();
        CallType expectedCallTable = {
                {"First", {"Second", "Third"}},
                {"Second", {"Third"}}
        };
        REQUIRE(resCallTable == expectedCallTable);
    }

    SECTION("Check CallStmtTable") {
        std::unordered_map<StmtNo, ProcName> resCallStmtTable = CallStmtTable::getCallStmtToProcMap();
        std::unordered_map<StmtNo, ProcName> expectedCallStmtTable = {
                {3, "Second"},
                {8, "Third"}
        };
        std::unordered_map<ProcName, ListOfStmtNos> resProcTable = CallStmtTable::getProcToCallStmtsMap();
        std::unordered_map<ProcName, ListOfStmtNos> expectedProcTable = {
                {"Second", {3}},
                {"Third", {8}}
        };
        REQUIRE(resCallStmtTable == expectedCallStmtTable);
        REQUIRE(resProcTable == expectedProcTable);
    }

    SECTION("Check IfControlTable") {
        IfControlType resIfControlTable = IfControlTable::getIfToVarListMap();
        IfControlType expectedIfControlTable = {
                {10, {"x"}}
        };
        REQUIRE(resIfControlTable == expectedIfControlTable);
    }

    SECTION("Check WhileControlTable") {
        WhileControlType resWhileControlTable = WhileControlTable::getWhileToVarListMap();
        WhileControlType expectedWhileControlTable = {
                {6, {"i"}}
        };
        REQUIRE(resWhileControlTable == expectedWhileControlTable);
    }
}
