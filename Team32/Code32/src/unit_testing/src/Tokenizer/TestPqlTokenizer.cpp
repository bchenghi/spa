#include "Tokenizer/PqlTokenizer.h"
#include "Tokenizer/Token/PqlToken.h"
#include "catch.hpp"

#include <vector>
#include <stdexcept>
#include <string>

using pql::PqlToken;
using pql::PqlTokenizer;
using pql::TokenType;
using std::logic_error;
using std::string;
using std::vector;

TEST_CASE("PqlTokenizer", "[pql]") {
    SECTION("should tokenize pql query") {
        string source = "assign a; while w;\n"
                        "Select w such that Parent* (w, a)\n"
                        "pattern a (\"count\", _)";
        vector<PqlToken> tokens = PqlTokenizer::tokenize(source);
        vector<PqlToken> expected = {
            PqlToken(TokenType::kKeyWord, "assign", 1),
            PqlToken(TokenType::kIdentifier, "a", 1),
            PqlToken(TokenType::kStatementEnd, ";", 1),
            PqlToken(TokenType::kKeyWord, "while", 1),
            PqlToken(TokenType::kIdentifier, "w", 1),
            PqlToken(TokenType::kStatementEnd, ";", 1),
            PqlToken(TokenType::kKeyWord, "Select", 2),
            PqlToken(TokenType::kIdentifier, "w", 2),
            PqlToken(TokenType::kKeyWord, "such that", 2),
            PqlToken(TokenType::kKeyWord, "Parent*", 2),
            PqlToken(TokenType::kOpenBracket, "(", 2),
            PqlToken(TokenType::kIdentifier, "w", 2),
            PqlToken(TokenType::kSeparator, ",", 2),
            PqlToken(TokenType::kIdentifier, "a", 2),
            PqlToken(TokenType::kCloseBracket, ")", 2),
            PqlToken(TokenType::kKeyWord, "pattern", 3),
            PqlToken(TokenType::kIdentifier, "a", 3),
            PqlToken(TokenType::kOpenBracket, "(", 3),
            PqlToken(TokenType::kConstantString, "\"count\"", 3),
            PqlToken(TokenType::kSeparator, ",", 3),
            PqlToken(TokenType::kWildCard, "_", 3),
            PqlToken(TokenType::kCloseBracket, ")", 3),
        };

        REQUIRE(tokens == expected);
    }

    SECTION("should throw logic error when invalid symbol used") {
        string source = "assign a; while w;\n"
                        "Select w such that Parent* (w, a)\n"
                        "pattern a (\"count\", _);\n"
                        "5 + 6;";
        REQUIRE_THROWS_AS(PqlTokenizer::tokenize(source), logic_error);
        REQUIRE_THROWS_WITH(PqlTokenizer::tokenize(source), "Invalid + symbol at line 4");
    }
}
