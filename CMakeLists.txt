cmake_minimum_required(VERSION 3.10)
project(TableOfLife)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++17 ")

include_directories(Creator)
include_directories(GABuilder)
include_directories(GenAlgo)
include_directories(Genome)
include_directories(Mater)
include_directories(Mutator)
include_directories(Selector)
include_directories(Simulator)


include_directories(Adapter)
include_directories(IDatabase)
include_directories(Manager)
include_directories(ParserToHuman)
include_directories(PatternMaker)
include_directories(Reporter)
include_directories(Result)

include_directories(Queue)
include_directories(Request)
include_directories(Server)
include_directories(ParserToGA)
include_directories(General)
include_directories(Client)

file(
GLOB Project_SRC
        main.cpp
#        "${PROJECT_SOURCE_DIR}/ParserToGA/ParserToGA.h"
#"${PROJECT_SOURCE_DIR}/Gtests/main.cpp"
#"${PROJECT_SOURCE_DIR}/Gtests/TestQueue.cpp"
#"${PROJECT_SOURCE_DIR}/Gtests/TestServer.cpp"
#"${PROJECT_SOURCE_DIR}/Gtests/TestParserToGA.cpp"
)

# если вам нужно собрать динамическую либу (а вообще это только для меня!)
#set(PQ_INCLUDE_DIR /usr/local/Cellar/libpq/13.3/include)
#set(PQXX_INCLUDE_DIR /usr/local/var/homebrew/linked/libpqxx/include/pqxx)
#
#set(PQXX_LIB /usr/local/lib/libpqxx.la)
#set(PQ_LIB /usr/local/Cellar/libpq/13.3/lib/libecpg.6.13.dylib)
##
#find_library(PQXX_LIB pqxx REQUIRED)
#find_library(PQ_LIB pq REQUIRED)

#add_library(reporter STATIC ./Reporter/Reporter.cpp ./Adapter/Adapter.cpp ./IDatabase/TestDatabase/TestDatabase.cpp ./IDatabase/Database.cpp ./ParserToHuman/ParserToHuman.h)

#add_library(reporter STATIC ./Reporter/Reporter.cpp  ./Adapter/Adapter.cpp ./IDatabase/TestDatabase/TestDatabase.cpp ./IDatabase/Database.cpp ./ParserToHuman/ParserToHuman.cpp)

add_library(reporter STATIC ./Reporter/Reporter.cpp  ./Adapter/Adapter.cpp ./IDatabase/TestDatabase/TestDatabase.cpp ./IDatabase/Database.cpp )

# Тут будет boost
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(test1 main.cpp)
target_link_libraries(test1  ${Boost_LIBRARIES})

add_executable(TableOfLife ${Project_SRC})
target_link_libraries(TableOfLife reporter)
target_link_libraries(TableOfLife ${PQXX_LIB} ${PQ_LIB}  ${Boost_LIBRARIES})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


target_link_libraries(TableOfLife ${GTEST_LIBRARIES})
target_link_libraries(TableOfLife pthread)

add_test(TableOfLife TableOfLife)