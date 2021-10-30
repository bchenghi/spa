#include "CallTable.h"

CallTable* CallTable::callTablePtr = nullptr;

bool CallTable::addCall(ProcName proc1, ProcName proc2)
{
    return getInstance()->addOneToMany(CALL_MAP, proc1, proc2)
        && getInstance()->addOneToManyRev(CALL_REV_MAP, proc2, proc1);
}

bool CallTable::addCallStar(ProcName proc1, ProcName proc2)
{
    return getInstance()->addOneToMany(CALL_STAR_MAP, proc1, proc2)
        && getInstance()->addOneToManyRev(CALL_STAR_REV_MAP, proc2, proc1);
}

bool CallTable::isCall(ProcName proc1, ProcName proc2)
{
    return getInstance()->isOneToMany(CALL_MAP, proc1, proc2);
}

bool CallTable::isCallStar(ProcName proc1, ProcName proc2)
{
    return getInstance()->isOneToMany(CALL_STAR_MAP, proc1, proc2);
}

ListOfProcNames CallTable::getCall(ProcName proc1)
{
    return getInstance()->getOneToMany(CALL_MAP, proc1);
}

ListOfProcNames CallTable::getCalledBy(ProcName proc2)
{
    return getInstance()->getOneToManyRev(CALL_REV_MAP, proc2);
}

ListOfProcNames CallTable::getCallStar(ProcName proc1)
{
    return getInstance()->getOneToMany(CALL_STAR_MAP, proc1);
}

ListOfProcNames CallTable::getCalledStarBy(ProcName proc2)
{
    return getInstance()->getOneToManyRev(CALL_STAR_REV_MAP, proc2);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallMap()
{
    return getInstance()->getOneToManyMap(CALL_MAP);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallReverseMap()
{
    return getInstance()->getOneToManyRevMap(CALL_REV_MAP);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallStarMap()
{
    return getInstance()->getOneToManyMap(CALL_STAR_MAP);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallStarReverseMap()
{
    return getInstance()->getOneToManyRevMap(CALL_STAR_REV_MAP);
}

void CallTable::clear()
{
    getInstance()->clearAll();
}
