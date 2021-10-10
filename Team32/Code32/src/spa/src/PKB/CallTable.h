#ifndef GUARD_CALL_TABLE_H
#define GUARD_CALL_TABLE_H

#include "TypePreDefine.h"

#include <unordered_map>

class CallTable {
public:
    static bool addCall(ProcName proc1, ProcName proc2);
    static bool addCallStar(ProcName proc1, ProcName proc2);
    static bool isCall(ProcName proc1, ProcName proc2);
    static bool isCallStar(ProcName proc1, ProcName proc2);
    static ListOfProcNames getCall(ProcName proc1);
    static ListOfProcNames getCalledBy(ProcName proc2);
    static ListOfProcNames getCallStar(ProcName proc1);
    static ListOfProcNames getCalledStarBy(ProcName proc2);
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallMap();
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallReverseMap();
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallStarMap();
    static const std::unordered_map<ProcName, ListOfProcNames>& getCallStarReverseMap();
    static void clear();

private:
    static std::unordered_map<ProcName, ListOfProcNames> callMap;
    static std::unordered_map<ProcName, ListOfProcNames> reverseCallMap;
    static std::unordered_map<ProcName, ListOfProcNames> callStarMap;
    static std::unordered_map<ProcName, ListOfProcNames> reverseCallStarMap;
};

#endif // GUARD_CALL_TABLE_H
