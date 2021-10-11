#include "TestUtils.h"

#include "PKB/AssignPostFixTable.h"
#include "PKB/CallTable.h"
#include "PKB/CallStmtTable.h"
#include "PKB/ConstantTable.h"
#include "PKB/FollowTable.h"
#include "PKB/IfControlTable.h"
#include "PKB/ModifyTable.h"
#include "PKB/ParentTable.h"
#include "PKB/ProcTable.h"
#include "PKB/TypeToStmtNumTable.h"
#include "PKB/UseTable.h"
#include "PKB/VarTable.h"
#include "PKB/WhileControlTable.h"

void clearPKB() {
    AssignPostFixTable::clear();
    CallTable::clear();
    CallStmtTable::clear();
    ConstantTable::clear();
    FollowTable::clear();
    IfControlTable::clear();
    ModifyTable::clear();
    ParentTable::clear();
    ProcTable::clear();
    TypeToStmtNumTable::clear();
    UseTable::clear();
    VarTable::clear();
    WhileControlTable::clear();
}
