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

file(
        GLOB Project_SRC
        "${PROJECT_SOURCE_DIR}/Gtests/*"
)

add_library(reporter STATIC ./Reporter/Reporter.cpp ./Manager/Manager.cpp ./Adapter/Adapter.cpp ./IDatabase/TestDatabase/TestDatabase.cpp)


add_executable(TableOfLife ${Project_SRC})
target_link_libraries(TableOfLife reporter)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(TableOfLife ${GTEST_LIBRARIES})
target_link_libraries(TableOfLife pthread)


add_test(TableOfLife TableOfLife)
