#include "CallTable.h"

CallTable* CallTable::call_table_ptr = nullptr;

bool CallTable::addCall(ProcName proc1, ProcName proc2)
{
    return getInstance()->add_one_to_many(CALL_MAP, proc1, proc2) 
        && getInstance()->add_one_to_many_rev(CALL_REV_MAP, proc2, proc1);
}

bool CallTable::addCallStar(ProcName proc1, ProcName proc2)
{
    return getInstance()->add_one_to_many(CALL_STAR_MAP, proc1, proc2)
        && getInstance()->add_one_to_many_rev(CALL_STAR_REV_MAP, proc2, proc1);
}

bool CallTable::isCall(ProcName proc1, ProcName proc2)
{
    return getInstance()->is_one_to_many(CALL_MAP, proc1, proc2);
}

bool CallTable::isCallStar(ProcName proc1, ProcName proc2)
{
    return getInstance()->is_one_to_many(CALL_STAR_MAP, proc1, proc2);
}

ListOfProcNames CallTable::getCall(ProcName proc1)
{
    return getInstance()->get_one_to_many(CALL_MAP, proc1);
}

ListOfProcNames CallTable::getCalledBy(ProcName proc2)
{
    return getInstance()->get_one_to_many_rev(CALL_REV_MAP, proc2);
}

ListOfProcNames CallTable::getCallStar(ProcName proc1)
{
    return getInstance()->get_one_to_many(CALL_STAR_MAP, proc1);
}

ListOfProcNames CallTable::getCalledStarBy(ProcName proc2)
{
    return getInstance()->get_one_to_many_rev(CALL_STAR_REV_MAP, proc2);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallMap()
{
    return getInstance()->get_one_to_many_map(CALL_MAP);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallReverseMap()
{
    return getInstance()->get_one_to_many_rev_map(CALL_REV_MAP);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallStarMap()
{
    return getInstance()->get_one_to_many_map(CALL_STAR_MAP);
}

const std::unordered_map<ProcName, ListOfProcNames>& CallTable::getCallStarReverseMap()
{
    return getInstance()->get_one_to_many_rev_map(CALL_STAR_REV_MAP);
}

void CallTable::clear()
{
    getInstance()->clearAll();
}
