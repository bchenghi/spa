#include "StatementParser.h"
#include "simple/Tokenizer/Token.h"
#include "simple/Tokenizer/Tokenizer.h"
#include "PKB/FollowTable.h"
#include "PKB/ParentTable.h"
#include "PKB/ProcTable.h"
#include "PKB/CFGBipTable.h"
#include "Utils/StmtType.h"
#include "Utils/ParserUtils.h"
#include "PKB/CFGTable.h"
#include "PKB/NextTable.h"
#include "PKB/CallStmtTable.h"
#include "CFGBip.h"
#include "Parser.h"
#include "Utils/GraphUtils.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <queue>
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


void simple::Parser::validateProgramStructure(const TokenList& tokens) {
    stack<string> bracketValidationStack;

    for (const auto &token: tokens) {
        if (token.getToken() == "}" && bracketValidationStack.empty()) {
            throwWithMessage("[Parser] Program's brace doesn't match");
        }

        if (token.getToken() == "}" && bracketValidationStack.top() == "{") {
            bracketValidationStack.pop();
        } else if (token.getToken() == "{") {
            bracketValidationStack.push("{");
        } else {
            continue;
        }
    }

    if (!bracketValidationStack.empty()) {
        throwWithMessage("[Parser] Program's brace doesn't match");
    }
}

void simple::Parser::constructStmtsTokenAndTypeMap(const TokenList& tokens) {
    int currStmtNum = 1;
    int currInvalidNum = -1;
    int startIndex = 0; // Start index in the token list
    size_t last = 0;

    while (startIndex < tokens.size()) {
        TokenList stmtTokenList = generateTokensForNextStmt(tokens, startIndex);
        startIndex += int(stmtTokenList.size());

        StmtType stmtType = getTypeForStmt(stmtTokenList);

        if (stmtType != StmtType::NOT_STMT && stmtType != StmtType::PROCEDURE_DEF) {
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

        lineNextMap[last] = 0; // Mark the end
    }
}

void simple::Parser::constructStmtProcMap(const TokenList& tokens) {
    int startIndex = 0;
    string currProcName;
    int currStmtNum = 1;
    unordered_set<string> processedProcs;

    while (startIndex < tokens.size()) {
        TokenList lineToken = generateTokensForNextStmt(tokens, startIndex);
        StmtType type = getTypeForStmt(lineToken);
        startIndex += int(lineToken.size());

        if (type == StmtType::PROCEDURE_DEF) {
            currProcName = getProcName(lineToken);

            if (processedProcs.find(currProcName) != processedProcs.end())
                throwWithMessage("Duplicate procedure: " + currProcName);

            processedProcs.insert(currProcName);
            continue;
        }

        if (type != StmtType::NOT_STMT) {
            assert(!currProcName.empty());
            stmtProcMap[currStmtNum] = currProcName;
            currStmtNum++;
        }
    }
}

void simple::Parser::insertProcInformation() {
    unordered_set<string> seenProc;
    for (const auto& entry : stmtProcMap) {
        string currProc = entry.second;

        if (seenProc.find(currProc) != seenProc.end()) {
            continue;
        }
        seenProc.insert(currProc);

        ProcTable::addProc(currProc, convertToSet(getStmtListForProc(currProc)));
    }
}

StmtsList simple::Parser::getStmtListForProc(const string& procName) {
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

        if (currToken.getToken() == "procedure") {
            return stmtTokens[i + 1].getToken();
        }
    }

    throwWithoutToken("Procedure definition", stmtTokens[0].getLineNumber());
    return "";
}

TokenList simple::Parser::generateTokensForNextStmt(TokenList tokens, int startIndex) {
    TokenList stmtTokenList;
    int nextIndex = -1;
    bool isElse = false;
    do {
        nextIndex++;
        SimpleToken curr = tokens[startIndex + nextIndex];
        stmtTokenList.push_back(curr);
        if (startIndex + nextIndex < tokens.size() - 2) {
            isElse = curr.getTokenType() == TokenType::CLOSE_BRACE
                    && tokens[startIndex + nextIndex + 1].getToken() == "else"
                    && tokens[startIndex + nextIndex + 2].getTokenType() == TokenType::OPEN_BRACE;
        }
    } while (isElse || startIndex + nextIndex < tokens.size() && !isStatementEnd(tokens[startIndex + nextIndex]));

    return stmtTokenList;
}

