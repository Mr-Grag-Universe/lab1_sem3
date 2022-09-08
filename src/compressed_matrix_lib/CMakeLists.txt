cmake_minimum_required(VERSION 3.16)
project(CM_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(CM_lib
        CSR.cpp
        ListMatrix.cpp
        input.cpp
        matrixes.h
        input.h
        )
