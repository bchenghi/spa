#ifndef GUARD_TYPE_PRE_DEFINE_H
#define GUARD_TYPE_PRE_DEFINE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

typedef size_t StmtNo;
typedef size_t VarIndex;
typedef size_t ProgLine;
typedef std::string ProcName;
typedef std::string VarName;
typedef std::unordered_set<std::string> ListOfProcNames;
typedef std::unordered_set<StmtNo> ListOfStmtNos;
typedef std::unordered_set<VarName> ListOfVarNames;
typedef std::unordered_set<int> ListOfConstants;
typedef std::unordered_set<ProgLine> ListOfProgLines;

#endif
