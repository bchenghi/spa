#include "TestUtils.h"

#include "PKB/AssignPostFixTable.h"
#include "PKB/CallTable.h"
#include "PKB/CallStmtTable.h"
#include "PKB/CFGTable.h"
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
#include "PKB/NextTable.h"
#include "PKB/CFGBipTable.h"

void clearPKB() {
    AssignPostFixTable::clear();
    CallTable::clear();
    CallStmtTable::clear();
    CFGTable::clear();
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
    NextTable::clear();
    CFGBipTable::clear();
}
