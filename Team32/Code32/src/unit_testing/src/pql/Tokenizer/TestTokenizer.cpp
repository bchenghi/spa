#include "catch.hpp"

#include "pql/Tokenizer/Tokenizer.h"
#include "pql/Tokenizer/Token.h"

#include <stdexcept>
#include <string>
#include <vector>

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

    SECTION("should throw logic error when invalid symbol used") {
        string source = "assign a; while w;\n"
                        "Select w such that Parent* (w, a)\n"
                        "pattern a (\"count\", _);\n"
                        "5 + 6;";
        REQUIRE_THROWS_AS(Tokenizer::tokenize(source), logic_error);
        REQUIRE_THROWS_WITH(Tokenizer::tokenize(source), "Invalid + symbol at line 4");
    }
}
