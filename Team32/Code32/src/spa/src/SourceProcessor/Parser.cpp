#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include "../simple/Tokenizer/Token.h"
#include "../simple/Tokenizer/Tokenizer.h"
#include "PKB.h"
#include "TNode.h"
#include "Parser.h"
#include "../Utils/StmtType.h"
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <StatementParser.h>
#include "../Utils/ParserUtils.h"

using namespace simple;
using namespace std;

typedef simple::Token SimpleToken;
typedef simple::StmtType StmtType;
typedef simple::TokenType TokenType;
typedef vector<size_t> StmtsList;
typedef unordered_map<size_t , StmtType> StmtsTypeMap;
typedef unordered_map<size_t , vector<SimpleToken>> StmtsTokenMap,TokenLineMap;
typedef unordered_map<size_t , size_t> LineNextMap;
typedef unordered_map<size_t , string> StmtProcMap;
typedef vector<SimpleToken> TokenList;


// This class is built on the assumption that only have one procedure
class ParserImp: Parser {
private:
    StmtsTypeMap stmtsTypeMap;
    StmtsTokenMap stmtsTokenMap; // Use negative number to denote invalid statement like procedure definition and else
    StmtProcMap  stmtProcMap;
    LineNextMap lineNextMap; // Map the current line to the next line， used when get the container statement list, since bracket needs to be considered
    StatementParser stmtParser;

    void validateProgramStructure(const TokenList& tokens) {
        stack<string> bracketValidationStack;

        for (const auto& token: tokens) {
            if (token.GetToken() == "}" && bracketValidationStack.empty()){
                throwWithMessage("Program's brace doesn't match");
            }

            if (token.GetToken() == "}" && bracketValidationStack.top() == "{") {
                bracketValidationStack.pop();
            } else if (token.GetToken() == "{"){
                bracketValidationStack.push("{");
            } else {
                continue;
            }
        }

        if (!bracketValidationStack.empty()) {
            throwWithMessage("Program's brace doesn't match");
        }
    }

    void constructStmtsTokenAndTypeMap(const TokenList& tokens) {
        int currStmtNum = 1;
        int currInvalidNum = -1;
        int startIndex = 0; // Start index in the token list
        size_t last = 0;

        while (startIndex < tokens.size()) {
            TokenList stmtTokenList = generateTokensForNextStmt(tokens, startIndex);
            startIndex += int(stmtTokenList.size());

            StmtType stmtType = getTypeForStmt(stmtTokenList);

            if (stmtType != StmtType::not_stmt && stmtType != StmtType::procedure_def) {
                stmtsTypeMap[currStmtNum] = stmtType;
                stmtsTokenMap[currStmtNum] = stmtTokenList;
                lineNextMap[last] = currStmtNum;
                last = currStmtNum;
                currStmtNum++;
            } else {
                stmtsTypeMap[currInvalidNum]  = stmtType;
                stmtsTokenMap[currInvalidNum] = stmtTokenList;
                lineNextMap[last] = currInvalidNum;
                last = currInvalidNum;
                currInvalidNum--;
            }
        }
    }

    void constructStmtProcMap(const TokenList& tokens) {
        int startIndex = 0;
        string currProcName;
        int currStmtNum = 1;

        while (startIndex < tokens.size()) {
            TokenList lineToken = generateTokensForNextStmt(tokens, startIndex);
            StmtType type = getTypeForStmt(lineToken);
            startIndex++;

            if (type == StmtType::procedure_def) {
                currProcName = getProcName(lineToken);
                continue;
            }

            if (type != StmtType::not_stmt) {
                assert(!currProcName.empty());
                stmtProcMap[currStmtNum] = currProcName;
                currStmtNum++;
            }
        }
    }

    string getProcName(TokenList stmtTokens) {
        for (int i = 0; i < stmtTokens.size(); i++) {
            Token currToken = stmtTokens[i];

            if (currToken.GetToken() == "procedure") {
                return stmtTokens[i + 1].GetToken();
            }
        }

        throwWithoutToken("Procedure definition", stmtTokens[0].GetLineNumber());
    }

    TokenList generateTokensForNextStmt(TokenList tokens, int startIndex) {
        // TODO: Validate the line during generation of the token
        TokenList stmtTokenList;
        int nextIndex = 0;

        do {
            stmtTokenList.push_back(tokens[startIndex + nextIndex]);
            nextIndex++;
        } while (startIndex + nextIndex < tokens.size() && isStatementend(tokens[startIndex + nextIndex]));

        return stmtTokenList;
    }

