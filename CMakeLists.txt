cmake_minimum_required(VERSION 3.16)

project(lab1_sem3 VERSION 1.0 LANGUAGES CXX)

add_compile_options(
        -Werror

        -Wall
#        -Wextra
#        -Wpedantic
#
#        -Wcast-align
#        -Wcast-qual
#        -Wconversion
#        -Wctor-dtor-privacy
#        -Wenum-compare
#        -Wfloat-equal
#        -Wnon-virtual-dtor
#        -Wold-style-cast
#        -Woverloaded-virtual
#        -Wredundant-decls
#        -Wsign-conversion
#        -Wsign-promo
)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)