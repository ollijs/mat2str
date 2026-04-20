cmake_minimum_required(VERSION 3.10)

project(mat2str)

add_executable(exampleMain-basic "exampleMain-basic.cpp" "mat2str.h" "mat2str-cout.h")

add_executable(exampleMain-ext "exampleMain-ext.cpp" "mat2str.h" "mat2str-cout.h" "mat2str-glm.h"  "exampleMain-ext.cpp")
message(WARNING "mat2str doesn't come with linalg.h or glm sources, you have to provide them to compile and run exampleMain-ext")
