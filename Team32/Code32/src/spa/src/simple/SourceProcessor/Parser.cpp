#include "StatementParser.h"
#include "simple/Tokenizer/Token.h"
#include "simple/Tokenizer/Tokenizer.h"
#include "PKB/FollowTable.h"
#include "PKB/ParentTable.h"
#include "PKB/ProcTable.h"
#include "Utils/StmtType.h"
#include "Utils/ParserUtils.h"
#include "Parser.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <cassert>

using namespace simple;
using namespace std;

typedef simple::Token SimpleToken;
typedef simple::StmtType StmtType;
typedef simple::TokenType TokenType;
typedef vector<size_t> StmtsList;
typedef unordered_map<size_t, StmtType> StmtsTypeMap;
typedef unordered_map<size_t, vector<SimpleToken>> StmtsTokenMap, TokenLineMap;
typedef unordered_map<size_t, size_t> LineNextMap;
typedef unordered_map<size_t, string> StmtProcMap;
typedef unordered_map<size_t, vector<size_t>> ProcStmtListMap;
typedef vector<SimpleToken> TokenList;


void simple::Parser::validateProgramStructure(const TokenList &tokens) {
    stack<string> bracketValidationStack;

    for (const auto &token: tokens) {
        if (token.GetToken() == "}" && bracketValidationStack.empty()) {
            throwWithMessage("Program's brace doesn't match");
        }

        if (token.GetToken() == "}" && bracketValidationStack.top() == "{") {
            bracketValidationStack.pop();
        } else if (token.GetToken() == "{") {
            bracketValidationStack.push("{");
        } else {
            continue;
        }
    }

    if (!bracketValidationStack.empty()) {
        throwWithMessage("Program's brace doesn't match");
    }
}

void simple::Parser::constructStmtsTokenAndTypeMap(const TokenList &tokens) {
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
            stmtsTypeMap[currInvalidNum] = stmtType;
            stmtsTokenMap[currInvalidNum] = stmtTokenList;
            lineNextMap[last] = currInvalidNum;
            last = currInvalidNum;
            currInvalidNum--;
        }
    }
}

void simple::Parser::constructStmtProcMap(const TokenList &tokens) {
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

void simple::Parser::insertProcInformation() {
    unordered_set<string> seenProc;
    for (auto entry: stmtProcMap) {
        string currProc = entry.second;

        if (!seenProc.find(currProc)->empty()) {
            continue;
        }
        seenProc.insert(currProc);

        ProcTable::addProc(currProc, convertToSet(getStmtListForProc(currProc)));
    }
}

StmtsList simple::Parser::getStmtListForProc(const string &procName) {
    StmtsList stmtsList;

    for (const auto &entry: stmtProcMap) {
        string procNameNow = entry.second;
        size_t stmtNumber = entry.first;

        if (procName == procNameNow) {
            stmtsList.push_back(stmtNumber);
        }
    }

    return stmtsList;
}

string simple::Parser::getProcName(TokenList stmtTokens) {
    for (int i = 0; i < stmtTokens.size(); i++) {
        Token currToken = stmtTokens[i];

        if (currToken.GetToken() == "procedure") {
            return stmtTokens[i + 1].GetToken();
        }
    }

    throwWithoutToken("Procedure definition", stmtTokens[0].GetLineNumber());
    return "";
}

TokenList simple::Parser::generateTokensForNextStmt(TokenList tokens, int startIndex) {
    // TODO: Validate the line during generation of the token
    TokenList stmtTokenList;
    int nextIndex = 0;

    do {
        stmtTokenList.push_back(tokens[startIndex + nextIndex]);
        nextIndex++;
    } while (startIndex + nextIndex < tokens.size() && isStatementend(tokens[startIndex + nextIndex]));

    return stmtTokenList;
}

bool simple::Parser::isStatementend(Token token) {
    return token.GetTokenType() != TokenType::kOpenBrace &&
           token.GetTokenType() != TokenType::kCloseBrace &&
           token.GetTokenType() != TokenType::kStatementEnd;
}

// Get Type should be called only after validating the syntax
StmtType simple::Parser::getTypeForStmt(TokenList lineList) {
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
        } else if (currToken.GetToken() == "=") {
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

StmtsList simple::Parser::getStmtsListForContainer(size_t containerStmtNum) {
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
            } else if (token.GetToken() == "{") {
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
void simple::Parser::resolveProgram(StmtsList stmtsList) {
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
            for (auto stmtNum:newStmtsList) {
                ParentTable::addParent(stmtNum, convertToSet(newStmtsList));
            }

            resolveProgram(newStmtsList);
            i += int(newStmtsList.size());
            // Update i with regards to the statement list for

            if (stmtsTypeMap[stmtsList[i]] != StmtType::not_stmt ||
                stmtsTypeMap[stmtsList[i]] != StmtType::procedure_def) {
                FollowTable::addFollow(stmtNum, stmtsList[i]);
            }

        } else {
            //TODO: Add Follow relationship
            FollowTable::addFollow(stmtNum, stmtNum + 1);
            string procedureName = stmtProcMap[stmtNum];
        }
    }
}

unordered_set<size_t> simple::Parser::convertToSet(vector<size_t> v) {
    // Declaring the  set
    unordered_set<size_t> s;

    // Traverse the Vector
    for (int x : v) {

        // Insert each element
        // into the Set
        s.insert(x);
    }

    // Return the resultant Set
    return s;
}

vector<size_t> simple::Parser::getStmtsNums(StmtsTypeMap map) {
    vector<size_t> keySet;
    for (auto const &imap: map) {
        if (imap.first > 0) {
            keySet.push_back(imap.first);
        }
    }

    sort(keySet.begin(), keySet.end());
    return keySet;
}

bool simple::Parser::isContainer(StmtType type) {
    return type == StmtType::if_stmt || type == StmtType::while_stmt || type == StmtType::procedure_def;
}

void simple::Parser::parse(string &inputs) {

    //Tokenize the raw inputs
    vector<simple::Token> tokens = simple::Tokenizer::tokenize(inputs);

    validateProgramStructure(tokens);

    // Construct the required mapping
    constructStmtsTokenAndTypeMap(tokens);
    constructStmtProcMap(tokens);
    insertProcInformation();
    // Build relationship using the map
    // Get the statements set
    StmtsList stmtNums = getStmtsNums(stmtsTypeMap);

    try {
        resolveProgram(stmtNums);
    } catch (logic_error e) {
        printf("%s", e.what());
    }
}