#include "catch.hpp"

#include "pql/Tokenizer/Tokenizer.h"
#include "pql/Tokenizer/Token.h"

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

using pql::Token;
using pql::Tokenizer;
using pql::TokenType;
using std::logic_error;
using std::string;
using std::vector;

TEST_CASE("pql::Tokenizer", "[pql]") {
    SECTION("should tokenize pql query") {
        string source = "assign a; while w;\n"
                        "Select w such that Parent* (w, a)\n"
                        "pattern a (\"count\", _)";
        vector<Token> tokens = Tokenizer::tokenize(source);
        vector<Token> expected = {
            Token(TokenType::KEY_WORD, "assign", 1),
            Token(TokenType::IDENTIFIER, "a", 1),
            Token(TokenType::STATEMENT_END, ";", 1),
            Token(TokenType::KEY_WORD, "while", 1),
            Token(TokenType::IDENTIFIER, "w", 1),
            Token(TokenType::STATEMENT_END, ";", 1),
            Token(TokenType::KEY_WORD, "Select", 2),
            Token(TokenType::IDENTIFIER, "w", 2),
            Token(TokenType::KEY_WORD, "such that", 2),
            Token(TokenType::KEY_WORD, "Parent*", 2),
            Token(TokenType::OPEN_BRACKET, "(", 2),
            Token(TokenType::IDENTIFIER, "w", 2),
            Token(TokenType::SEPARATOR, ",", 2),
            Token(TokenType::IDENTIFIER, "a", 2),
            Token(TokenType::CLOSE_BRACKET, ")", 2),
            Token(TokenType::KEY_WORD, "pattern", 3),
            Token(TokenType::IDENTIFIER, "a", 3),
            Token(TokenType::OPEN_BRACKET, "(", 3),
            Token(TokenType::CONSTANT_STRING, "count", 3),
            Token(TokenType::SEPARATOR, ",", 3),
            Token(TokenType::WILD_CARD, "_", 3),
            Token(TokenType::CLOSE_BRACKET, ")", 3),
        };

        REQUIRE(tokens == expected);
    }

    SECTION("should tokenize iter 2 pql query") {
        string source = "prog_line n; procedure p, p1; assign a1, a2; stmt s1; variable v;\n"
                        "Select <n, p> such that Next* (5, n)\n"
                        "\tand Next(n, 12)\n"
                        "\tand Calls(p, p1)\n"
                        "\tsuch that Calls* (p, p1)\n"
                        "\tand Affects (a1, a2)\n"
                        "\tand Affects*(a1, a2)\n"
                        "\twith p.procName = v.varName and s1.stmt#=n";
        vector<Token> tokens = Tokenizer::tokenize(source);
        vector<Token> expected = {
            Token(TokenType::KEY_WORD, "prog_line", 1),
            Token(TokenType::IDENTIFIER, "n", 1),
            Token(TokenType::STATEMENT_END, ";", 1),
            Token(TokenType::KEY_WORD, "procedure", 1),
            Token(TokenType::IDENTIFIER, "p", 1),
            Token(TokenType::SEPARATOR, ",", 1),
            Token(TokenType::IDENTIFIER, "p1", 1),
            Token(TokenType::STATEMENT_END, ";", 1),
            Token(TokenType::KEY_WORD, "assign", 1),
            Token(TokenType::IDENTIFIER, "a1", 1),
            Token(TokenType::SEPARATOR, ",", 1),
            Token(TokenType::IDENTIFIER, "a2", 1),
            Token(TokenType::STATEMENT_END, ";", 1),
            Token(TokenType::KEY_WORD, "stmt", 1),
            Token(TokenType::IDENTIFIER, "s1", 1),
            Token(TokenType::STATEMENT_END, ";", 1),
            Token(TokenType::KEY_WORD, "variable", 1),
            Token(TokenType::IDENTIFIER, "v", 1),
            Token(TokenType::STATEMENT_END, ";", 1),
            Token(TokenType::KEY_WORD, "Select", 2),
            Token(TokenType::OPEN_TUPLE, "<", 2),
            Token(TokenType::IDENTIFIER, "n", 2),
            Token(TokenType::SEPARATOR, ",", 2),
            Token(TokenType::IDENTIFIER, "p", 2),
            Token(TokenType::CLOSE_TUPLE, ">", 2),
            Token(TokenType::KEY_WORD, "such that", 2),
            Token(TokenType::KEY_WORD, "Next*", 2),
            Token(TokenType::OPEN_BRACKET, "(", 2),
            Token(TokenType::CONSTANT_INTEGER, "5", 2),
            Token(TokenType::SEPARATOR, ",", 2),
            Token(TokenType::IDENTIFIER, "n", 2),
            Token(TokenType::CLOSE_BRACKET, ")", 2),
            Token(TokenType::KEY_WORD, "and", 3),
            Token(TokenType::KEY_WORD, "Next", 3),
            Token(TokenType::OPEN_BRACKET, "(", 3),
            Token(TokenType::IDENTIFIER, "n", 3),
            Token(TokenType::SEPARATOR, ",", 3),
            Token(TokenType::CONSTANT_INTEGER, "12", 3),
            Token(TokenType::CLOSE_BRACKET, ")", 3),
            Token(TokenType::KEY_WORD, "and", 4),
            Token(TokenType::KEY_WORD, "Calls", 4),
            Token(TokenType::OPEN_BRACKET, "(", 4),
            Token(TokenType::IDENTIFIER, "p", 4),
            Token(TokenType::SEPARATOR, ",", 4),
            Token(TokenType::IDENTIFIER, "p1", 4),
            Token(TokenType::CLOSE_BRACKET, ")", 4),
            Token(TokenType::KEY_WORD, "such that", 5),
            Token(TokenType::KEY_WORD, "Calls*", 5),
            Token(TokenType::OPEN_BRACKET, "(", 5),
            Token(TokenType::IDENTIFIER, "p", 5),
            Token(TokenType::SEPARATOR, ",", 5),
            Token(TokenType::IDENTIFIER, "p1", 5),
            Token(TokenType::CLOSE_BRACKET, ")", 5),
            Token(TokenType::KEY_WORD, "and", 6),
            Token(TokenType::KEY_WORD, "Affects", 6),
            Token(TokenType::OPEN_BRACKET, "(", 6),
            Token(TokenType::IDENTIFIER, "a1", 6),
            Token(TokenType::SEPARATOR, ",", 6),
            Token(TokenType::IDENTIFIER, "a2", 6),
            Token(TokenType::CLOSE_BRACKET, ")", 6),
            Token(TokenType::KEY_WORD, "and", 7),
            Token(TokenType::KEY_WORD, "Affects*", 7),
            Token(TokenType::OPEN_BRACKET, "(", 7),
            Token(TokenType::IDENTIFIER, "a1", 7),
            Token(TokenType::SEPARATOR, ",", 7),
            Token(TokenType::IDENTIFIER, "a2", 7),
            Token(TokenType::CLOSE_BRACKET, ")", 7),
            Token(TokenType::KEY_WORD, "with", 8),
            Token(TokenType::IDENTIFIER, "p", 8),
            Token(TokenType::MEMBER_OPERATOR, ".", 8),
            Token(TokenType::ATTRIBUTE_NAME, "procName", 8),
            Token(TokenType::EQUAL_OPERATOR, "=", 8),
            Token(TokenType::IDENTIFIER, "v", 8),
            Token(TokenType::MEMBER_OPERATOR, ".", 8),
            Token(TokenType::ATTRIBUTE_NAME, "varName", 8),
            Token(TokenType::KEY_WORD, "and", 8),
            Token(TokenType::IDENTIFIER, "s1", 8),
            Token(TokenType::MEMBER_OPERATOR, ".", 8),
            Token(TokenType::ATTRIBUTE_NAME, "stmt#", 8),
            Token(TokenType::EQUAL_OPERATOR, "=", 8),
            Token(TokenType::IDENTIFIER, "n", 8)
        };

        REQUIRE(tokens == expected);
    }

    SECTION("should tokenize iter 2 pql query selecting BOOLEAN") {
        string source = "prog_line n; procedure p, p1; assign a1, a2; stmt s1; variable v;\n"
                        "Select BOOLEAN such that Next* (5, n)\n"
                        "\tand Next(n, 12)\n"
                        "\tand Calls(p, p1)\n"
                        "\tsuch that Calls* (p, p1)\n"
                        "\tand Affects (a1, a2)\n"
                        "\tand Affects*(a1, a2)\n"
                        "\twith p.procName = v.varName and s1.stmt#=n";
        vector<Token> tokens = Tokenizer::tokenize(source);
        vector<Token> expected = {
                Token(TokenType::KEY_WORD, "prog_line", 1),
                Token(TokenType::IDENTIFIER, "n", 1),
                Token(TokenType::STATEMENT_END, ";", 1),
                Token(TokenType::KEY_WORD, "procedure", 1),
                Token(TokenType::IDENTIFIER, "p", 1),
                Token(TokenType::SEPARATOR, ",", 1),
                Token(TokenType::IDENTIFIER, "p1", 1),
                Token(TokenType::STATEMENT_END, ";", 1),
                Token(TokenType::KEY_WORD, "assign", 1),
                Token(TokenType::IDENTIFIER, "a1", 1),
                Token(TokenType::SEPARATOR, ",", 1),
                Token(TokenType::IDENTIFIER, "a2", 1),
                Token(TokenType::STATEMENT_END, ";", 1),
                Token(TokenType::KEY_WORD, "stmt", 1),
                Token(TokenType::IDENTIFIER, "s1", 1),
                Token(TokenType::STATEMENT_END, ";", 1),
                Token(TokenType::KEY_WORD, "variable", 1),
                Token(TokenType::IDENTIFIER, "v", 1),
                Token(TokenType::STATEMENT_END, ";", 1),
                Token(TokenType::KEY_WORD, "Select", 2),
                Token(TokenType::BOOLEAN, "BOOLEAN", 2),
                Token(TokenType::KEY_WORD, "such that", 2),
                Token(TokenType::KEY_WORD, "Next*", 2),
                Token(TokenType::OPEN_BRACKET, "(", 2),
                Token(TokenType::CONSTANT_INTEGER, "5", 2),
                Token(TokenType::SEPARATOR, ",", 2),
                Token(TokenType::IDENTIFIER, "n", 2),
                Token(TokenType::CLOSE_BRACKET, ")", 2),
                Token(TokenType::KEY_WORD, "and", 3),
                Token(TokenType::KEY_WORD, "Next", 3),
                Token(TokenType::OPEN_BRACKET, "(", 3),
                Token(TokenType::IDENTIFIER, "n", 3),
                Token(TokenType::SEPARATOR, ",", 3),
                Token(TokenType::CONSTANT_INTEGER, "12", 3),
                Token(TokenType::CLOSE_BRACKET, ")", 3),
                Token(TokenType::KEY_WORD, "and", 4),
                Token(TokenType::KEY_WORD, "Calls", 4),
                Token(TokenType::OPEN_BRACKET, "(", 4),
                Token(TokenType::IDENTIFIER, "p", 4),
                Token(TokenType::SEPARATOR, ",", 4),
                Token(TokenType::IDENTIFIER, "p1", 4),
                Token(TokenType::CLOSE_BRACKET, ")", 4),
                Token(TokenType::KEY_WORD, "such that", 5),
                Token(TokenType::KEY_WORD, "Calls*", 5),
                Token(TokenType::OPEN_BRACKET, "(", 5),
                Token(TokenType::IDENTIFIER, "p", 5),
                Token(TokenType::SEPARATOR, ",", 5),
                Token(TokenType::IDENTIFIER, "p1", 5),
                Token(TokenType::CLOSE_BRACKET, ")", 5),
                Token(TokenType::KEY_WORD, "and", 6),
                Token(TokenType::KEY_WORD, "Affects", 6),
                Token(TokenType::OPEN_BRACKET, "(", 6),
                Token(TokenType::IDENTIFIER, "a1", 6),
                Token(TokenType::SEPARATOR, ",", 6),
                Token(TokenType::IDENTIFIER, "a2", 6),
                Token(TokenType::CLOSE_BRACKET, ")", 6),
                Token(TokenType::KEY_WORD, "and", 7),
                Token(TokenType::KEY_WORD, "Affects*", 7),
                Token(TokenType::OPEN_BRACKET, "(", 7),
                Token(TokenType::IDENTIFIER, "a1", 7),
                Token(TokenType::SEPARATOR, ",", 7),
                Token(TokenType::IDENTIFIER, "a2", 7),
                Token(TokenType::CLOSE_BRACKET, ")", 7),
                Token(TokenType::KEY_WORD, "with", 8),
                Token(TokenType::IDENTIFIER, "p", 8),
                Token(TokenType::MEMBER_OPERATOR, ".", 8),
                Token(TokenType::ATTRIBUTE_NAME, "procName", 8),
                Token(TokenType::EQUAL_OPERATOR, "=", 8),
                Token(TokenType::IDENTIFIER, "v", 8),
                Token(TokenType::MEMBER_OPERATOR, ".", 8),
                Token(TokenType::ATTRIBUTE_NAME, "varName", 8),
                Token(TokenType::KEY_WORD, "and", 8),
                Token(TokenType::IDENTIFIER, "s1", 8),
                Token(TokenType::MEMBER_OPERATOR, ".", 8),
                Token(TokenType::ATTRIBUTE_NAME, "stmt#", 8),
                Token(TokenType::EQUAL_OPERATOR, "=", 8),
                Token(TokenType::IDENTIFIER, "n", 8)
        };

        REQUIRE(tokens == expected);
    }

    SECTION("should tokenize extension tokens") {
        string source = "stmt s1, s2;\n"
                        "Select <s1, s2> such that AffectsBip(s1, s2)\n"
                        "    and AffectsBip*(s1, s2)\n"
                        "    and NextBip(s1, s2)\n"
                        "    and NextBip*(s1, s2)";
        vector<Token> tokens = Tokenizer::tokenize(source);
        vector<Token> expected = {
                Token(TokenType::KEY_WORD, "stmt", 1),
                Token(TokenType::IDENTIFIER, "s1", 1),
                Token(TokenType::SEPARATOR, ",", 1),
                Token(TokenType::IDENTIFIER, "s2", 1),
                Token(TokenType::STATEMENT_END, ";", 1),
                Token(TokenType::KEY_WORD, "Select", 2),
                Token(TokenType::OPEN_TUPLE, "<", 2),
                Token(TokenType::IDENTIFIER, "s1", 2),
                Token(TokenType::SEPARATOR, ",", 2),
                Token(TokenType::IDENTIFIER, "s2", 2),
                Token(TokenType::CLOSE_TUPLE, ">", 2),
                Token(TokenType::KEY_WORD, "such that", 2),
                Token(TokenType::KEY_WORD, "AffectsBip", 2),
                Token(TokenType::OPEN_BRACKET, "(", 2),
                Token(TokenType::IDENTIFIER, "s1", 2),
                Token(TokenType::SEPARATOR, ",", 2),
                Token(TokenType::IDENTIFIER, "s2", 2),
                Token(TokenType::CLOSE_BRACKET, ")", 2),
                Token(TokenType::KEY_WORD, "and", 3),
                Token(TokenType::KEY_WORD, "AffectsBip*", 3),
                Token(TokenType::OPEN_BRACKET, "(", 3),
                Token(TokenType::IDENTIFIER, "s1", 3),
                Token(TokenType::SEPARATOR, ",", 3),
                Token(TokenType::IDENTIFIER, "s2", 3),
                Token(TokenType::CLOSE_BRACKET, ")", 3),
                Token(TokenType::KEY_WORD, "and", 4),
                Token(TokenType::KEY_WORD, "NextBip", 4),
                Token(TokenType::OPEN_BRACKET, "(", 4),
                Token(TokenType::IDENTIFIER, "s1", 4),
                Token(TokenType::SEPARATOR, ",", 4),
                Token(TokenType::IDENTIFIER, "s2", 4),
                Token(TokenType::CLOSE_BRACKET, ")", 4),
                Token(TokenType::KEY_WORD, "and", 5),
                Token(TokenType::KEY_WORD, "NextBip*", 5),
                Token(TokenType::OPEN_BRACKET, "(", 5),
                Token(TokenType::IDENTIFIER, "s1", 5),
                Token(TokenType::SEPARATOR, ",", 5),
                Token(TokenType::IDENTIFIER, "s2", 5),
                Token(TokenType::CLOSE_BRACKET, ")", 5),
        };

        REQUIRE(tokens == expected);
    }


    SECTION("should throw logic error when invalid symbol used") {
        string source = "assign a; while w;\n"
                        "Select w such that Parent* (w, a)\n"
                        "pattern a (\"count\", _);\n"
                        "5 + 6;";
        REQUIRE_THROWS_AS(Tokenizer::tokenize(source), logic_error);
        REQUIRE_THROWS_WITH(Tokenizer::tokenize(source), "Invalid + symbol at line 4");
    }
}
