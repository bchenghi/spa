#include "simple/SourceProcessor/Parser.h"
#include <catch.hpp>
#include "PKB/UseTable.h"
#include "PKB/ModifyTable.h"
#include <stdexcept>
using namespace std;

TEST_CASE("Should parse follow relationship inside container statement") {
    std::string source = "procedure test {\n"
                         "if (x > 1) then {\n"
                         "x = x + 1;\n"
                         "y = y + 1;\n"
                         "} else { \n"
                         "z = z + 1;\n"
                         "k = k + 1;\n"
                         "}\n"
                         "}\n";

            Parser parser;
            parser.parse(source);
}

TEST_CASE("Should parse follow relationship without container") {
    std::string source = "procedure test {\n"
                         "x = x + 1;\n"
                         "y = y + 1;\n"
                         "}";
    Parser parser;
    parser.parse(source);

        LIST_OF_VAR_NAME resUse = UseTable::getStmtUse(1);
        LIST_OF_VAR_NAME expUse = {"x"};

        REQUIRE(resUse == expUse);

        LIST_OF_VAR_NAME resModify = UseTable::getStmtUse(1);
        LIST_OF_VAR_NAME expModify = {"x"};

        REQUIRE(resModify == expModify);
}

TEST_CASE("Should parse follow relationship for container after non-container statement") {
    std::string source = "procedure test {\n"
                         "x = x + 1;\n"
                         "if (x > 1) then {\n"
                         "x = x + 1;\n"
                         "y = y + 1;\n"
                         "} else { \n"
                         "z = z + 1;\n"
                         "k = k + 1;\n"
                         "}\n"
                         "}\n";
        Parser parser;
        parser.parse(source);
}

TEST_CASE("Should parse follow relationship for non-container - container - non-container") {
    std::string source = "procedure test {\n"
                         "x = x + 1;\n"
                         "if (x > 1) then {\n"
                         "x = x + 1;\n"
                         "y = y + 1;\n"
                         "} else { \n"
                         "z = z + 1;\n"
                         "k = k + 1;\n"
                         "}\n"
                         "y = y + 1;\n"
                         "}\n";
                Parser parser;
                parser.parse(source);

}


TEST_CASE("Shouldn't have parent relationship without container statement") {
    std::string source = "procedure test {\n"
                         "x = x + 1;\n"
                         "y = y + 1;\n"
                         "}";
                        Parser parser;
                        parser.parse(source);
}

TEST_CASE("Should parse parent relationship for nested container statement") {
    std::string source = "procedure test {\n"
                         "while (x>1) {\n"
                         "x = x + 1;\n"
                         "if (x < 100) then {\n"
                         "y = y + 1;\n"
                         "} else {\n"
                         "z = z + 1;\n"
                         "}\n"
                         "}\n"
                         "}\n";
                        Parser parser;
                        parser.parse(source);

}

TEST_CASE("Should parse parent relationship for single container statement") {

}


TEST_CASE("Parser can detect invalid brace") {
    std::string source = "procedure test {\n"
                         "while (x>1) {\n"
                         "x = x + 1;\n"
                         "if (x < 100) then {\n"
                         "y = y + 1;\n"
                         "} else {\n"
                         "z = z + 1;\n"
                         "}\n"
                         "}\n"
                         "}}\n";

    Parser parser;
    REQUIRE_THROWS(parser.parse(source));

}

TEST_CASE("Parser can detect invalid bracket") {
    std::string source = "procedure test {\n"
                         "while (x>1)) {\n"
                         "y = 100;\n"
                         "x = x + 1;\n"
                         "if (x < 100) then {\n"
                         "y = y + 1;\n"
                         "} else {\n"
                         "z = z + 1;\n"
                         "}\n"
                         "}\n"
                         "}}\n";

    Parser parser;
    REQUIRE_THROWS(parser.parse(source));
}

TEST_CASE("Parser can detect invalid variable definition") {
    std::string source = "procedure test {\n"
                         "while (x>1) {\n"
                         "1_x = x + 1;\n"
                         "if (x < 100) then {\n"
                         "y = y + 1;\n"
                         "} else {\n"
                         "z = z + 1;\n"
                         "}\n"
                         "}\n"
                         "}}\n";

    Parser parser;
    REQUIRE_THROWS(parser.parse(source));
}