bool simple::Parser::isStatementEnd(const Token& token) {
    return token.getTokenType() == TokenType::OPEN_BRACE ||
            token.getTokenType() == TokenType::CLOSE_BRACE ||
            token.getTokenType() == TokenType::STATEMENT_END;
}

// Get Type should be called only after validating the syntax
StmtType simple::Parser::getTypeForStmt(TokenList lineList) {
    try {
        SimpleToken secondToken = lineList.at(1);

        if (secondToken.getTokenType() == TokenType::ASSIGNMENT)
            return StmtType::ASSIGN;
    } catch (const logic_error& err) { }

    for (const SimpleToken& currToken : lineList) {
        // Simple case for not a statement
        if (currToken.getToken() == "procedure")
            return StmtType::PROCEDURE_DEF;
        if (currToken.getToken() == "while")
            return StmtType::WHILE_STMT;
        if (currToken.getToken() == "if")
            return StmtType::IF_STMT;
        if (currToken.getToken() == "read")
            return StmtType::READ_STMT;
        if (currToken.getToken() == "print")
            return StmtType::PRINT_STMT;
        if (currToken.getToken() == "call")
            return StmtType::CALL_STMT;
        if (currToken.getToken() == "else")
            return StmtType::NOT_STMT;
    }
    return StmtType::NOT_STMT;
}

StmtsList simple::Parser::getTotalListForContainer(size_t containerStmtNum) {
    StmtsList stmtsList;
    vector<string> bracketValidation;
    bracketValidation.emplace_back("{");
    size_t currStmtNum = lineNextMap[containerStmtNum];

    // Each iteration iterate through a statement (valid or invalid), invalid need to process the bracket
    while (!bracketValidation.empty()) {
        TokenList currStmtTokens = stmtsTokenMap[currStmtNum];
        StmtType type = getTypeForStmt(currStmtTokens);

        for (const Token& token : currStmtTokens) {
            if (token.getToken() == "}" && bracketValidation.at(bracketValidation.size() - 1) == "{") {
                bracketValidation.pop_back();
            } else if (token.getToken() == "{") {
                bracketValidation.emplace_back("{");
            } else {
                continue;
            }
        }
        if (type != StmtType::NOT_STMT && type != StmtType::PROCEDURE_DEF) {
            stmtsList.push_back(currStmtNum);
        }

        currStmtNum = lineNextMap[currStmtNum];
    }
    return stmtsList;
}

StmtsList simple::Parser::getStmtsListForContainer(size_t containerStmtNum) {
    StmtsList stmtsList;
    vector<string> bracketValidation;
    bracketValidation.emplace_back("{");
    size_t currStmtNum = lineNextMap[containerStmtNum];

    // Each iteration iterate through a statement (valid or invalid), invalid need to process the bracket
    while (!bracketValidation.empty()) {
        TokenList currStmtTokens = stmtsTokenMap[currStmtNum];
        StmtType type = getTypeForStmt(currStmtTokens);
        bool isContainer = type == StmtType::IF_STMT || type == StmtType::WHILE_STMT;

        for (const auto& token : currStmtTokens) {
           if (token.getToken() == "}" && bracketValidation.at(bracketValidation.size() - 1) == "{") {
               bracketValidation.pop_back();
           } else if (token.getToken() == "{") {
               bracketValidation.emplace_back("{");
           } else {
               continue;
           }
        }

        if (bracketValidation.size() == 1 && bracketValidation.at(bracketValidation.size() - 1) == "{"
        && int(currStmtNum) > 0) {
            stmtsList.push_back(currStmtNum);
        }

        if (bracketValidation.size() == 2 && isContainer) {
            stmtsList.push_back(currStmtNum);
        }

        currStmtNum = lineNextMap[currStmtNum];
    }

    return stmtsList;
}

