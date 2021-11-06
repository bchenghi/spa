#include "PkbAbstractor.h"
#include "PkbAbstractorHelper.h"
#include "WithAbstractorHelper.h"

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValues(DesignEntity designEntity1, AttributeType attributeType1,
                                                                     DesignEntity designEntity2, AttributeType attributeType2) {

    list<pair<Value, Value>> result;

    switch(designEntity1) {
        case DesignEntity::ASSIGN:
            result = getWithNoneValuesHelperAssign1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::CALL:
            result = getWithNoneValuesHelperCall1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::CONSTANT:
            result = getWithNoneValuesHelperConstant1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::IF:
            result = getWithNoneValuesHelperIf1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::PRINT:
            result = getWithNoneValuesHelperPrint1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::PROCEDURE:
            result = getWithNoneValuesHelperProcedure1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::PROGRAM_LINE:
            result = getWithNoneValuesHelperStmtOrProgline1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::READ:
            result = getWithNoneValuesHelperRead1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::STMT:
            result = getWithNoneValuesHelperStmtOrProgline1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::VARIABLE:
            result = getWithNoneValuesHelperVariable1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::WHILE:
            result = getWithNoneValuesHelperWhile1(attributeType1, designEntity2, attributeType2);
            break;

        case DesignEntity::NONE:
            break;

        default:
            throw "Invalid Design Entity";
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperAssign1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::ASSIGN || designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                    result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    if (listOfConstants.find(*itAssignStmtNums) != listOfConstants.end()) {
                        string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                        result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperCall1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::PROCEDURE_NAME) {
        if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for (itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    string callStmtNumStr = std::to_string(*itCallStmts);
                    ProcName procCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    result.push_back(make_pair(callStmtNumStr, procCalled));
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                std::unordered_map<ProcName, ListOfStmtNos> procStmtListMap = CallStmtTable::getProcToCallStmtsMap();
                std::unordered_map<ProcName, ListOfStmtNos>::iterator procStmtListIterator;
                for (procStmtListIterator = procStmtListMap.begin(); procStmtListIterator != procStmtListMap.end(); procStmtListIterator++) {
                    pair<ProcName, ListOfStmtNos> procStmtList = *procStmtListIterator;
                    ListOfStmtNos stmtList = procStmtList.second;
                    ListOfStmtNos::iterator stmtListIterator;
                    ListOfStmtNos::iterator stmtListIterator1;
                    for (stmtListIterator = stmtList.begin(); stmtListIterator != stmtList.end(); stmtListIterator++) {
                        string callStmtNumStr = std::to_string(*stmtListIterator);
                        for (stmtListIterator1 = stmtList.begin(); stmtListIterator1 != stmtList.end(); stmtListIterator1++) {
                            string callStmtNumStr1 = std::to_string(*stmtListIterator1);
                            result.push_back(make_pair(callStmtNumStr, callStmtNumStr1));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itRead;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
                        VarName readVarName = *(ModifyTable::getStmtModify(*itRead).begin());

                        if (procNameCalled == readVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string readStmtNumStr = std::to_string(*itRead);
                            result.push_back(make_pair(callStmtNumstr, readStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2  == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrint;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
                        VarName printVarName = *(UseTable::getStmtUse(*itPrint).begin());

                        if (procNameCalled == printVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string printStmtNumStr = std::to_string(*itPrint);
                            result.push_back(make_pair(callStmtNumstr, printStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    if (listOfVarNames.find(procNameCalled) != listOfVarNames.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmts);
                        result.push_back(make_pair(callStmtNumStr, procNameCalled));
                    }
                }
            }
        }
    } else if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::CALL || designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                ListOfStmtNos listOfCallStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmtNums;

                for(itCallStmtNums = listOfCallStmtNums.begin(); itCallStmtNums != listOfCallStmtNums.end(); ++itCallStmtNums) {
                    string callStmtNumStr = std::to_string(*itCallStmtNums);
                    result.push_back(make_pair(callStmtNumStr, callStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfStmtNos listOfCallStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itCallStmtNums = listOfCallStmtNums.begin(); itCallStmtNums != listOfCallStmtNums.end(); ++itCallStmtNums) {
                    if (listOfConstants.find(*itCallStmtNums) != listOfConstants.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmtNums);
                        result.push_back(make_pair(callStmtNumStr, callStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperConstant1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::VALUE) {
        if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    string constStr = std::to_string(*itConstants);
                    result.push_back(make_pair(constStr, constStr));
                }
            }
        } else if (designEntity2 == DesignEntity::STMT) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                    if (*itConstants <= largestStmtNum && *itConstants > 0) {
                        string constStr = std::to_string(*itConstants);
                        result.push_back(make_pair(constStr, constStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::NONE) {
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                    if (*itConstants <= largestStmtNum && *itConstants > 0) {
                        string constStr = std::to_string(*itConstants);
                        result.push_back(make_pair(constStr, constStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::ASSIGN) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    if (listOfConstants.find(*itAssignStmtNums) != listOfConstants.end()) {
                        string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                        result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfCallStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itCallStmtNums = listOfCallStmtNums.begin(); itCallStmtNums != listOfCallStmtNums.end(); ++itCallStmtNums) {
                    if (listOfConstants.find(*itCallStmtNums) != listOfConstants.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmtNums);
                        result.push_back(make_pair(callStmtNumStr, callStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::IF) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIfStmtNums;
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itIfStmtNums = listOfIfStmtNums.begin(); itIfStmtNums != listOfIfStmtNums.end(); ++itIfStmtNums) {
                    if (listOfConstants.find(*itIfStmtNums) != listOfConstants.end()) {
                        string ifStmtNumStr = std::to_string(*itIfStmtNums);
                        result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::WHILE) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhileStmtNums;
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itWhileStmtNums = listOfWhileStmtNums.begin(); itWhileStmtNums != listOfWhileStmtNums.end(); ++itWhileStmtNums) {
                    if (listOfConstants.find(*itWhileStmtNums) != listOfConstants.end()) {
                        string whileStmtNumStr = std::to_string(*itWhileStmtNums);
                        result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    if (listOfConstants.find(*itPrintStmtNums) != listOfConstants.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmtNums);
                        result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    if (listOfConstants.find(*itReadStmtNums) != listOfConstants.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmtNums);
                        result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperIf1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::IF || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIfStmtNums;

                for(itIfStmtNums = listOfIfStmtNums.begin(); itIfStmtNums != listOfIfStmtNums.end(); ++itIfStmtNums) {
                    string ifStmtNumStr = std::to_string(*itIfStmtNums);
                    result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIfStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itIfStmtNums = listOfIfStmtNums.begin(); itIfStmtNums != listOfIfStmtNums.end(); ++itIfStmtNums) {
                    if (listOfConstants.find(*itIfStmtNums) != listOfConstants.end()) {
                        string ifStmtNumStr = std::to_string(*itIfStmtNums);
                        result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperPrint1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::PRINT || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    if (listOfConstants.find(*itPrintStmtNums) != listOfConstants.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmtNums);
                        result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                    }
                }
            }
        }
    } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
        if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                    result.push_back(make_pair(printStmtNumStr, printVarName));
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;
                ListOfStmtNos::iterator itPrintStmtNums2;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                    for (itPrintStmtNums2 = listOfPrintStmtNums.begin(); itPrintStmtNums2 != listOfPrintStmtNums.end(); ++itPrintStmtNums2) {
                        VarName printVarName2 = *(UseTable::getStmtUse(*itPrintStmtNums2).begin());

                        if (printVarName == printVarName2) {
                            string printStmtNumStr = std::to_string(*itPrintStmtNums);
                            string printStmtNumStr2 = std::to_string(*itPrintStmtNums2);
                            result.push_back(make_pair(printStmtNumStr, printStmtNumStr2));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());

                    for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                        VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                        if (readVarName == printVarName) {
                            string readStmtNumStr = std::to_string(*itReadStmtNums);
                            string printStmtNumStr = std::to_string(*itPrintStmtNums);
                            result.push_back(make_pair(printStmtNumStr, readStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfProcNames listOfProcName = ProcTable::getAllProcedure();

                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                    if (listOfProcName.find(printVarName) !=  listOfProcName.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmtNums);
                        result.push_back(make_pair(printStmtNumStr, printVarName));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrint;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itPrint = listOfPrintStmts.begin(); itPrint != listOfPrintStmts.end(); ++itPrint) {
                        VarName printVarName = *(UseTable::getStmtUse(*itPrint).begin());

                        if (procNameCalled == printVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string printStmtNumStr = std::to_string(*itPrint);
                            result.push_back(make_pair(printStmtNumStr, callStmtNumstr));
                        }
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperProcedure1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::PROCEDURE_NAME) {
        if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for (itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    string callStmtNumStr = std::to_string(*itCallStmts);
                    ProcName procCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    result.push_back(make_pair(procCalled, callStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfProcNames::iterator itProcNames;

                for(itProcNames = listOfProcNames.begin(); itProcNames != listOfProcNames.end(); ++itProcNames) {
                    result.push_back(make_pair(*itProcNames, *itProcNames));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmts;

                for (itReadStmts = listOfReadStmts.begin(); itReadStmts != listOfReadStmts.end(); ++itReadStmts) {
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmts).begin());
                    if (listOfProcNames.find(readVarName) != listOfProcNames.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmts);
                        result.push_back(make_pair(readVarName, readStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfStmtNos listOfPrintStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmts;

                for (itPrintStmts = listOfPrintStmts.begin(); itPrintStmts != listOfPrintStmts.end(); ++itPrintStmts) {
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmts).begin());
                    if (listOfProcNames.find(printVarName) != listOfProcNames.end()) {
                        string printStmtNumStr = std::to_string(*itPrintStmts);
                        result.push_back(make_pair(printVarName, printStmtNumStr));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfVarNames::iterator itVarNames;

                for (itVarNames = listOfVarNames.begin(); itVarNames != listOfVarNames.end(); ++itVarNames) {
                    if (listOfProcNames.find(*itVarNames) != listOfProcNames.end()) {
                        result.push_back(make_pair(*itVarNames, *itVarNames));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperStmtOrProgline1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM || attributeType1 == AttributeType::NONE) {
        if (designEntity2 == DesignEntity::IF)  {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfIfStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);
                ListOfStmtNos::iterator itIf;

                for (itIf = listOfIfStmtNums.begin(); itIf != listOfIfStmtNums.end(); ++itIf) {
                    string ifStmtNumStr = std::to_string(*itIf);
                    result.push_back(make_pair(ifStmtNumStr, ifStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::WHILE) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhile;

                for (itWhile = listOfWhileStmtNums.begin(); itWhile != listOfWhileStmtNums.end(); ++itWhile) {
                    string whileStmtNumStr = std::to_string(*itWhile);
                    result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();

                for (int i = 1; i <= largestStmtNum; i++) {
                    string stmtNum = std::to_string(i);
                    result.push_back(make_pair(stmtNum, stmtNum));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    result.push_back(make_pair(printStmtNumStr, printStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::ASSIGN) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfAssignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);
                ListOfStmtNos::iterator itAssignStmtNums;

                for(itAssignStmtNums = listOfAssignStmtNums.begin(); itAssignStmtNums != listOfAssignStmtNums.end(); ++itAssignStmtNums) {
                    string assignStmtNumStr = std::to_string(*itAssignStmtNums);
                    result.push_back(make_pair(assignStmtNumStr, assignStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::STMT_NUM) {
                ListOfStmtNos listOfCallStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmtNums;

                for(itCallStmtNums = listOfCallStmtNums.begin(); itCallStmtNums != listOfCallStmtNums.end(); ++itCallStmtNums) {
                    string callStmtNumStr = std::to_string(*itCallStmtNums);
                    result.push_back(make_pair(callStmtNumStr, callStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfConstants listOfConstants = ConstantTable::getAllConstant();
                ListOfConstants::iterator itConstants;

                for (itConstants = listOfConstants.begin(); itConstants != listOfConstants.end(); ++itConstants) {
                    StmtNum largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                    if (*itConstants <= largestStmtNum && *itConstants > 0) {
                        string constStr = std::to_string(*itConstants);
                        result.push_back(make_pair(constStr, constStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperRead1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::READ || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    if (listOfConstants.find(*itReadStmtNums) != listOfConstants.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmtNums);
                        result.push_back(make_pair(readStmtNumStr, readStmtNumStr));
                    }
                }
            }
        }
    } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
        if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                    result.push_back(make_pair(readStmtNumStr, readVarName));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;
                ListOfStmtNos::iterator itReadStmtNums2;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                    for (itReadStmtNums2 = listOfReadStmtNums.begin(); itReadStmtNums2 != listOfReadStmtNums.end(); ++itReadStmtNums2) {
                        VarName readVarName2 = *(ModifyTable::getStmtModify(*itReadStmtNums2).begin());

                        if (readVarName == readVarName2) {
                            string readStmtNumStr = std::to_string(*itReadStmtNums);
                            string readStmtNumStr2 = std::to_string(*itReadStmtNums2);
                            result.push_back(make_pair(readStmtNumStr, readStmtNumStr2));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());

                    for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                        VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                        if (readVarName == printVarName) {
                            string readStmtNumStr = std::to_string(*itReadStmtNums);
                            string printStmtNumStr = std::to_string(*itPrintStmtNums);
                            result.push_back(make_pair(readStmtNumStr, printStmtNumStr));
                        }
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmts;

                for (itReadStmts = listOfReadStmts.begin(); itReadStmts != listOfReadStmts.end(); ++itReadStmts) {
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmts).begin());
                    if (listOfProcNames.find(readVarName) != listOfProcNames.end()) {
                        string readStmtNumStr = std::to_string(*itReadStmts);
                        result.push_back(make_pair(readStmtNumStr, readVarName));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;
                ListOfStmtNos listOfReadStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itRead;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);

                    for(itRead = listOfReadStmts.begin(); itRead != listOfReadStmts.end(); ++itRead) {
                        VarName readVarName = *(ModifyTable::getStmtModify(*itRead).begin());

                        if (procNameCalled == readVarName) {
                            string callStmtNumstr = std::to_string(*itCallStmts);
                            string readStmtNumStr = std::to_string(*itRead);
                            result.push_back(make_pair(readStmtNumStr, callStmtNumstr));
                        }
                    }

                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperVariable1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::VARIABLE_NAME) {
        if (designEntity2 == DesignEntity::PRINT) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
                ListOfStmtNos::iterator itPrintStmtNums;

                for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                    string printStmtNumStr = std::to_string(*itPrintStmtNums);
                    VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                    result.push_back(make_pair(printVarName, printStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::READ) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfStmtNos listOfReadStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
                ListOfStmtNos::iterator itReadStmtNums;

                for(itReadStmtNums = listOfReadStmtNums.begin(); itReadStmtNums != listOfReadStmtNums.end(); ++itReadStmtNums) {
                    string readStmtNumStr = std::to_string(*itReadStmtNums);
                    VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                    result.push_back(make_pair(readVarName, readStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::VARIABLE) {
            if (attributeType2 == AttributeType::VARIABLE_NAME) {
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfVarNames::iterator itVarNames;

                for(itVarNames = listOfVarNames.begin(); itVarNames != listOfVarNames.end(); ++itVarNames) {
                    result.push_back(make_pair(*itVarNames, *itVarNames));
                }
            }
        } else if (designEntity2 == DesignEntity::PROCEDURE) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfVarNames::iterator itVarNames;

                for (itVarNames = listOfVarNames.begin(); itVarNames != listOfVarNames.end(); ++itVarNames) {
                    if (listOfProcNames.find(*itVarNames) != listOfProcNames.end()) {
                        result.push_back(make_pair(*itVarNames, *itVarNames));
                    }
                }
            }
        } else if (designEntity2 == DesignEntity::CALL) {
            if (attributeType2 == AttributeType::PROCEDURE_NAME) {
                ListOfVarNames listOfVarNames = VarTable::getAllVarName();
                ListOfStmtNos listOfCallStmts = TypeToStmtNumTable::getStmtWithType(DesignEntity::CALL);
                ListOfStmtNos::iterator itCallStmts;

                for(itCallStmts = listOfCallStmts.begin(); itCallStmts != listOfCallStmts.end(); ++itCallStmts) {
                    ProcName procNameCalled = CallStmtTable::getProcCalled(*itCallStmts);
                    if (listOfVarNames.find(procNameCalled) != listOfVarNames.end()) {
                        string callStmtNumStr = std::to_string(*itCallStmts);
                        result.push_back(make_pair(procNameCalled, callStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithNoneValuesHelperWhile1(AttributeType attributeType1, DesignEntity designEntity2, AttributeType attributeType2) {
    list<pair<Value, Value>> result;

    if (attributeType1 == AttributeType::STMT_NUM) {
        if (designEntity2 == DesignEntity::STMT || designEntity2 == DesignEntity::WHILE || designEntity2 == DesignEntity::PROGRAM_LINE) {
            if (attributeType2 == AttributeType::STMT_NUM || attributeType2 == AttributeType::NONE) {
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhileStmtNums;

                for(itWhileStmtNums = listOfWhileStmtNums.begin(); itWhileStmtNums != listOfWhileStmtNums.end(); ++itWhileStmtNums) {
                    string whileStmtNumStr = std::to_string(*itWhileStmtNums);
                    result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                }
            }
        } else if (designEntity2 == DesignEntity::CONSTANT) {
            if (attributeType2 == AttributeType::VALUE) {
                ListOfStmtNos listOfWhileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);
                ListOfStmtNos::iterator itWhileStmtNums;

                ListOfConstants listOfConstants = ConstantTable::getAllConstant();

                for(itWhileStmtNums = listOfWhileStmtNums.begin(); itWhileStmtNums != listOfWhileStmtNums.end(); ++itWhileStmtNums) {
                    if (listOfConstants.find(*itWhileStmtNums) != listOfConstants.end()) {
                        string whileStmtNumStr = std::to_string(*itWhileStmtNums);
                        result.push_back(make_pair(whileStmtNumStr, whileStmtNumStr));
                    }
                }
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithOneValueRight(DesignEntity designEntity1, AttributeType attributeType1, const Value& value2) {
    list<pair<Value, Value>> result;

    if (designEntity1 == DesignEntity::ASSIGN) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos assignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (assignStmtNums.find(numValue2) != assignStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } if (designEntity1 == DesignEntity::CALL) {
        if (attributeType1 == AttributeType::PROCEDURE_NAME) {
            ListOfStmtNos callStmtNums = CallStmtTable::getCallStmtsOfProcCalled(value2);
            ListOfStmtNos::iterator itCalls;

            for (itCalls = callStmtNums.begin(); itCalls != callStmtNums.end(); ++itCalls) {
                string callStmtNumStr = std::to_string(*itCalls);
                result.push_back(make_pair(callStmtNumStr, value2));
            }
        } else if (attributeType1 == AttributeType::STMT_NUM) {
            int numValue2 = std::stoi(value2);
            ProcName procName = CallStmtTable::getProcCalled(numValue2);

            if (procName != "") {
                result.push_back(make_pair(value2, value2));
            }
        }
    } else if (designEntity1 == DesignEntity::CONSTANT) {
        if (attributeType1 == AttributeType::VALUE) {
            ListOfConstants listOfConstants = ConstantTable::getAllConstant();

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (listOfConstants.find(numValue2) != listOfConstants.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::IF) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos ifStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (ifStmtNums.find(numValue2) != ifStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::WHILE) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos whileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (whileStmtNums.find(numValue2) != whileStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::PRINT) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos printStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (printStmtNums.find(numValue2) != printStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
            ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
            ListOfStmtNos::iterator itPrintStmtNums;

            for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                if (printVarName == value2) {
                    string printStmtStr = std::to_string(*itPrintStmtNums);
                    result.push_back(make_pair(printStmtStr, printVarName));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::READ) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos readStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (readStmtNums.find(numValue2) != readStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
            ListOfStmtNos readStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
            ListOfStmtNos::iterator itReadStmtNums;

            for(itReadStmtNums = readStmtNums.begin(); itReadStmtNums != readStmtNums.end(); ++itReadStmtNums) {
                VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                if (readVarName == value2) {
                    string readStmtStr = std::to_string(*itReadStmtNums);
                    result.push_back(make_pair(readStmtStr, readVarName));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::PROCEDURE) {
        if (attributeType1 == AttributeType::PROCEDURE_NAME) {
            ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();

            if (listOfProcNames.find(value2) != listOfProcNames.end()) {
                result.push_back(make_pair(value2, value2));
            }
        }
    } else if (designEntity1 == DesignEntity::PROGRAM_LINE || designEntity1 == DesignEntity::STMT) {
        if (attributeType1 == AttributeType::NONE || attributeType1 == AttributeType::STMT_NUM) {
            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                int largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                if (numValue2 > 0 && numValue2 <= largestStmtNum) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::VARIABLE) {
        if (attributeType1 == AttributeType::VARIABLE_NAME) {
            ListOfVarNames listOfVarNames = VarTable::getAllVarName();

            if (listOfVarNames.find(value2) != listOfVarNames.end()) {
                result.push_back(make_pair(value2, value2));
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithOneValueLeft(DesignEntity designEntity1, AttributeType attributeType1, const Value& value2) {
    list<pair<Value, Value>> result;

    if (designEntity1 == DesignEntity::ASSIGN) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos assignStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::ASSIGN);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (assignStmtNums.find(numValue2) != assignStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } if (designEntity1 == DesignEntity::CALL) {
        if (attributeType1 == AttributeType::PROCEDURE_NAME) {
            ListOfStmtNos callStmtNums = CallStmtTable::getCallStmtsOfProcCalled(value2);
            ListOfStmtNos::iterator itCalls;

            for (itCalls = callStmtNums.begin(); itCalls != callStmtNums.end(); ++itCalls) {
                string callStmtNumStr = std::to_string(*itCalls);
                result.push_back(make_pair(value2, callStmtNumStr));
            }
        } else if (attributeType1 == AttributeType::STMT_NUM) {
            int numValue2 = std::stoi(value2);
            ProcName procName = CallStmtTable::getProcCalled(numValue2);

            if (procName != "") {
                result.push_back(make_pair(value2, value2));
            }
        }
    } else if (designEntity1 == DesignEntity::CONSTANT) {
        if (attributeType1 == AttributeType::VALUE) {
            ListOfConstants listOfConstants = ConstantTable::getAllConstant();

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (listOfConstants.find(numValue2) != listOfConstants.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::IF) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos ifStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::IF);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (ifStmtNums.find(numValue2) != ifStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::WHILE) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos whileStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::WHILE);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (whileStmtNums.find(numValue2) != whileStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::PRINT) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos printStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (printStmtNums.find(numValue2) != printStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
            ListOfStmtNos listOfPrintStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::PRINT);
            ListOfStmtNos::iterator itPrintStmtNums;

            for(itPrintStmtNums = listOfPrintStmtNums.begin(); itPrintStmtNums != listOfPrintStmtNums.end(); ++itPrintStmtNums) {
                VarName printVarName = *(UseTable::getStmtUse(*itPrintStmtNums).begin());
                if (printVarName == value2) {
                    string printStmtStr = std::to_string(*itPrintStmtNums);
                    result.push_back(make_pair(printVarName, printStmtStr));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::READ) {
        if (attributeType1 == AttributeType::STMT_NUM) {
            ListOfStmtNos readStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);

            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                if (readStmtNums.find(numValue2) != readStmtNums.end()) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        } else if (attributeType1 == AttributeType::VARIABLE_NAME) {
            ListOfStmtNos readStmtNums = TypeToStmtNumTable::getStmtWithType(DesignEntity::READ);
            ListOfStmtNos::iterator itReadStmtNums;

            for(itReadStmtNums = readStmtNums.begin(); itReadStmtNums != readStmtNums.end(); ++itReadStmtNums) {
                // for each read stmt num, get the var used, then check if it = value2
                VarName readVarName = *(ModifyTable::getStmtModify(*itReadStmtNums).begin());
                if (readVarName == value2) {
                    string readStmtStr = std::to_string(*itReadStmtNums);
                    result.push_back(make_pair(readVarName, readStmtStr));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::PROCEDURE) {
        if (attributeType1 == AttributeType::PROCEDURE_NAME) {
            ListOfProcNames listOfProcNames = ProcTable::getAllProcedure();

            if (listOfProcNames.find(value2) != listOfProcNames.end()) {
                result.push_back(make_pair(value2, value2));
            }
        }
    } else if (designEntity1 == DesignEntity::PROGRAM_LINE || designEntity1 == DesignEntity::STMT) {
        if (attributeType1 == AttributeType::NONE || attributeType1 == AttributeType::STMT_NUM) {
            if (PkbAbstractorHelper::isNum(value2)) {
                int numValue2 = std::stoi(value2);
                int largestStmtNum = TypeToStmtNumTable::getLargestStmt();
                if (numValue2 > 0 && numValue2 <= largestStmtNum) {
                    result.push_back(make_pair(value2, value2));
                }
            }
        }
    } else if (designEntity1 == DesignEntity::VARIABLE) {
        if (attributeType1 == AttributeType::VARIABLE_NAME) {
            // v.varName = "x"
            ListOfVarNames listOfVarNames = VarTable::getAllVarName();

            if (listOfVarNames.find(value2) != listOfVarNames.end()) {
                result.push_back(make_pair(value2, value2));
            }
        }
    }
    return result;
}

list<pair<Value, Value>> pql::WithAbstractorHelper::getWithBothValues(const Value& value1, const Value& value2) {
    list<pair<Value, Value>> result;

    if (value1 == value2) {
        result.push_back(make_pair(value1, value2));
    }
    return result;
}