#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include "../Tokenizer/Token/SimpleToken.h"
#include "../Tokenizer/SimpleTokenizer.h"
#include "PKB.h"
#include "TNode.h"
#include "Parser.h"
#include "../Utils/StmtType.h"
#include <bits/stdc++.h>

using namespace simple;

class ParserImp: Parser {
private:
    unordered_map<int, simple::StmtType> stmtsTypeMap;
    unordered_map<int, vector<simple::SimpleToken>> stmtsTokenMap;

    void constructStmtsTokenMap(const vector<simple::SimpleToken>& tokens) {

    }

    void unordered_map<int, simple::StmtType>> constructStmtsTypeMap(const vector<simple::SimpleToken> tokens) {

    }

    vector<int> getStmtsListForContainer(int containerStmtNum) {

    }

    //Recursive resolve a program
    void resolveProgram(int stmtsNumber, vector<int> stmtsList) {
        int size = stmtsList.size();

        for (int i = 0; i < size - 1; i++) {
            stmtNum = stmtNums[i];
            simple::StmtType currType = stmtsTypeMap[stmtNum];
            simple::StmtType nextType = stmtsTypeMap[stmtNum + 1];

            if (isContainer(currType)) {
                // When the current statement is a container statement
                vector<int> newStmtsList = getStmtsListForContainer(stmtNum);
                // TODO: add stmts List as parent relationship
                resolveProgram(stmtNum + 1, newStmtsList);
                i += newStmtsList.size();
                // Update i with regards to the statement list for
            } else {
                //TODO: Add Follow relationship
            }
        }
    }

    vector<int> getStmtsNums(unordered_map<int, simple::StmtType> map) {
        vector<int> keySet;

        for (auto const& map: entry) {
            keySet.push_back(map.first);
        }

        int n = sizeof(keySet) / sizeof(keySet[0])
        return sort(keySet, keySet + n);
    }

    bool isContainer(StmtType type) {
        return type == if_stmt || type == while_stmt;
    }
public:

    int parse(string& inputs) final {

        //Tokenize the raw inputs
        vector<simple::SimpleToken> tokens = simple::SimpleTokenizer::tokenize(inputs);
        // Construct the required mapping
        constructStmtsTokenMap(tokens);
        constructStmtsTypeMap(tokens);

        // Build relationship using the map

        // Get the statements set
        vector<int> stmtNums = getStmtsNums(stmtsTypeMap);

        resolveProgram(stmtNums[0], stmtNums);

        return 0;
    }
};
