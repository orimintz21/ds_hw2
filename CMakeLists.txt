# cmake_minimum_required(VERSION 3.0.0)
# project (hw1 VERSION 0.1.0 LANGUAGES C CXX)
# set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
# set(MTM_FLAGS_RELEASE "${MTM_FLAG_DEBUG} -DNDEBUG")
# set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
# add_executable(my_executable Employee.h Company.h DS.cpp library1.cpp List.h Avltree.h main1.cpp SalaryKey.h)

cmake_minimum_required(VERSION 3.19)
project(322835976)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG")
add_executable(my_executable Employee.cpp Company.cpp Data.cpp employeeTree.cpp library2.cpp List.h Rank.h Node.h UnionFind.cpp Ex2Exception.h RankTreeExceptions.h main2_without_bonus.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.in.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
