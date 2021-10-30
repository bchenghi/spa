#include "NextTable.h"

NextTable* NextTable::nextTablePtr = nullptr;

bool NextTable::addNext(ProgLine n1, ProgLine n2) 
{
    return getInstance()->addOneToMany(NEXT_MAP, n1, n2)
        && getInstance()->addOneToManyRev(PREV_MAP, n2, n1);
}

bool NextTable::isNext(ProgLine n1, ProgLine n2)
{
    return getInstance()->isOneToMany(NEXT_MAP, n1, n2);
}

ListOfProgLines NextTable::getNext(ProgLine n1)
{
    return getInstance()->getOneToMany(NEXT_MAP, n1);
}

ListOfProgLines NextTable::getPrev(ProgLine n2)
{
    return getInstance()->getOneToManyRev(PREV_MAP, n2);
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextTable::getNextMap()
{
    return getInstance()->getOneToManyMap(NEXT_MAP);
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextTable::getPrevMap()
{
    return getInstance()->getOneToManyRevMap(PREV_MAP);
}

void NextTable::clear()
{
    getInstance()->clearAll();
}
