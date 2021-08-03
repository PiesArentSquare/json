cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 17)

project(pson)

include_directories(./include ./src)

add_executable(tests ./src/jsonarray.cpp ./src/jsonobject.cpp ./src/jsonvalue.cpp ./src/jsonutil.cpp ./tests/tests.cpp)