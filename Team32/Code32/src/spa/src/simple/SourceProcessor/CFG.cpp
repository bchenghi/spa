#include "CFG.h"

void CFG::addEdge(size_t from_stmt, size_t to_stmt) {
    graph.at(from_stmt - 1).at(to_stmt - 1) = 1;
}

Graph CFG::getCFG() {
    return graph;
}

void CFG::initCFG(size_t size) {
    for (int i = 0; i < size; i++) {
        vector<size_t> row;
        for (int j = 0; j < size; j++) {
            row.push_back(0);
        }
        graph.push_back(row);
    }
}

size_t CFG::addDummyNode() {
    // Returns the node number to represent dummy node
    for (auto & i : graph) {
        i.push_back(0);
    }

    vector<size_t> newRow;
    for (int i = 0; i <= graph.size(); i++) {
        newRow.push_back(0);
    }

    graph.push_back(newRow);

    return graph.size();
}
