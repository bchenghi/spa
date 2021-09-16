//
// Created by geyul on 16/9/2021.
//

#include "TestUtils.h"
#include <PKB//AssignPostFixTable.h>
#include <PKB/ConstantTable.h>
#include <PKB/FollowTable.h>
#include <PKB/ModifyTable.h>
#include <PKB/ParentTable.h>
#include <PKB/ProcTable.h>
#include <PKB/TypeToStmtNumTable.h>
#include <PKB/UseTable.h>
#include <PKB/VarTable.h>

void clearPKB() {
    AssignPostFixTable::clear();
    ConstantTable::clear();
    FollowTable::clear();
    ModifyTable::clear();
    ParentTable::clear();
    ProcTable::clear();
    TypeToStmtNumTable::clear();
    UseTable::clear();
    VarTable::clear();
}
