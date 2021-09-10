file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/Utils/StmtType.h src/PKB/FollowTable.h src/PKB/ParentTable.h src/PKB/UseTable.h src/PKB/ModifyTable.h src/PKB/TypeToStmtNumTable.h src/PKB/VarTable.h src/PKB/ProcTable.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
