#ifndef AUTOTESTER_DESIGNENTITY_H
#define AUTOTESTER_DESIGNENTITY_H

#include <string>

enum class DesignEntity {
    kAssign,
    kCall,
    kConstant,
    kIf,
    kPrint,
    kProcedure,
    kRead,
    kStmt,
    kWhile
};

#endif //AUTOTESTER_DESIGNENTITY_H
