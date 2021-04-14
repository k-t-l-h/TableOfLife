cmake_minimum_required(VERSION 3.10)
project(TableOfLife)
set(CMAKE_CXX_STANDARD 11)


file(
        GLOB Project_SRC
        main.cpp
)

add_executable(TableOfLife ${Project_SRC})