    bool isStatementend(Token token) {
        return token.GetTokenType() != TokenType::kOpenBrace &&
        token.GetTokenType() != TokenType::kCloseBrace &&
        token.GetTokenType() != TokenType::kStatementEnd;
    }

    // Get Type should be called only after validating the syntax
    StmtType getTypeForStmt(TokenList lineList) {
        for (int i = 0; i < lineList.size(); i++) {
            SimpleToken currToken = lineList[0];

            // Simple case for not a statement
            if (currToken.GetToken() == "procedure") {
                return StmtType::procedure_def;
            } else if (currToken.GetToken() == "else") {
                return StmtType::not_stmt;
            } else if (currToken.GetToken() == "while") {
                    return StmtType::while_stmt;
            } else if (currToken.GetToken() == "if") {
                return StmtType::if_stmt;
            } else if (currToken.GetToken() == "="){
                return StmtType::assign;
            } else if (currToken.GetToken() == "read") {
                return StmtType::read_stmt;
            } else if (currToken.GetToken() == "print") {
                return StmtType::print_stmt;
            } else {
                continue;
            }
        }
        return StmtType::not_stmt;
    }

    StmtsList getStmtsListForContainer(size_t containerStmtNum) {
        StmtsList stmtsList;
        stack<string> bracketValidationStack;
        bracketValidationStack.push("{");
        size_t currStmtNum = lineNextMap[containerStmtNum];

        // Each iteration iterate through a statement (valid or invalid), invalid need to process the bracket
        while (!bracketValidationStack.empty()) {
            TokenList currStmtTokens = stmtsTokenMap[currStmtNum];

            for (auto token: currStmtTokens) {
                if (token.GetToken() == "}" && bracketValidationStack.top() == "{") {
                    bracketValidationStack.pop();
                } else if (token.GetToken() == "{"){
                    bracketValidationStack.push("{");
                } else {
                    continue;
                }
            }

            if (bracketValidationStack.size() == 1 && bracketValidationStack.top() == "{") {
                stmtsList.push_back(currStmtNum);
            }

            currStmtNum = lineNextMap[currStmtNum];
        }

        return stmtsList;
    }

    //Recursive resolve a program
    void resolveProgram(StmtsList stmtsList) {
        int size = int(stmtsList.size());

        for (int i = 0; i < size - 1; i++) {
            size_t stmtNum = stmtsList[i];
            simple::StmtType currType = stmtsTypeMap[stmtNum];
            simple::StmtType nextType = stmtsTypeMap[stmtNum + 1];
            TokenList tokenList = stmtsTokenMap[stmtNum];
            string procedureName = stmtProcMap[stmtNum];
            simple::Statement statement = {tokenList, stmtNum, procedureName};
            stmtParser.parse(statement);

            if (isContainer(currType)) {
                // When the current statement is a container statement
                // TODO: Validate the container statement
                vector<size_t> newStmtsList = getStmtsListForContainer(stmtNum);
                // TODO: add stmts List as parent relationship
                resolveProgram( newStmtsList);
                i += int(newStmtsList.size());
                // Update i with regards to the statement list for
            } else {
                //TODO: Add Follow relationship
                // TODO: Make use of the statement parser
                string procedureName = stmtProcMap[stmtNum];
            }
        }
    }

    vector<size_t> getStmtsNums(StmtsTypeMap map) {
        vector<size_t> keySet;
        for (auto const& imap: map) {
            if (imap.first > 0) {
                keySet.push_back(imap.first);
            }
        }

        sort(keySet.begin(), keySet.end());
        return keySet;
    }

    bool isContainer(StmtType type) {
        return type == StmtType::if_stmt || type == StmtType :: while_stmt || type == StmtType::procedure_def;
    }
public:

    int parse(string& inputs) final {

        //Tokenize the raw inputs
        vector<simple::Token> tokens = simple::Tokenizer::tokenize(inputs);

        validateProgramStructure(tokens);

        // Construct the required mapping
        constructStmtsTokenAndTypeMap(tokens);
        constructStmtProcMap(tokens);

        // Build relationship using the map

        // Get the statements set
        StmtsList stmtNums = getStmtsNums(stmtsTypeMap);

        try {
            resolveProgram(stmtNums);
            return 0;
        } catch (logic_error e) {
            printf("%s", e.what());
        }
    }
};
