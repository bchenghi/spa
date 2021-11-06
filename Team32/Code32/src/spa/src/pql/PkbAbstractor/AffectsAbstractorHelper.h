#ifndef GUARD_AFFECTS_ABSTRACTOR_HELPER_H
#define GUARD_AFFECTS_ABSTRACTOR_HELPER_H

namespace pql {
    class AffectsAbstractorHelper {
    public:
        static bool isAffects(StmtNum, StmtNum);
        static std::unordered_set<StmtNum> getAffectsStar(StmtNum, Graph);
        static std::unordered_set<StmtNum> getAffectedByStar(StmtNum, Graph);

        static bool isAffectsBipItself(StmtNum, VarName);
        static list<std::vector<StmtNum>> getAllPathsBip(StmtNum, StmtNum);
        static void getAllPathsBipHelper(StmtNum, StmtNum, size_t label, std::vector<std::vector<bool>>&, std::vector<StmtNum>&, list<std::vector<StmtNum>>&, std::vector<size_t>&);
        static bool isAffectsBip(StmtNum, StmtNum);
        static bool isVarNotModifiedByAssignment(list<vector<StmtNum>> listOfAllPaths, VarName varName, bool isCheckFirstNode);

        static Graph createAffectsBipStarGraph();
        static std::unordered_set<StmtNum> getAffectsBipStar(StmtNum, Graph);
        static std::unordered_set<StmtNum> getAffectedBipByStar(StmtNum, Graph);

    public:
        static bool isSameProc(StmtNum, StmtNum);
        static bool isModifiesUsed(StmtNum, StmtNum);
        static bool isAffectsItself(StmtNum, VarName);
        static list<std::vector<StmtNum>> getAllPaths(StmtNum, StmtNum);
        static void getAllPathsHelper(StmtNum, StmtNum, std::vector<size_t>&, std::vector<StmtNum>&, list<std::vector<StmtNum>>&);
        static bool isStmtModifiesVar(StmtNum, VarName);
        static bool isVarNotModifiedByAPathCheckFirstNode(list<std::vector<StmtNum>>, VarName);
        static bool isVarNotModifiedByAPathNotCheckFirstNode(list<std::vector<StmtNum>>, VarName);
        static Graph createAffectsStarGraph();
    };
}

#endif //GUARD_AFFECTS_ABSTRACTOR_HELPER_H
