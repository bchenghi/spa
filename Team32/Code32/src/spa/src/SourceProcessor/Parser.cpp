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
using namespace  std;

struct ParsingException: exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "Exception During Parsing the source program";
    }
};

class ParserImp: Parser {
private:
    unordered_map<int, simple::StmtType> stmtsTypeMap;
    unordered_map<int, vector<simple::SimpleToken>> stmtsTokenMap;

    void constructStmtsTokenMap(const vector<simple::SimpleToken>& tokens) {

    }

    void constructStmtsTypeMap(const vector<simple::SimpleToken>& tokens) {

    }

    vector<int> getStmtsListForContainer(int containerStmtNum) {

    }

    //Recursive resolve a program
    void resolveProgram(int stmtsNumber, vector<int> stmtsList) {
        int size = int(stmtsList.size());

        for (int i = 0; i < size - 1; i++) {
            int stmtNum = stmtsList[i];
            simple::StmtType currType = stmtsTypeMap[stmtNum];
            simple::StmtType nextType = stmtsTypeMap[stmtNum + 1];

            if (isContainer(currType)) {
                // When the current statement is a container statement
                vector<int> newStmtsList = getStmtsListForContainer(stmtNum);
                // TODO: add stmts List as parent relationship
                resolveProgram(stmtNum + 1, newStmtsList);
                i += int(newStmtsList.size());
                // Update i with regards to the statement list for
            } else {
                //TODO: Add Follow relationship
            }
        }
    }

    vector<int> getStmtsNums(unordered_map<int, simple::StmtType> map) {
        vector<int> keySet;
        for (auto const& imap: map) {
            keySet.push_back(imap.first);
        }

        int n = int(keySet.size());
        sort(keySet.begin(), keySet.end());
        return keySet;
    }

    bool isContainer(StmtType type) {
        return type == StmtType::if_stmt || type == StmtType :: while_stmt;
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

        try {
            resolveProgram(stmtNums[0], stmtNums);
        } catch (ParsingException e) {
            printf("%s", e.what());
        }

        return 0;
    }
};
