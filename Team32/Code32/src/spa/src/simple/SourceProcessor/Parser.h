#ifndef GUARD_PARSER_H
#define GUARD_PARSER_H
#include "Parser.h"
#include "StatementParser.h"
#include "simple/Tokenizer/Token.h"
#include "simple/Tokenizer/Tokenizer.h"
#include "PKB/FollowTable.h"
#include "PKB/ParentTable.h"
#include "PKB/ProcTable.h"
#include "Utils/StmtType.h"
#include "Utils/ParserUtils.h"
#include "CFG.h"

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
typedef unordered_map<size_t, vector<SimpleToken>> StmtsTokenMap;
typedef unordered_map<size_t, size_t> LineNextMap;
typedef unordered_map<size_t, string> StmtProcMap;
typedef vector<SimpleToken> TokenList;

namespace simple {
    class Parser{
    public:
        void parse(std::string& source_program);

        Graph getCFG();

    private:
        StmtsTypeMap stmtsTypeMap;
        StmtsTokenMap stmtsTokenMap; // Use negative number to denote invalid statement like procedure definition and else
        StmtProcMap  stmtProcMap;
        LineNextMap lineNextMap; // Map the current line to the next line， used when get the container statement list, since bracket needs to be considered
        StatementParser stmtParser;
        CFG cfg;
        CFG cfgBip;
        size_t stmtsSize;

        void validateProgramStructure(const TokenList& tokens);
        void constructStmtsTokenAndTypeMap(const TokenList& tokens);
        void constructStmtProcMap(const TokenList& tokens);
        void insertProcInformation();
        StmtsList getStmtListForProc(const string& procName);
        string getProcName(TokenList stmtTokens);
        TokenList generateTokensForNextStmt(TokenList tokens, int startIndex);
        bool isStatementEnd(const Token& token);
        StmtType getTypeForStmt(TokenList lineList);
        StmtsList getStmtsListForContainer(size_t containerStmtNum);
        void resolveProgram(StmtsList stmtsList);
        unordered_set<size_t> convertToSet(const vector<size_t>& v);
        vector<size_t> getStmtsNums(const StmtsTypeMap& map);
        bool isContainer(StmtType type);
        StmtsList getTotalListForContainer(size_t containerStmtNum);
        bool isCrossingBlock(size_t start, size_t end);
        size_t generatingCFGForProgram(StmtsList stmtList);
        vector<StmtsList> getIfElseList(StmtNo ifStmtNum);
        void populateNextTable();
        void generateCFGBip();
    };
}

#endif