// Recursive resolve a program
void simple::Parser::resolveProgram(StmtsList stmtsList) {
    int size = int(stmtsList.size());
    for (int i = 0; i < size; i++) {
        size_t stmtNum = stmtsList[i];
        simple::StmtType currType = stmtsTypeMap[stmtNum];
        TokenList tokenList = stmtsTokenMap[stmtNum];
        string procedureName = stmtProcMap[stmtNum];

        if (getTypeForStmt(tokenList) != StmtType::NOT_STMT &&
            getTypeForStmt(tokenList) != StmtType::PROCEDURE_DEF) {
            simple::Statement statement = {tokenList, stmtNum, procedureName};
            stmtParser.parse(statement);
        } else {
            continue;
        }

        if (isContainer(currType)) {
            // When the current statement is a container statement
            vector<size_t> childStmtsList = getStmtsListForContainer(stmtNum);

            ParentTable::addParent(stmtNum, convertToSet(childStmtsList));
            StmtsList newStmtsList = getTotalListForContainer(stmtNum);

            resolveProgram(newStmtsList);

            i += int(getTotalListForContainer(stmtNum).size());

            if (i + 1 < stmtsList.size() && isCrossingBlock(stmtNum, stmtsList[i + 1])) {
                continue;
            }
            if (i+ 1 < stmtsList.size() && (stmtsTypeMap[stmtsList[i + 1]] != StmtType::NOT_STMT ||
                stmtsTypeMap[stmtsList[i + 1]] != StmtType::PROCEDURE_DEF)) {
                    FollowTable::addFollow(stmtNum, stmtsList[i + 1]);
            }

        } else {
            if (lineNextMap[stmtNum] == stmtNum + 1) {
                FollowTable::addFollow(stmtNum, stmtNum + 1);
            }
        }
    }
}

unordered_set<size_t> simple::Parser::convertToSet(const vector<size_t>& v) {
    // Declaring the  set
    unordered_set<size_t> s;

    // Traverse the Vector
    for (size_t x : v) {

        // Insert each element
        // into the Set
        s.insert(x);
    }

    // Return the resultant Set
    return s;
}

vector<size_t> simple::Parser::getStmtsNums(const StmtsTypeMap& map) {
    vector<size_t> keySet;
    for (auto const &imap: map) {
        if (int(imap.first) > 0) {
            keySet.push_back(imap.first);
        }
    }

    sort(keySet.begin(), keySet.end());
    return keySet;
}

bool simple::Parser::isContainer(StmtType type) {
    return type == StmtType::IF_STMT || type == StmtType::WHILE_STMT || type == StmtType::PROCEDURE_DEF;
}

void simple::Parser::parse(string &inputs) {
    // Tokenize the raw inputs
    vector<simple::Token> tokens = simple::Tokenizer::tokenize(inputs);

    validateProgramStructure(tokens);

    // Construct the required mapping
    constructStmtsTokenAndTypeMap(tokens);
    constructStmtProcMap(tokens);
    insertProcInformation();

    // Build relationship using the map
    // Get the statements set
    StmtsList stmtNums = getStmtsNums(stmtsTypeMap);
    stmtsSize = stmtNums.size();
    resolveProgram(stmtNums);

    cfg.initCFG(stmtNums.size());
    generatingCFGForProgram(stmtNums);

    CFGTable::setCFG(cfg.getCFG());

    populateNextTable(cfg.getCFG(), "Next", stmtsSize);
}

bool Parser::isCrossingBlock(size_t start, size_t end) {
    vector<string> bracketValidation;

    bracketValidation.emplace_back("{");
    size_t curr = start;

    while (curr != end) {
        TokenList currStmtTokens = stmtsTokenMap[curr];

        for (const auto& token : currStmtTokens) {
            if (token.getToken() == "}" && bracketValidation.at(bracketValidation.size() - 1) == "{") {
                bracketValidation.pop_back();
            } else if (token.getToken() == "{") {
                bracketValidation.emplace_back("{");
            } else {
                continue;
            }

            if (bracketValidation.empty()) {
                return true;
            }
        }

        curr = lineNextMap[curr];
    }

    return false;
}

