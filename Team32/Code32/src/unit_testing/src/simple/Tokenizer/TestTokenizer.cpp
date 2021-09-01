#include "catch.hpp"
#include "simple/Tokenizer/Tokenizer.h"

#include <string>
#include <vector>

using simple::Token;
using simple::Tokenizer;
using simple::TokenType;
using std::logic_error;
using std::string;
using std::vector;

TEST_CASE("simple::Tokenizer", "[simple]") {
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
        vector<Token> tokens = Tokenizer::tokenize(source);
        vector<Token> expected = {
                Token(TokenType::kKeyWord, "procedure", 1),
                Token(TokenType::kIdentifier, "computeCentroid", 1),
                Token(TokenType::kOpenBrace, "{", 1),
                Token(TokenType::kIdentifier, "count", 2),
                Token(TokenType::kAssignment, "=", 2),
                Token(TokenType::kConstant, "0", 2),
                Token(TokenType::kStatementEnd, ";", 2),
                Token(TokenType::kIdentifier, "cenX", 3),
                Token(TokenType::kAssignment, "=", 3),
                Token(TokenType::kConstant, "0", 3),
                Token(TokenType::kStatementEnd, ";", 3),
                Token(TokenType::kIdentifier, "cenY", 4),
                Token(TokenType::kAssignment, "=", 4),
                Token(TokenType::kConstant, "0", 4),
                Token(TokenType::kStatementEnd, ";", 4),
                Token(TokenType::kKeyWord, "call", 5),
                Token(TokenType::kIdentifier, "readPoint", 5),
                Token(TokenType::kStatementEnd, ";", 5),
                Token(TokenType::kKeyWord, "while", 7),
                Token(TokenType::kOpenBracket, "(", 7),
                Token(TokenType::kOpenBracket, "(", 7),
                Token(TokenType::kIdentifier, "x", 7),
                Token(TokenType::kRelationalOperator, "!=", 7),
                Token(TokenType::kConstant, "0", 7),
                Token(TokenType::kCloseBracket, ")", 7),
                Token(TokenType::kConditionOperator, "&&", 7),
                Token(TokenType::kOpenBracket, "(", 7),
                Token(TokenType::kIdentifier, "y", 7),
                Token(TokenType::kRelationalOperator, "!=", 7),
                Token(TokenType::kConstant, "0", 7),
                Token(TokenType::kCloseBracket, ")", 7),
                Token(TokenType::kCloseBracket, ")", 7),
                Token(TokenType::kOpenBrace, "{", 7),
                Token(TokenType::kIdentifier, "count", 8),
                Token(TokenType::kAssignment, "=", 8),
                Token(TokenType::kIdentifier, "count", 8),
                Token(TokenType::kOperator, "+", 8),
                Token(TokenType::kConstant, "1", 8),
                Token(TokenType::kStatementEnd, ";", 8),
                Token(TokenType::kIdentifier, "cenX", 9),
                Token(TokenType::kAssignment, "=", 9),
                Token(TokenType::kIdentifier, "cenX", 9),
                Token(TokenType::kOperator, "+", 9),
                Token(TokenType::kIdentifier, "x", 9),
                Token(TokenType::kStatementEnd, ";", 9),
                Token(TokenType::kIdentifier, "cenY", 10),
                Token(TokenType::kAssignment, "=", 10),
                Token(TokenType::kIdentifier, "cenY", 10),
                Token(TokenType::kOperator, "+", 10),
                Token(TokenType::kIdentifier, "y", 10),
                Token(TokenType::kStatementEnd, ";", 10),
                Token(TokenType::kKeyWord, "call", 11),
                Token(TokenType::kIdentifier, "readPoint", 11),
                Token(TokenType::kStatementEnd, ";", 11),
                Token(TokenType::kCloseBrace, "}", 12),
                Token(TokenType::kKeyWord, "if", 14),
                Token(TokenType::kOpenBracket, "(", 14),
                Token(TokenType::kIdentifier, "count", 14),
                Token(TokenType::kRelationalOperator, "==", 14),
                Token(TokenType::kConstant, "0", 14),
                Token(TokenType::kCloseBracket, ")", 14),
                Token(TokenType::kKeyWord, "then", 14),
                Token(TokenType::kOpenBrace, "{", 14),
                Token(TokenType::kIdentifier, "flag", 15),
                Token(TokenType::kAssignment, "=", 15),
                Token(TokenType::kConstant, "1", 15),
                Token(TokenType::kStatementEnd, ";", 15),
                Token(TokenType::kCloseBrace, "}", 16),
                Token(TokenType::kKeyWord, "else", 16),
                Token(TokenType::kOpenBrace, "{", 16),
                Token(TokenType::kIdentifier, "cenX", 17),
                Token(TokenType::kAssignment, "=", 17),
                Token(TokenType::kIdentifier, "cenX", 17),
                Token(TokenType::kOperator, "/", 17),
                Token(TokenType::kIdentifier, "count", 17),
                Token(TokenType::kStatementEnd, ";", 17),
                Token(TokenType::kIdentifier, "cenY", 18),
                Token(TokenType::kAssignment, "=", 18),
                Token(TokenType::kIdentifier, "cenY", 18),
                Token(TokenType::kOperator, "/", 18),
                Token(TokenType::kIdentifier, "count", 18),
                Token(TokenType::kStatementEnd, ";", 18),
                Token(TokenType::kCloseBrace, "}", 19),
                Token(TokenType::kIdentifier, "normSq", 21),
                Token(TokenType::kAssignment, "=", 21),
                Token(TokenType::kIdentifier, "cenX", 21),
                Token(TokenType::kOperator, "*", 21),
                Token(TokenType::kIdentifier, "cenX", 21),
                Token(TokenType::kOperator, "+", 21),
                Token(TokenType::kIdentifier, "cenY", 21),
                Token(TokenType::kOperator, "*", 21),
                Token(TokenType::kIdentifier, "cenY", 21),
                Token(TokenType::kStatementEnd, ";", 21),
                Token(TokenType::kCloseBrace, "}", 22),
                Token(TokenType::kKeyWord, "procedure", 24),
                Token(TokenType::kIdentifier, "main", 24),
                Token(TokenType::kOpenBrace, "{", 24),
                Token(TokenType::kIdentifier, "flag", 25),
                Token(TokenType::kAssignment, "=", 25),
                Token(TokenType::kConstant, "0", 25),
                Token(TokenType::kStatementEnd, ";", 25),
                Token(TokenType::kKeyWord, "call", 26),
                Token(TokenType::kIdentifier, "computeCentroid", 26),
                Token(TokenType::kStatementEnd, ";", 26),
                Token(TokenType::kKeyWord, "call", 27),
                Token(TokenType::kIdentifier, "printResults", 27),
                Token(TokenType::kStatementEnd, ";", 27),
                Token(TokenType::kCloseBrace, "}", 28),
                Token(TokenType::kKeyWord, "procedure", 30),
                Token(TokenType::kIdentifier, "readPoint", 30),
                Token(TokenType::kOpenBrace, "{", 30),
                Token(TokenType::kKeyWord, "read", 31),
                Token(TokenType::kIdentifier, "x", 31),
                Token(TokenType::kStatementEnd, ";", 31),
                Token(TokenType::kKeyWord, "read", 32),
                Token(TokenType::kIdentifier, "y", 32),
                Token(TokenType::kStatementEnd, ";", 32),
                Token(TokenType::kCloseBrace, "}", 33),
                Token(TokenType::kKeyWord, "procedure", 35),
                Token(TokenType::kIdentifier, "printResults", 35),
                Token(TokenType::kOpenBrace, "{", 35),
                Token(TokenType::kKeyWord, "print", 36),
                Token(TokenType::kIdentifier, "flag", 36),
                Token(TokenType::kStatementEnd, ";", 36),
                Token(TokenType::kKeyWord, "print", 37),
                Token(TokenType::kIdentifier, "cenX", 37),
                Token(TokenType::kStatementEnd, ";", 37),
                Token(TokenType::kKeyWord, "print", 38),
                Token(TokenType::kIdentifier, "cenY", 38),
                Token(TokenType::kStatementEnd, ";", 38),
                Token(TokenType::kKeyWord, "print", 39),
                Token(TokenType::kIdentifier, "normSq", 39),
                Token(TokenType::kStatementEnd, ";", 39),
                Token(TokenType::kCloseBrace, "}", 40)
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
            REQUIRE_THROWS_AS(Tokenizer::tokenize(source), logic_error);
            REQUIRE_THROWS_WITH(Tokenizer::tokenize(source), "Invalid & symbol at line 7");
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
            REQUIRE_THROWS_AS(Tokenizer::tokenize(source), logic_error);
            REQUIRE_THROWS_WITH(Tokenizer::tokenize(source), "Invalid | symbol at line 14");
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
            REQUIRE_THROWS_AS(Tokenizer::tokenize(source), logic_error);
            REQUIRE_THROWS_WITH(Tokenizer::tokenize(source), "Invalid ~ symbol at line 25");
        }
    }
}
