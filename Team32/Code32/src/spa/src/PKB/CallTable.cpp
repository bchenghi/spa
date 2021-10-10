#include "CallTable.h"

using std::count;

std::unordered_map<ProcName, ListOfProcNames> CallTable::callMap;
std::unordered_map<ProcName, ListOfProcNames> CallTable::reverseCallMap;
std::unordered_map<ProcName, ListOfProcNames> CallTable::callStarMap;
std::unordered_map<ProcName, ListOfProcNames> CallTable::reverseCallStarMap;

bool CallTable::addCall(ProcName proc1, ProcName proc2)
{
    auto res1 = CallTable::callMap.find(proc1);
    auto res2 = CallTable::reverseCallMap.find(proc2);
    if (res1 != CallTable::callMap.end()) {
        CallTable::callMap[proc1].insert(proc2);
        if (res2 != CallTable::reverseCallMap.end()) {
            CallTable::reverseCallMap[proc2].insert(proc1);
        }
        else {
            CallTable::reverseCallMap[proc2] = ListOfProcNames();
            CallTable::reverseCallMap[proc2].insert(proc1);
        }
        return true;
    }
    else {
        CallTable::callMap[proc1] = ListOfProcNames();
        CallTable::callMap[proc1].insert(proc2);
        if (res2 != CallTable::reverseCallMap.end()) {
            CallTable::reverseCallMap[proc2].insert(proc1);
        }
        else {
            CallTable::reverseCallMap[proc2] = ListOfProcNames();
            CallTable::reverseCallMap[proc2].insert(proc1);
        }
        return true;
    }
    return false;
}

bool CallTable::addCallStar(ProcName proc1, ProcName proc2)
{
    auto res1 = CallTable::callStarMap.find(proc1);
    auto res2 = CallTable::reverseCallStarMap.find(proc2);
    if (res1 != CallTable::callStarMap.end()) {
        CallTable::callStarMap[proc1].insert(proc2);
        if (res2 != CallTable::reverseCallStarMap.end()) {
            CallTable::reverseCallStarMap[proc2].insert(proc1);
        }
        else {
            CallTable::reverseCallStarMap[proc2] = ListOfProcNames();
            CallTable::reverseCallStarMap[proc2].insert(proc1);
        }
        return true;
    }
    else {
        CallTable::callStarMap[proc1] = ListOfProcNames();
        CallTable::callStarMap[proc1].insert(proc2);
        if (res2 != CallTable::reverseCallStarMap.end()) {
            CallTable::reverseCallStarMap[proc2].insert(proc1);
        }
        else {
            CallTable::reverseCallStarMap[proc2] = ListOfProcNames();
            CallTable::reverseCallStarMap[proc2].insert(proc1);
        }
        return true;
    }
    return false;
}

bool CallTable::isCall(ProcName proc1, ProcName proc2)
{
    auto res = CallTable::callMap.find(proc1);
    if (res != CallTable::callMap.end()) {
        if (res->second.count(proc2)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool CallTable::isCallStar(ProcName proc1, ProcName proc2)
{
    auto res = CallTable::callStarMap.find(proc1);
    if (res != CallTable::callStarMap.end()) {
        if (res->second.count(proc2)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

ListOfProcNames CallTable::getCall(ProcName proc1)
{
    auto res = CallTable::callMap.find(proc1);
    if (res != CallTable::callMap.end()) {
        return res->second;
    }
    else {
        return ListOfProcNames();
    }
}

ListOfProcNames CallTable::getCalledBy(ProcName proc2)
{
    auto res = CallTable::reverseCallMap.find(proc2);
    if (res != CallTable::reverseCallMap.end()) {
        return res->second;
    }
    else {
        return ListOfProcNames();
    }
}

ListOfProcNames CallTable::getCallStar(ProcName proc1)
{
    auto res = CallTable::callStarMap.find(proc1);
    if (res != CallTable::callStarMap.end()) {
        return res->second;
    }
    else {
        return ListOfProcNames();
    }
}

ListOfProcNames CallTable::getCalledStarBy(ProcName proc2)
{
    auto res = CallTable::reverseCallStarMap.find(proc2);
    if (res != CallTable::reverseCallStarMap.end()) {
        return res->second;
    }
    else {
        return ListOfProcNames();
    }
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallMap()
{
    return callMap;
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallReverseMap()
{
    return reverseCallMap;
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallStarMap()
{
    return callStarMap;
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallStarReverseMap()
{
    return reverseCallStarMap;
}

void CallTable::clear()
{
    callMap.clear();
    reverseCallMap.clear();
    callStarMap.clear();
    reverseCallStarMap.clear();
}
