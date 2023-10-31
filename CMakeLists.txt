cmake_minimum_required(VERSION 3.24)
project(1)

set(CMAKE_CXX_STANDARD 17)

add_executable(1 main.cpp CFG.cpp CFG.h Symbol.cpp Symbol.h Production.cpp Production.h ReadJson.cpp ReadJson.h PDA.cpp PDA.h State.cpp State.h)
