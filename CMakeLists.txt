cmake_minimum_required(VERSION 3.5)

project(pson)

add_library(libpson SHARED
    src/jsonobject.cpp
    src/jsonarray.cpp
    src/jsonvalue.cpp
    src/json.cpp
    src/jsonutil.cpp
    src/jsonserializer.cpp
    src/jsonparser.cpp
)
target_compile_features(libpson PUBLIC cxx_std_17)
target_include_directories(libpson PUBLIC include)
set_target_properties(libpson PROPERTIES OUTPUT_NAME "pson" )

add_executable(tests tests/tests.cpp )
target_include_directories(tests PUBLIC include)
target_link_libraries(tests libpson)
