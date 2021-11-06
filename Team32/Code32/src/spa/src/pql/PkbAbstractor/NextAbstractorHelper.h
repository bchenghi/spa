#ifndef GUARD_NEXT_ABSTRACTOR_HELPER_H
#define GUARD_NEXT_ABSTRACTOR_HELPER_H

typedef size_t ProcLine;

namespace pql {
    class NextAbstractorHelper {
    public:
        static Graph createNextStarGraph();
        static std::unordered_set<ProcLine> getNextStar(ProcLine, Graph);
        static std::unordered_set<ProcLine> getPrevStar(ProcLine, Graph);
        static Graph createNextBipStarGraph();
        static bool hasPath(unordered_map<size_t, unordered_set<CFGBipEdge>> edgeMap, size_t from, size_t to);
        static std::unordered_set<ProcLine> getNextBipStar(ProcLine, Graph);
        static std::unordered_set<ProcLine> getPrevBipStar(ProcLine, Graph);
        static std::vector<std::vector<size_t>> getAllPossibleStartLabel(StmtNum stmtNum);
    };
}

#endif //GUARD_NEXT_ABSTRACTOR_HELPER_H
