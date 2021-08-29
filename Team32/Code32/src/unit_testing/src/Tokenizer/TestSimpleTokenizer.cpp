#include "catch.hpp"
#include "Tokenizer/SimpleTokenizer.h"

#include <string>
#include <vector>

using simple::SimpleToken;
using simple::SimpleTokenizer;
using simple::TokenType;
using std::logic_error;
using std::string;
using std::vector;

TEST_CASE("SimpleTokenizer", "[simple]") {
    SECTION("should tokenize simple query") {
        string source = "procedure computeCentroid {\n"
                        "    count = 0;\n"
                        "    cenX = 0;\n"
                        "    cenY = 0;\n"
                        "    call readPoint;\n"
                        "\n"
                        "    while ((x != 0) && (y != 0)) {\n"
                        "        count = count + 1;\n"
                        "        cenX = cenX + x;\n"
                        "        cenY = cenY + y;\n"
                        "        call readPoint;\n"
                        "    }\n"
                        "\n"
                        "    if (count == 0) then {\n"
                        "        flag = 1;\n"
                        "    } else {\n"
                        "        cenX = cenX / count;\n"
                        "        cenY = cenY / count;\n"
                        "    }\n"
                        "\n"
                        "    normSq = cenX * cenX + cenY * cenY;\n"
                        "}\n"
                        "\n"
                        "procedure main {\n"
                        "    flag = 0;\n"
                        "    call computeCentroid;\n"
                        "    call printResults;\n"
                        "}\n"
                        "\n"
                        "procedure readPoint{\n"
                        "    read x;\n"
                        "    read y;\n"
                        "}\n"
                        "\n"
                        "procedure printResults{\n"
                        "    print flag;\n"
                        "    print cenX;\n"
                        "    print cenY;\n"
                        "    print normSq;\n"
                        "}";
        vector<SimpleToken> tokens = SimpleTokenizer::tokenize(source);
        vector<SimpleToken> expected = {
                SimpleToken(TokenType::kKeyWord, "procedure", 1),
                SimpleToken(TokenType::kIdentifier, "computeCentroid", 1),
                SimpleToken(TokenType::kOpenBrace, "{", 1),
                SimpleToken(TokenType::kIdentifier, "count", 2),
                SimpleToken(TokenType::kAssignment, "=", 2),
                SimpleToken(TokenType::kConstant, "0", 2),
                SimpleToken(TokenType::kStatementEnd, ";", 2),
                SimpleToken(TokenType::kIdentifier, "cenX", 3),
                SimpleToken(TokenType::kAssignment, "=", 3),
                SimpleToken(TokenType::kConstant, "0", 3),
                SimpleToken(TokenType::kStatementEnd, ";", 3),
                SimpleToken(TokenType::kIdentifier, "cenY", 4),
                SimpleToken(TokenType::kAssignment, "=", 4),
                SimpleToken(TokenType::kConstant, "0", 4),
                SimpleToken(TokenType::kStatementEnd, ";", 4),
                SimpleToken(TokenType::kKeyWord, "call", 5),
                SimpleToken(TokenType::kIdentifier, "readPoint", 5),
                SimpleToken(TokenType::kStatementEnd, ";", 5),
                SimpleToken(TokenType::kKeyWord, "while", 7),
                SimpleToken(TokenType::kOpenBracket, "(", 7),
                SimpleToken(TokenType::kOpenBracket, "(", 7),
                SimpleToken(TokenType::kIdentifier, "x", 7),
                SimpleToken(TokenType::kRelationalOperator, "!=", 7),
                SimpleToken(TokenType::kConstant, "0", 7),
                SimpleToken(TokenType::kCloseBracket, ")", 7),
                SimpleToken(TokenType::kConditionOperator, "&&", 7),
                SimpleToken(TokenType::kOpenBracket, "(", 7),
                SimpleToken(TokenType::kIdentifier, "y", 7),
                SimpleToken(TokenType::kRelationalOperator, "!=", 7),
                SimpleToken(TokenType::kConstant, "0", 7),
                SimpleToken(TokenType::kCloseBracket, ")", 7),
                SimpleToken(TokenType::kCloseBracket, ")", 7),
                SimpleToken(TokenType::kOpenBrace, "{", 7),
                SimpleToken(TokenType::kIdentifier, "count", 8),
                SimpleToken(TokenType::kAssignment, "=", 8),
                SimpleToken(TokenType::kIdentifier, "count", 8),
                SimpleToken(TokenType::kOperator, "+", 8),
                SimpleToken(TokenType::kConstant, "1", 8),
                SimpleToken(TokenType::kStatementEnd, ";", 8),
                SimpleToken(TokenType::kIdentifier, "cenX", 9),
                SimpleToken(TokenType::kAssignment, "=", 9),
                SimpleToken(TokenType::kIdentifier, "cenX", 9),
                SimpleToken(TokenType::kOperator, "+", 9),
                SimpleToken(TokenType::kIdentifier, "x", 9),
                SimpleToken(TokenType::kStatementEnd, ";", 9),
                SimpleToken(TokenType::kIdentifier, "cenY", 10),
                SimpleToken(TokenType::kAssignment, "=", 10),
                SimpleToken(TokenType::kIdentifier, "cenY", 10),
                SimpleToken(TokenType::kOperator, "+", 10),
                SimpleToken(TokenType::kIdentifier, "y", 10),
                SimpleToken(TokenType::kStatementEnd, ";", 10),
                SimpleToken(TokenType::kKeyWord, "call", 11),
                SimpleToken(TokenType::kIdentifier, "readPoint", 11),
                SimpleToken(TokenType::kStatementEnd, ";", 11),
                SimpleToken(TokenType::kCloseBrace, "}", 12),
                SimpleToken(TokenType::kKeyWord, "if", 14),
                SimpleToken(TokenType::kOpenBracket, "(", 14),
                SimpleToken(TokenType::kIdentifier, "count", 14),
                SimpleToken(TokenType::kRelationalOperator, "==", 14),
                SimpleToken(TokenType::kConstant, "0", 14),
                SimpleToken(TokenType::kCloseBracket, ")", 14),
                SimpleToken(TokenType::kKeyWord, "then", 14),
                SimpleToken(TokenType::kOpenBrace, "{", 14),
                SimpleToken(TokenType::kIdentifier, "flag", 15),
                SimpleToken(TokenType::kAssignment, "=", 15),
                SimpleToken(TokenType::kConstant, "1", 15),
                SimpleToken(TokenType::kStatementEnd, ";", 15),
                SimpleToken(TokenType::kCloseBrace, "}", 16),
                SimpleToken(TokenType::kKeyWord, "else", 16),
                SimpleToken(TokenType::kOpenBrace, "{", 16),
                SimpleToken(TokenType::kIdentifier, "cenX", 17),
                SimpleToken(TokenType::kAssignment, "=", 17),
                SimpleToken(TokenType::kIdentifier, "cenX", 17),
                SimpleToken(TokenType::kOperator, "/", 17),
                SimpleToken(TokenType::kIdentifier, "count", 17),
                SimpleToken(TokenType::kStatementEnd, ";", 17),
                SimpleToken(TokenType::kIdentifier, "cenY", 18),
                SimpleToken(TokenType::kAssignment, "=", 18),
                SimpleToken(TokenType::kIdentifier, "cenY", 18),
                SimpleToken(TokenType::kOperator, "/", 18),
                SimpleToken(TokenType::kIdentifier, "count", 18),
                SimpleToken(TokenType::kStatementEnd, ";", 18),
                SimpleToken(TokenType::kCloseBrace, "}", 19),
                SimpleToken(TokenType::kIdentifier, "normSq", 21),
                SimpleToken(TokenType::kAssignment, "=", 21),
                SimpleToken(TokenType::kIdentifier, "cenX", 21),
                SimpleToken(TokenType::kOperator, "*", 21),
                SimpleToken(TokenType::kIdentifier, "cenX", 21),
                SimpleToken(TokenType::kOperator, "+", 21),
                SimpleToken(TokenType::kIdentifier, "cenY", 21),
                SimpleToken(TokenType::kOperator, "*", 21),
                SimpleToken(TokenType::kIdentifier, "cenY", 21),
                SimpleToken(TokenType::kStatementEnd, ";", 21),
                SimpleToken(TokenType::kCloseBrace, "}", 22),
                SimpleToken(TokenType::kKeyWord, "procedure", 24),
                SimpleToken(TokenType::kIdentifier, "main", 24),
                SimpleToken(TokenType::kOpenBrace, "{", 24),
                SimpleToken(TokenType::kIdentifier, "flag", 25),
                SimpleToken(TokenType::kAssignment, "=", 25),
                SimpleToken(TokenType::kConstant, "0", 25),
                SimpleToken(TokenType::kStatementEnd, ";", 25),
                SimpleToken(TokenType::kKeyWord, "call", 26),
                SimpleToken(TokenType::kIdentifier, "computeCentroid", 26),
                SimpleToken(TokenType::kStatementEnd, ";", 26),
                SimpleToken(TokenType::kKeyWord, "call", 27),
                SimpleToken(TokenType::kIdentifier, "printResults", 27),
                SimpleToken(TokenType::kStatementEnd, ";", 27),
                SimpleToken(TokenType::kCloseBrace, "}", 28),
                SimpleToken(TokenType::kKeyWord, "procedure", 30),
                SimpleToken(TokenType::kIdentifier, "readPoint", 30),
                SimpleToken(TokenType::kOpenBrace, "{", 30),
                SimpleToken(TokenType::kKeyWord, "read", 31),
                SimpleToken(TokenType::kIdentifier, "x", 31),
                SimpleToken(TokenType::kStatementEnd, ";", 31),
                SimpleToken(TokenType::kKeyWord, "read", 32),
                SimpleToken(TokenType::kIdentifier, "y", 32),
                SimpleToken(TokenType::kStatementEnd, ";", 32),
                SimpleToken(TokenType::kCloseBrace, "}", 33),
                SimpleToken(TokenType::kKeyWord, "procedure", 35),
                SimpleToken(TokenType::kIdentifier, "printResults", 35),
                SimpleToken(TokenType::kOpenBrace, "{", 35),
                SimpleToken(TokenType::kKeyWord, "print", 36),
                SimpleToken(TokenType::kIdentifier, "flag", 36),
                SimpleToken(TokenType::kStatementEnd, ";", 36),
                SimpleToken(TokenType::kKeyWord, "print", 37),
                SimpleToken(TokenType::kIdentifier, "cenX", 37),
                SimpleToken(TokenType::kStatementEnd, ";", 37),
                SimpleToken(TokenType::kKeyWord, "print", 38),
                SimpleToken(TokenType::kIdentifier, "cenY", 38),
                SimpleToken(TokenType::kStatementEnd, ";", 38),
                SimpleToken(TokenType::kKeyWord, "print", 39),
                SimpleToken(TokenType::kIdentifier, "normSq", 39),
                SimpleToken(TokenType::kStatementEnd, ";", 39),
                SimpleToken(TokenType::kCloseBrace, "}", 40)
        };

        REQUIRE(tokens == expected);
    }

    SECTION("should throw logic error") {
        SECTION("when only one & symbol") {
            string source = "procedure computeCentroid {\n"
                            "    count = 0;\n"
                            "    cenX = 0;\n"
                            "    cenY = 0;\n"
                            "    call readPoint;\n"
                            "\n"
                            "    while ((x != 0) & (y != 0)) {\n"
                            "        count = count + 1;\n"
                            "        cenX = cenX + x;\n"
                            "        cenY = cenY + y;\n"
                            "        call readPoint;\n"
                            "    }\n"
                            "\n"
                            "    if (count == 0) then {\n"
                            "        flag = 1;\n"
                            "    } else {\n"
                            "        cenX = cenX / count;\n"
                            "        cenY = cenY / count;\n"
                            "    }\n"
                            "\n"
                            "    normSq = cenX * cenX + cenY * cenY;\n"
                            "}\n"
                            "\n"
                            "procedure main {\n"
                            "    flag = 0;\n"
                            "    call computeCentroid;\n"
                            "    call printResults;\n"
                            "}\n"
                            "\n"
                            "procedure readPoint{\n"
                            "    read x;\n"
                            "    read y;\n"
                            "}\n"
                            "\n"
                            "procedure printResults{\n"
                            "    print flag;\n"
                            "    print cenX;\n"
                            "    print cenY;\n"
                            "    print normSq;\n"
                            "}";
            REQUIRE_THROWS_AS(SimpleTokenizer::tokenize(source), logic_error);
            REQUIRE_THROWS_WITH(SimpleTokenizer::tokenize(source), "Invalid & symbol at line 7");
        }

        SECTION("when only one | symbol") {
            string source = "procedure computeCentroid {\n"
                            "    count = 0;\n"
                            "    cenX = 0;\n"
                            "    cenY = 0;\n"
                            "    call readPoint;\n"
                            "\n"
                            "    while ((x != 0) && (y != 0)) {\n"
                            "        count = count + 1;\n"
                            "        cenX = cenX + x;\n"
                            "        cenY = cenY + y;\n"
                            "        call readPoint;\n"
                            "    }\n"
                            "\n"
                            "    if (count == 0 | count < 0) then {\n"
                            "        flag = 1;\n"
                            "    } else {\n"
                            "        cenX = cenX / count;\n"
                            "        cenY = cenY / count;\n"
                            "    }\n"
                            "\n"
                            "    normSq = cenX * cenX + cenY * cenY;\n"
                            "}\n"
                            "\n"
                            "procedure main {\n"
                            "    flag = 0;\n"
                            "    call computeCentroid;\n"
                            "    call printResults;\n"
                            "}\n"
                            "\n"
                            "procedure readPoint{\n"
                            "    read x;\n"
                            "    read y;\n"
                            "}\n"
                            "\n"
                            "procedure printResults{\n"
                            "    print flag;\n"
                            "    print cenX;\n"
                            "    print cenY;\n"
                            "    print normSq;\n"
                            "}";
            REQUIRE_THROWS_AS(SimpleTokenizer::tokenize(source), logic_error);
            REQUIRE_THROWS_WITH(SimpleTokenizer::tokenize(source), "Invalid | symbol at line 14");
        }

        SECTION("when invalid symbol") {
            string source = "procedure computeCentroid {\n"
                            "    count = 0;\n"
                            "    cenX = 0;\n"
                            "    cenY = 0;\n"
                            "    call readPoint;\n"
                            "\n"
                            "    while ((x != 0) && (y != 0)) {\n"
                            "        count = count + 1;\n"
                            "        cenX = cenX + x;\n"
                            "        cenY = cenY + y;\n"
                            "        call readPoint;\n"
                            "    }\n"
                            "\n"
                            "    if (count == 0) then {\n"
                            "        flag = 1;\n"
                            "    } else {\n"
                            "        cenX = cenX / count;\n"
                            "        cenY = cenY / count;\n"
                            "    }\n"
                            "\n"
                            "    normSq = cenX * cenX + cenY * cenY;\n"
                            "}\n"
                            "\n"
                            "procedure main {\n"
                            "    if (~(flag == 0)) {\n"
                            "        flag = 0;\n"
                            "    }\n"
                            "    call computeCentroid;\n"
                            "    call printResults;\n"
                            "}\n"
                            "\n"
                            "procedure readPoint{\n"
                            "    read x;\n"
                            "    read y;\n"
                            "}\n"
                            "\n"
                            "procedure printResults{\n"
                            "    print flag;\n"
                            "    print cenX;\n"
                            "    print cenY;\n"
                            "    print normSq;\n"
                            "}";
            REQUIRE_THROWS_AS(SimpleTokenizer::tokenize(source), logic_error);
            REQUIRE_THROWS_WITH(SimpleTokenizer::tokenize(source), "Invalid ~ symbol at line 25");
        }
    }
}
