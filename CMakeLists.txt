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

file(
        GLOB Project_SRC
        "${PROJECT_SOURCE_DIR}/Gtests/*"

)

add_executable(TableOfLife ${Project_SRC})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(TableOfLife ${GTEST_LIBRARIES})
target_link_libraries(TableOfLife pthread)

add_test(TableOfLife TableOfLife)