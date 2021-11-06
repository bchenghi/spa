#include "PkbAbstractorHelper.h"
#include "PkbAbstractor.h"
#include <algorithm>

using std::unordered_map;

unordered_map<Value, Graph> pql::PkbAbstractorHelper::graphsMap;

bool pql::PkbAbstractorHelper::isNum(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

Graph pql::PkbAbstractorHelper::initGraph(int size) {
    Graph graph;
    graph.reserve(size);

    for (int i = 0; i < size; i++) {
        vector<size_t> row;
        row.reserve(size);
        for (int j = 0; j < size; j++) {
            row.push_back(0);
        }
        graph.push_back(row);
    }
    return graph;
}

Graph pql::PkbAbstractorHelper::getGraph(Value graphName) {
    auto res = PkbAbstractorHelper::graphsMap.find(graphName);
    if (res != PkbAbstractorHelper::graphsMap.end()) {
        return res->second;
    }
    else {
        return Graph();
    }
}

void pql::PkbAbstractorHelper::addGraph(Value graphName, Graph graph) {
    auto res = PkbAbstractorHelper::graphsMap.find(graphName);
    if (res == PkbAbstractorHelper::graphsMap.end()) {
        PkbAbstractorHelper::graphsMap[graphName] = graph;
    }
}

void pql::PkbAbstractorHelper::clearGraphs() {
    PkbAbstractorHelper::graphsMap.clear();
}