size_t Parser::generatingCFGForProgram(StmtsList stmtList) {
    int size = int(stmtList.size());
    size_t lastNode = -1;
    string currProc = stmtProcMap[stmtList[0]];

    for (int i = 0; i < size; i++) {
        size_t stmtNum = stmtList[i];
        simple::StmtType currType = stmtsTypeMap[stmtNum];
        TokenList tokenList = stmtsTokenMap[stmtNum];
        string procedureName = stmtProcMap[stmtNum];
        if (procedureName != currProc) {
            lastNode = -1;
            currProc = procedureName;
        }
        if (lastNode != -1) {
            cfg.addEdge(lastNode, stmtNum);
        }
        if (isContainer(currType)) {
            if (currType == StmtType::WHILE_STMT) {
                // Handling while statement
                StmtsList newStmtsList = getTotalListForContainer(stmtNum);

                if (newStmtsList.empty()) {
                    lastNode = stmtNum;
                    continue;
                }
                cfg.addEdge(stmtNum, newStmtsList[0]);

                lastNode = generatingCFGForProgram(newStmtsList);

                i += int(getTotalListForContainer(stmtNum).size());

                // Connect back to the while
                cfg.addEdge(lastNode, stmtNum);

                // Update lastNode to head of While.
                lastNode = stmtNum;
            } else {
                // Handling if statement
                vector<StmtsList> ifElseList = getIfElseList(stmtNum);
                StmtsList ifList = ifElseList[0];
                StmtsList elseList = ifElseList[1];

                if (ifList.empty() && elseList.empty()) {
                    lastNode = stmtNum;
                    continue;
                }

                size_t lastIfNode;
                size_t lastElseNode;

                if (!ifList.empty()) {
                    cfg.addEdge(stmtNum, ifList[0]);
                    lastIfNode = generatingCFGForProgram(ifList);
                } else {
                    lastIfNode = stmtNum;
                }

                if (!elseList.empty()) {
                    cfg.addEdge(stmtNum, elseList[0]);
                    lastElseNode = generatingCFGForProgram(elseList);
                } else {
                    lastElseNode = stmtNum;
                }

                size_t dummyNodeNum = cfg.addDummyNode();
                cfg.addEdge(lastIfNode, dummyNodeNum);
                cfg.addEdge(lastElseNode, dummyNodeNum);

                lastNode = dummyNodeNum;
                i += int(getTotalListForContainer(stmtNum).size());
            }
        } else {
            lastNode = stmtNum;
        }
    }

    return lastNode;
}

vector<StmtsList> Parser::getIfElseList(StmtNo ifStmtNum) {
    vector<StmtsList> res;

    StmtsList ifList;
    StmtsList elseList;
    bool isIf = true;
    vector<string> bracketValidation;
    bracketValidation.emplace_back("{");
    size_t currStmtNum = lineNextMap[ifStmtNum];

    // Each iteration iterate through a statement (valid or invalid), invalid need to process the bracket
    while (!bracketValidation.empty()) {
        TokenList currStmtTokens = stmtsTokenMap[currStmtNum];
        StmtType type = getTypeForStmt(currStmtTokens);

        for (const Token& token : currStmtTokens) {
            if (token.getToken() == "else" && bracketValidation.empty()) {
                isIf = false;
            }

            if (token.getToken() == "}" && bracketValidation.at(bracketValidation.size() - 1) == "{") {
                bracketValidation.pop_back();
            } else if (token.getToken() == "{") {
                bracketValidation.emplace_back("{");
            } else {
                continue;
            }
        }

        if (type != StmtType::NOT_STMT && type != StmtType::PROCEDURE_DEF) {
            if (isIf) {
                ifList.push_back(currStmtNum);
            } else {
                elseList.push_back(currStmtNum);
            }
        }

        currStmtNum = lineNextMap[currStmtNum];
    }

    res.push_back(ifList);
    res.push_back(elseList);
    return res;
}

Graph Parser::getCFG() {
    return cfg.getCFG();
}