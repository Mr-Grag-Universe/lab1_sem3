cmake_minimum_required(VERSION 3.16)
project(CM_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(CM_lib
        CSR.cpp
        DOC.cpp
        ListMatrix.cpp
        input.cpp
        common.cpp
        matrixes.h
        input.h
        )
