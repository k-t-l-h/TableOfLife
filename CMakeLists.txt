cmake_minimum_required(VERSION 3.10)
project(TableOfLife)
set(CMAKE_CXX_STANDARD 11)

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

add_executable(TableOfLife ${Project_SRC})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(TableOfLife ${GTEST_LIBRARIES})
target_link_libraries(TableOfLife pthread)

add_test(TableOfLife TableOfLife)