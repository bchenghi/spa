#include "NextTable.h"

NextTable* NextTable::next_table_ptr = nullptr;

bool NextTable::addNext(ProgLine n1, ProgLine n2) 
{
    return getInstance()->add_one_to_many(NEXT_MAP, n1, n2)
        && getInstance()->add_one_to_many_rev(PREV_MAP, n2, n1);
}

bool NextTable::isNext(ProgLine n1, ProgLine n2)
{
    return getInstance()->is_one_to_many(NEXT_MAP, n1, n2);
}

ListOfProgLines NextTable::getNext(ProgLine n1)
{
    return getInstance()->get_one_to_many(NEXT_MAP, n1);
}

ListOfProgLines NextTable::getPrev(ProgLine n2)
{
    return getInstance()->get_one_to_many_rev(PREV_MAP, n2);
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextTable::getNextMap()
{
    return getInstance()->get_one_to_many_map(NEXT_MAP);
}

const std::unordered_map<ProgLine, ListOfProgLines>& NextTable::getPrevMap()
{
    return getInstance()->get_one_to_many_rev_map(PREV_MAP);
}

void NextTable::clear()
{
    getInstance()->clearAll();
}
