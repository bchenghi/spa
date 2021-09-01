#include "catch.hpp"
#include "pql/Tokenizer/Tokenizer.h"
#include "pql/Tokenizer/Token.h"

#include <vector>
#include <stdexcept>
#include <string>

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
            Token(TokenType::kKeyWord, "assign", 1),
            Token(TokenType::kIdentifier, "a", 1),
            Token(TokenType::kStatementEnd, ";", 1),
            Token(TokenType::kKeyWord, "while", 1),
            Token(TokenType::kIdentifier, "w", 1),
            Token(TokenType::kStatementEnd, ";", 1),
            Token(TokenType::kKeyWord, "Select", 2),
            Token(TokenType::kIdentifier, "w", 2),
            Token(TokenType::kKeyWord, "such that", 2),
            Token(TokenType::kKeyWord, "Parent*", 2),
            Token(TokenType::kOpenBracket, "(", 2),
            Token(TokenType::kIdentifier, "w", 2),
            Token(TokenType::kSeparator, ",", 2),
            Token(TokenType::kIdentifier, "a", 2),
            Token(TokenType::kCloseBracket, ")", 2),
            Token(TokenType::kKeyWord, "pattern", 3),
            Token(TokenType::kIdentifier, "a", 3),
            Token(TokenType::kOpenBracket, "(", 3),
            Token(TokenType::kConstantString, "\"count\"", 3),
            Token(TokenType::kSeparator, ",", 3),
            Token(TokenType::kWildCard, "_", 3),
            Token(TokenType::kCloseBracket, ")", 3),
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
