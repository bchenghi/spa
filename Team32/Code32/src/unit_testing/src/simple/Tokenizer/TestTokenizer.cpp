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
                Token(TokenType::KEY_WORD, "procedure", 1),
                Token(TokenType::IDENTIFIER, "computeCentroid", 1),
                Token(TokenType::OPEN_BRACE, "{", 1),
                Token(TokenType::IDENTIFIER, "count", 2),
                Token(TokenType::ASSIGNMENT, "=", 2),
                Token(TokenType::CONSTANT, "0", 2),
                Token(TokenType::STATEMENT_END, ";", 2),
                Token(TokenType::IDENTIFIER, "cenX", 3),
                Token(TokenType::ASSIGNMENT, "=", 3),
                Token(TokenType::CONSTANT, "0", 3),
                Token(TokenType::STATEMENT_END, ";", 3),
                Token(TokenType::IDENTIFIER, "cenY", 4),
                Token(TokenType::ASSIGNMENT, "=", 4),
                Token(TokenType::CONSTANT, "0", 4),
                Token(TokenType::STATEMENT_END, ";", 4),
                Token(TokenType::KEY_WORD, "call", 5),
                Token(TokenType::IDENTIFIER, "readPoint", 5),
                Token(TokenType::STATEMENT_END, ";", 5),
                Token(TokenType::KEY_WORD, "while", 7),
                Token(TokenType::OPEN_BRACKET, "(", 7),
                Token(TokenType::OPEN_BRACKET, "(", 7),
                Token(TokenType::IDENTIFIER, "x", 7),
                Token(TokenType::RELATIONAL_OPERATOR, "!=", 7),
                Token(TokenType::CONSTANT, "0", 7),
                Token(TokenType::CLOSE_BRACKET, ")", 7),
                Token(TokenType::CONDITION_OPERATOR, "&&", 7),
                Token(TokenType::OPEN_BRACKET, "(", 7),
                Token(TokenType::IDENTIFIER, "y", 7),
                Token(TokenType::RELATIONAL_OPERATOR, "!=", 7),
                Token(TokenType::CONSTANT, "0", 7),
                Token(TokenType::CLOSE_BRACKET, ")", 7),
                Token(TokenType::CLOSE_BRACKET, ")", 7),
                Token(TokenType::OPEN_BRACE, "{", 7),
                Token(TokenType::IDENTIFIER, "count", 8),
                Token(TokenType::ASSIGNMENT, "=", 8),
                Token(TokenType::IDENTIFIER, "count", 8),
                Token(TokenType::OPERATOR, "+", 8),
                Token(TokenType::CONSTANT, "1", 8),
                Token(TokenType::STATEMENT_END, ";", 8),
                Token(TokenType::IDENTIFIER, "cenX", 9),
                Token(TokenType::ASSIGNMENT, "=", 9),
                Token(TokenType::IDENTIFIER, "cenX", 9),
                Token(TokenType::OPERATOR, "+", 9),
                Token(TokenType::IDENTIFIER, "x", 9),
                Token(TokenType::STATEMENT_END, ";", 9),
                Token(TokenType::IDENTIFIER, "cenY", 10),
                Token(TokenType::ASSIGNMENT, "=", 10),
                Token(TokenType::IDENTIFIER, "cenY", 10),
                Token(TokenType::OPERATOR, "+", 10),
                Token(TokenType::IDENTIFIER, "y", 10),
                Token(TokenType::STATEMENT_END, ";", 10),
                Token(TokenType::KEY_WORD, "call", 11),
                Token(TokenType::IDENTIFIER, "readPoint", 11),
                Token(TokenType::STATEMENT_END, ";", 11),
                Token(TokenType::CLOSE_BRACE, "}", 12),
                Token(TokenType::KEY_WORD, "if", 14),
                Token(TokenType::OPEN_BRACKET, "(", 14),
                Token(TokenType::IDENTIFIER, "count", 14),
                Token(TokenType::RELATIONAL_OPERATOR, "==", 14),
                Token(TokenType::CONSTANT, "0", 14),
                Token(TokenType::CLOSE_BRACKET, ")", 14),
                Token(TokenType::KEY_WORD, "then", 14),
                Token(TokenType::OPEN_BRACE, "{", 14),
                Token(TokenType::IDENTIFIER, "flag", 15),
                Token(TokenType::ASSIGNMENT, "=", 15),
                Token(TokenType::CONSTANT, "1", 15),
                Token(TokenType::STATEMENT_END, ";", 15),
                Token(TokenType::CLOSE_BRACE, "}", 16),
                Token(TokenType::KEY_WORD, "else", 16),
                Token(TokenType::OPEN_BRACE, "{", 16),
                Token(TokenType::IDENTIFIER, "cenX", 17),
                Token(TokenType::ASSIGNMENT, "=", 17),
                Token(TokenType::IDENTIFIER, "cenX", 17),
                Token(TokenType::OPERATOR, "/", 17),
                Token(TokenType::IDENTIFIER, "count", 17),
                Token(TokenType::STATEMENT_END, ";", 17),
                Token(TokenType::IDENTIFIER, "cenY", 18),
                Token(TokenType::ASSIGNMENT, "=", 18),
                Token(TokenType::IDENTIFIER, "cenY", 18),
                Token(TokenType::OPERATOR, "/", 18),
                Token(TokenType::IDENTIFIER, "count", 18),
                Token(TokenType::STATEMENT_END, ";", 18),
                Token(TokenType::CLOSE_BRACE, "}", 19),
                Token(TokenType::IDENTIFIER, "normSq", 21),
                Token(TokenType::ASSIGNMENT, "=", 21),
                Token(TokenType::IDENTIFIER, "cenX", 21),
                Token(TokenType::OPERATOR, "*", 21),
                Token(TokenType::IDENTIFIER, "cenX", 21),
                Token(TokenType::OPERATOR, "+", 21),
                Token(TokenType::IDENTIFIER, "cenY", 21),
                Token(TokenType::OPERATOR, "*", 21),
                Token(TokenType::IDENTIFIER, "cenY", 21),
                Token(TokenType::STATEMENT_END, ";", 21),
                Token(TokenType::CLOSE_BRACE, "}", 22),
                Token(TokenType::KEY_WORD, "procedure", 24),
                Token(TokenType::IDENTIFIER, "main", 24),
                Token(TokenType::OPEN_BRACE, "{", 24),
                Token(TokenType::IDENTIFIER, "flag", 25),
                Token(TokenType::ASSIGNMENT, "=", 25),
                Token(TokenType::CONSTANT, "0", 25),
                Token(TokenType::STATEMENT_END, ";", 25),
                Token(TokenType::KEY_WORD, "call", 26),
                Token(TokenType::IDENTIFIER, "computeCentroid", 26),
                Token(TokenType::STATEMENT_END, ";", 26),
                Token(TokenType::KEY_WORD, "call", 27),
                Token(TokenType::IDENTIFIER, "printResults", 27),
                Token(TokenType::STATEMENT_END, ";", 27),
                Token(TokenType::CLOSE_BRACE, "}", 28),
                Token(TokenType::KEY_WORD, "procedure", 30),
                Token(TokenType::IDENTIFIER, "readPoint", 30),
                Token(TokenType::OPEN_BRACE, "{", 30),
                Token(TokenType::KEY_WORD, "read", 31),
                Token(TokenType::IDENTIFIER, "x", 31),
                Token(TokenType::STATEMENT_END, ";", 31),
                Token(TokenType::KEY_WORD, "read", 32),
                Token(TokenType::IDENTIFIER, "y", 32),
                Token(TokenType::STATEMENT_END, ";", 32),
                Token(TokenType::CLOSE_BRACE, "}", 33),
                Token(TokenType::KEY_WORD, "procedure", 35),
                Token(TokenType::IDENTIFIER, "printResults", 35),
                Token(TokenType::OPEN_BRACE, "{", 35),
                Token(TokenType::KEY_WORD, "print", 36),
                Token(TokenType::IDENTIFIER, "flag", 36),
                Token(TokenType::STATEMENT_END, ";", 36),
                Token(TokenType::KEY_WORD, "print", 37),
                Token(TokenType::IDENTIFIER, "cenX", 37),
                Token(TokenType::STATEMENT_END, ";", 37),
                Token(TokenType::KEY_WORD, "print", 38),
                Token(TokenType::IDENTIFIER, "cenY", 38),
                Token(TokenType::STATEMENT_END, ";", 38),
                Token(TokenType::KEY_WORD, "print", 39),
                Token(TokenType::IDENTIFIER, "normSq", 39),
                Token(TokenType::STATEMENT_END, ";", 39),
                Token(TokenType::CLOSE_BRACE, "}", 40)
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
