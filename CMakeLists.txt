cmake_minimum_required(VERSION 3.5)

project(Pson)

add_library(pson STATIC
    src/jsonobject.cpp
    src/jsonarray.cpp
    src/jsonvalue.cpp
    src/json.cpp
    src/jsonutil.cpp
    src/jsonserializer.cpp
    src/jsonparser.cpp
)
target_compile_features(pson PUBLIC cxx_std_17)
target_include_directories(pson PUBLIC include)

