#include "CFGTable.h"

Graph CFGTable::cfg;

Graph CFGTable::getCFG()
{
    return cfg;
}

void CFGTable::setCFG(const Graph& graph)
{
    cfg = graph;
}

void CFGTable::clear()
{
    cfg.clear();
}
